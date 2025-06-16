/*
code almost complted - Things that could need changing:
1) change pin numbers to the correct ones, the ones that cannot change -> BPPS status and LED.
2) change the CAN ID's to the correct ones. Make sure that the can message getting received is in the order we aare expecting (aka the order of the LEDS) (so faults are at the start of the array)
2) JSON will change based on signals comming from the back of the car. Make sure you are using the 6.21.5 of the ArduinoJson libarary. 
    To update the JSON part of the code do this
      a) go to https://arduinojson.org/v6/assistant/#/step1 
          i)Processor = AVR
          ii) Mode = Serialization
          iii) Output = Serial
      b) Input the JSON object being received and click on "Generate Code"
      c) Next
      d) copy paste the program into the the area below
4) IF YOU ARE CHANGING THE PIN NUMBERS FOR THE BUTTONS AND LEDS, MAKE SURE THAT YOU UNDERSTAND THE MEANING OF LEDStates (array) will change, worst case you need to change can receive and send messages to correstpond to the position of the LEDs
  */
#include <Arduino.h>//General
#include <SPI.h>
#include <mcp2515.h>//CAN
#include <Adafruit_GPS.h>//GPS
#include <Arduino_LSM6DSOX.h>//Accelerometer/GyroScope/Temperature
#include <ArduinoJson.h>



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Buttons N LEDS<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	bool shouldLEDBlink = false;
	
	//Funtion Prototypes for Buttons n LEDS
	void checkCurrentButtonStates(int* switchArr);
	bool arraysEqual(const int* a, const int* b, size_t length);
	void actingOnVCUData(unsigned char* canArr);
	
	//timeKeeping
	unsigned previousMillisBlinkLED = 0; // will store last time LED was updated
	unsigned long oldTimeForCheckingButtons = 0;
	unsigned blinkingInterval = 500; // interval at which to blink the precharge LED (milliseconds)
	unsigned int checkButtonDelay = 5;//checks for button changes every 5ms
	int buttonDebounceCheckDuration = 15;//Double check button changes after 15ms

	//Stores Current Button and LED states
	int currentButtonState[5] = {0,0,0,0,0};
	int prevButtonState[5] = {0,0,0,0,0};//buton right now is set as 0=OFF, 1=ON
	int ledStates[8] = {1,1,1,1,1,2,1,1};//right now set as 0=OFF, 1=ON, 2=BLINKING 1-5 are Faults (RED), 6 is precharge (YELLOW), 7 and 8 is Regen and Traction (GREEN)
  //5 is the push button

	/*-------------NEED TO DECIDE PINS FOR THESE TO ATTACH TO-------------*/
	const int HVsts_LED = 23;
  const int RTDsts_LED = 25;
  const int BMSsts=27;
	const int IMDsts = 29;
	const int BPPSsts = 31;
  const int Prechargests_LED = 33;
	const int Regen = 35;
  const int Traction = 37;
	const int HVsts_Switch = 22;//Number 1 in the array
	const int RTDsts_Switch = 24;//Number 2 in the array
  const int Regen_Switch = 26;//Number 3 in the array
	const int Traction_Switch = 28;//Number 4 in the array
	const int BPPSsts_Switch = 30;//Number 5 in the array <- the push button

	/*--------------------------------------------------------------------*/
	
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CAN<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	struct can_frame canMsgReceived_LEDS;
	struct can_frame canMsgToSend_Buttons;
	int cntr_CANMsgs = 0;int canMsgsPerSec = 0;
	unsigned long timeSinceLastSecond_CAN = 0;
	MCP2515 mcp2515(53);
	unsigned int canIDIncomming = 0x101, canIDOutGoing = 0x196, canOutgoingLength = 0x8;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>GPS<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Adafruit_GPS GPS(&Wire);                                       // Hardware-I²C GPS
	#define GPSECHO false                                          // Echo raw NMEA if true

	struct GPSData {
	  uint8_t  hour, minute, seconds;      uint16_t milliseconds;
	  uint8_t  day,   month;               uint16_t year;
	  bool     fix;        uint8_t fixQuality;
	  float    latitude;   char   latHem;
	  float    longitude;  char   lonHem;
	  float    speedKnots;
	  float    angle;
	  float    altitude;
	  uint8_t  satellites;

	  String   timeStamp;  // ⇦ “HH:MM:SS.mmm”
	  String   dateStamp;  // ⇦ “DD/MM/YYYY”
	};
	GPSData currentGPSData;                                                // Latest snapshot
	uint32_t timeSinceLastGPSUpdate = millis();                                      // 2-s timer
	unsigned int delayBetweenGPSUpdates_ms = 2000;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Accelerometer/GyroScope/Temprature<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
float sampleRate_G_Hz,sampleRate_A_Hz;
float gyroX, gyroY, gyroZ;//degrees/second
float accelX, accelY, accelZ;//g's
float temperature_float;//Celsius
//int temperature_int;//Celsius

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>JSON<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
long jsonsSent = 0;
int cntr_json = 0;
unsigned long oldTime_Json = 0;
int jsonsPerSec = 0;


void setup() {
  Serial.begin(1000000);

/*Configure buttons and LED Pins*/
  pinMode(HVsts_LED, OUTPUT);
  pinMode(RTDsts_LED, OUTPUT);
  pinMode(Prechargests_LED, OUTPUT);
  pinMode(BPPSsts, OUTPUT);
  pinMode(IMDsts, OUTPUT);
  pinMode(BMSsts, OUTPUT);
  pinMode(Regen, OUTPUT);
  pinMode(Traction, OUTPUT);

  pinMode(HVsts_Switch, INPUT);
  pinMode(BPPSsts_Switch, INPUT);
  pinMode(RTDsts_Switch, INPUT);
  pinMode(Regen_Switch, INPUT);
  pinMode(Traction_Switch, INPUT);
 
/*CAN*/
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS,MCP_8MHZ);
  mcp2515.setNormalMode();
  
/*GPS*/
  GPS.begin(0x10);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GPS.println(PMTK_Q_RELEASE);
/*Accelerometer/GyroScope/Temperature*/
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    //while (1);
  }

  //<For Debugging> Serial.print("Gyroscope sample rate = ");  Serial.print(IMU.gyroscopeSampleRate());Serial.println(" Hz");Serial.println();  Serial.println("Gyroscope in degrees/second");  Serial.println("X\tY\tZ");
  //<For Debugging> Serial.print("Accelerometer sample rate = ");  Serial.print(IMU.accelerationSampleRate());  Serial.println(" Hz");  Serial.println();  Serial.println("Acceleration in g's");  Serial.println("X\tY\tZ");

  sampleRate_G_Hz = IMU.gyroscopeSampleRate();
  sampleRate_A_Hz = IMU.accelerationSampleRate();
}

void loop() {
	/*-------------------------------------------------------------CAN Messages Receive-----------------------------------------------------------------------*/
  if (mcp2515.readMessage(&canMsgReceived_LEDS) == MCP2515::ERROR_OK) {
    if(canMsgReceived_LEDS.can_id== canIDIncomming){

      cntr_CANMsgs++;
	    actingOnVCUData(canMsgReceived_LEDS.data);
      //<For Debugging> Serial.print(canMsgReceived_LEDS.can_id, HEX); // print ID
      //<For Debugging> Serial.print(" "); 
      //<For Debugging> Serial.print(canMsgReceived_LEDS.can_dlc, HEX); // print DLC
      //<For Debugging> Serial.print(" ");
      
      //<For Debugging> for (int i = 0; i<canMsgReceived_LEDS.can_dlc; i++)  {  // print the data
        //<For Debugging> Serial.print(canMsgReceived_LEDS.data[i],HEX);
        //<For Debugging> Serial.print(" ");
      //<For Debugging> }
      //<For Debugging> Serial.println(); 
    }
  }
  if ((millis()-timeSinceLastSecond_CAN)>1000) {//How many can messages received
    timeSinceLastSecond_CAN = millis();
    //<For Debugging> Serial.print(cntr_CANMsgs);
    //<For Debugging> Serial.println(" msg/sec");
	  canMsgsPerSec = cntr_CANMsgs;
    cntr_CANMsgs = 0;
  }
 
/*-----------------------------------------------------------BUTTONS AND LEDS--------------------------------------------------------------------------*/
  //actingOnVCUData(ledStates);//update LEDS inrelation to the CanData Received.//called in the "CAN Messages Receive" Section
  if(shouldLEDBlink){//if precharge is supposed to blink, make it happen
    if ((millis() - previousMillisBlinkLED)>= blinkingInterval) { // Check if the interval has passed
      previousMillisBlinkLED = millis(); // Update the last time the LED blinked
      digitalWrite(Prechargests_LED, !digitalRead(Prechargests_LED));
    }
  }
  if ((millis()-oldTimeForCheckingButtons)>checkButtonDelay) {//check if buttons have changed
    oldTimeForCheckingButtons = millis();
    //buttons
    checkCurrentButtonStates(currentButtonState);
    if(!arraysEqual(prevButtonState, currentButtonState, 5)){
      delay(buttonDebounceCheckDuration);// for debouncing the buttons
      checkCurrentButtonStates(currentButtonState);
        if(!arraysEqual(prevButtonState, currentButtonState, 5)){
            memcpy(prevButtonState,currentButtonState,sizeof(currentButtonState));
            //<For Debugging> Serial.print("current: ");Serial.print(currentButtonState[0]);Serial.print(currentButtonState[1]);Serial.print(currentButtonState[2]);Serial.print(currentButtonState[3]);Serial.println(currentButtonState[4]);
            //<For Debugging> Serial.print("prev: ");Serial.print(prevButtonState[0]);Serial.print(prevButtonState[1]);Serial.print(prevButtonState[2]);Serial.print(prevButtonState[3]);Serial.println(prevButtonState[4]);
        }
    }
  }
  
/*-------------------------------------------------------------CAN Messages Send-----------------------------------------------------------------------*/
  canMsgToSend_Buttons.can_id = canIDOutGoing;
  canMsgToSend_Buttons.can_dlc = canOutgoingLength;
  memcpy(canMsgToSend_Buttons.data,currentButtonState,sizeof(currentButtonState));
  mcp2515.sendMessage(&canMsgToSend_Buttons);
/*-------------------------------------------------------------GPS-----------------------------------------------------------------------*/
  char c_GPS = GPS.read();
  if (GPSECHO && c_GPS) Serial.print(c_GPS);

  if (GPS.newNMEAreceived() && GPS.parse(GPS.lastNMEA())){

	  if (millis() - timeSinceLastGPSUpdate > delayBetweenGPSUpdates_ms) {                                // Every ~2 s
		timeSinceLastGPSUpdate = millis();

		//──── Copy scalar fields ────
		currentGPSData.hour        = GPS.hour;
		currentGPSData.minute      = GPS.minute;
		currentGPSData.seconds     = GPS.seconds;
		currentGPSData.milliseconds= GPS.milliseconds;
		currentGPSData.day         = GPS.day;
		currentGPSData.month       = GPS.month;
		currentGPSData.year        = 2000 + GPS.year;
		currentGPSData.fix         = GPS.fix;
		currentGPSData.fixQuality  = GPS.fixquality;
		currentGPSData.latitude    = GPS.latitude;
		currentGPSData.latHem      = GPS.lat;
		currentGPSData.longitude   = GPS.longitude;
		currentGPSData.lonHem      = GPS.lon;
		currentGPSData.speedKnots  = GPS.speed;
		currentGPSData.angle       = GPS.angle;
		currentGPSData.altitude    = GPS.altitude;
		currentGPSData.satellites  = GPS.satellites;

		//──── Build formatted strings ────
		char bufTime[16];
		sprintf(bufTime, "%02d:%02d:%02d.%03d",
				currentGPSData.hour, currentGPSData.minute,
				currentGPSData.seconds, currentGPSData.milliseconds);
		currentGPSData.timeStamp = bufTime;                                // “HH:MM:SS.mmm”

		char bufDate[12];
		sprintf(bufDate, "%02d/%02d/%04d",
				currentGPSData.day, currentGPSData.month, currentGPSData.year);
		currentGPSData.dateStamp = bufDate;                                // “DD/MM/YYYY”

		//<For Debugging> Serial.println(currentGPSData.timeStamp + "\n" + currentGPSData.dateStamp + "\n" + currentGPSData.fix + "     " + currentGPSData.fixQuality + "\n");
		//<For Debugging> Serial.println(currentGPSData.latitude + String("\n") + currentGPSData.longitude + "\n" + currentGPSData.satellites + "     " + currentGPSData.speedKnots + "\n");
	  }
  }
	/*-------------------------------------------------------------Accelerometer/GyroScope/Temperature-----------------------------------------------------------------------*/
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gyroX,gyroY,gyroZ);
    //<For Debugging> Serial.print(gyroX);Serial.print('\t');Serial.print(gyroY);Serial.print('\t');Serial.println(gyroZ);
  }
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accelX, accelY, accelZ);
    //<For Debugging> Serial.print(accelX);Serial.print('\t');Serial.print(accelY);Serial.print('\t');Serial.println(accelZ);
  }
  if (IMU.temperatureAvailable())
  {
    //IMU.readTemperature(temperature_int);//if needed
    IMU.readTemperatureFloat(temperature_float);
    //<For Debugging> Serial.print("LSM6DSOX Temperature = ");Serial.print(temperature_int);Serial.print(" (");Serial.print(temperature_float);Serial.print(")");Serial.println(" °C");
  }
/*----------------------------------------------------------JSON-----------------------------------------------------------------------------------------------------*/
if ((millis()-oldTime_Json)>1000) {
  oldTime_Json = millis();
  Serial.print(cntr_json);
  Serial.println(" msg/sec");
  jsonsPerSec = cntr_json;
  cntr_json = 0;
}

//if (millis()%10 == 0){// every 10 milliseconds - 99msgs/sec -> max capacity -> 104msgs/sec

jsonsSent++;
StaticJsonDocument<512> doc;

JsonObject temprature = doc.createNestedObject("temprature");
temprature["temperature"] = 12;
temprature["condition"] = "cloudy";

JsonObject gps = doc.createNestedObject("gps");
gps["c"] = "";
gps["lastNMEA()"] = "";

JsonObject gps_Time = gps.createNestedObject("Time");
gps_Time["Hours"] = "";
gps_Time["Minutes"] = "";
gps_Time["Seconds"] = "";
gps_Time["Milliseconds"] = "";

JsonObject gps_Date = gps.createNestedObject("Date");
gps_Date["Day"] = "";
gps_Date["Month"] = "";
gps_Date["Year"] = "";

JsonObject gps_Fix = gps.createNestedObject("Fix");
gps_Fix["Value"] = "";
gps_Fix["Quality"] = "";

JsonObject gps_Location = gps.createNestedObject("Location");
gps_Location["Latitude"] = "";
gps_Location["lat"] = "";
gps_Location["Longitude"] = "";
gps_Location["long"] = "";
gps["Speed (Knots)"] = "";
gps["Angle"] = "";
gps["Altitude"] = "";
gps["Satellites"] = "";

JsonObject Dash = doc.createNestedObject("Dash");
Dash["TractionCntrlSwitch"] = currentButtonState[3];
Dash["RgnBreakingSwitch"] = currentButtonState[2];
Dash["RtdButton"] = currentButtonState[1];
Dash["BppsResetButton"] = currentButtonState[4];
Dash["HvSwitch"] = currentButtonState[0];
Dash["BMSsts"] = ledStates[2];
Dash["Precharge"] = ledStates[5];
Dash["Hv"] = ledStates[0];
Dash["BppsLED"] = ledStates[4];
Dash["Imd"] = ledStates[3];
Dash["Bpps"] = ledStates[6];

serializeJson(doc, Serial);
cntr_json++;

Serial.print("\n");
//}
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------
void checkCurrentButtonStates(int* switchArr){
  for(int i = 22; i<=30;i+=2){
    switchArr[(i-22)/2] = digitalRead(i);
  }
}
void actingOnVCUData(unsigned char* canArr){
  for(int i = 23;i<=37;i+=2){
    if(i == Prechargests_LED && static_cast<int>(canArr[2]) == 2){//[2] is replaced by whatever the PreCharge represents in the CAN array in the sequence is.// if statement could be more efficient
      shouldLEDBlink = true;
    }else if(i == Prechargests_LED && (static_cast<int>(canArr[2]) == 1 || static_cast<int>(canArr[2]) == 0)){
      shouldLEDBlink = false;
      digitalWrite(i,static_cast<int>(canArr[(i-23)/2]));
    }else{
      digitalWrite(i,static_cast<int>(canArr[(i-23)/2]));
    }
  }
}
bool arraysEqual(const int* a, const int* b, size_t length) {
  for (size_t i = 0; i < length; i++) {
    if (a[i] != b[i]){return false;}
  }
  return true;
}
