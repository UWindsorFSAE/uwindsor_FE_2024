import customtkinter as ctk
from tkinter import *
import math
import time
import sqlite3
import RPi.GPIO as GPIO

#To Do
# Add code to change the color of the gauges when they are above a certain number and give a error
# Impliment Datalogging
# Impliment CAN data requesting/recieving
# Impliment button controls/leds using interupts
# Replace speed variable with item from sensor_data list

#Nice to have
# Send data from VCU at a set frequency (ie. every 10ms) which some data is averaged over (ie. temperature)
# ^ Send data from VCU and recieve with interupts to save clock cycles

#################################################################################################

#CAN Communication Section (Use interrupts to update values based on CAN signals?)

sensor_data = []

#################################################################################################

#Data logging Code Section
class DataLogging():

    tableSQL = '''
        CREATE TABLE IF NOT EXISTS telemetry_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            DateTime DATETIME,
            Speed INTEGER,
            MotorTemperature REAL,
            CoolantTemperature1 REAL,
            CoolantTemperature2 REAL,
            CoolantTemperature3 REAL,
            CoolantFlowRate REAL,
            MotorCurrent REAL,
            HVBatteryVoltage REAL,
            HVBatteryTemperature REAL,
            LVBatteryVoltage REAL,
            Longitude REAL,
            Latitude REAL,
            yaw REAL,
            Pitch REAL,
            Roll REAL,  
            AccelerationX REAL,
            AccelerationY REAL,
            AccelerationZ REAL,
            MagnetoX REAL,
            MagnetoY REAL,
            MagnetoZ REAL,
            MaxAcceleration REAL,
            TopSpeed INTEGER,
            LapTime REAL,
            DriveMode BOOLEAN
        );
    '''
    #DriveMode is 0 when in neutral, 1 when in drive
    #check connection to DB, useful to run when there is an error
    def connectDB(self, conn):
        try:
            conn.cursor()
        except:
            conn = sqlite3.connect("fsae.db")
            return(conn)

    #create data table if not exists, useful to run when there is an error
    def createTable(self, conn, tableSQL):
        tmp = conn.cursor()
        tmp.execute(tableSQL)
        conn.commit()

    #initialize DB connection
    def __init__(self):
        self.connection = 0
        self.connection = self.connectDB(self.connection)
        self.createTable(self.connection, self.tableSQL)


    #function to be run each loop to log data to DB input DB connection and sensor_data list
    def logData(self, conn, sensor_data):
        tmp = conn.cursor()
        #this SQL needs to be updated to reflect variable change and DB structure change
        tmp.execute('''INSERT INTO telemetry_data
                    (Speed, MotorTemperature,CoolantTemperature1 ,
            CoolantTemperature2,
            CoolantTemperature3 ,
            CoolantFlowRate ,
            MotorCurrent ,
            HVBatteryVoltage ,
            HVBatteryTemperature ,
            LVBatteryVoltage ,
            Longitude ,
            Latitude,
            yaw ,
            Pitch ,
            Roll ,  
            AccelerationX ,
            AccelerationY ,
            AccelerationZ ,
            MagnetoX ,
            MagnetoY ,
            MagnetoZ ,
            MaxAcceleration ,
            TopSpeed ,
            LapTime ,
            DriveMode   )
            VALUES (?, ?, ?)''', sensor_data)
        conn.commit()

#################################################################################################

# Raspberry Pi Pin assignments and initialization
GPIO.setmode(GPIO.BCM)
#pin numbers (button,button,led,led)
pin = [17,27,22,23]

#GPIO.cleanup()

GPIO.setmode(GPIO.BCM)
GPIO.setup(pin[0], GPIO.IN)
GPIO.setup(pin[1], GPIO.IN)
GPIO.setup(pin[2], GPIO.OUT)
GPIO.setup(pin[3], GPIO.OUT)
        
GPIO.output((pin[2],pin[3]), False)

#################################################################################################

# Interrupt Code
led_state2 = False
#switch screen button
def interrupt_1(channel):
    
    global currentMode
    

    if currentMode >= 2:
        currentMode = 0
    else:
        currentMode += 1
    
    
    print(channel)
    global led_state2
    led_state2 = not led_state2
    GPIO.output(pin[3],led_state2)
        
led_state = False
#Screen Function Button
def interrupt_2(channel):
    global led_state
    led_state = not led_state
    GPIO.output(pin[2],led_state)
    print(channel)

GPIO.add_event_detect(17, GPIO.FALLING, callback=interrupt_1, bouncetime=200) #rising edge detection on a pin
GPIO.add_event_detect(27, GPIO.FALLING, callback=interrupt_2, bouncetime=200) #rising edge detection on a pin

#################################################################################################

#Screen Code

#parameters
width = 1024
height = 600
center = [width/2,height/2]
max_speed = 160 #max speed of the dial
gradations = 20 #gradations every X KM/H
velocity = 0 #0 to -180 speed value for the arc

#startup
root = ctk.CTk()
root.configure(fg_color="#1B1464")
root.geometry(f"{width}x{height}") #replace with line below when running on PI
root.wm_attributes('-fullscreen', True)
root.resizable(False,False)
root.title("FSAE Dashboard")
root.grid_columnconfigure((1,2,3), weight=1)

#Fonts
diagnosticFont = ctk.CTkFont(family="Source Sans Pro Bold", size=14, weight="normal") #test changing family name and weight
LabelFont = ctk.CTkFont(family="Source Sans Pro Bold", size=24, weight="normal")
displayFont = ctk.CTkFont(family="Source Sans Pro Bold", size=28, weight="normal")
WarningFont = ctk.CTkFont(family="Source Sans Pro Bold", size=40, weight="normal")
speedFont = ctk.CTkFont(family="Source Sans Pro Bold", size = 60, weight="normal")

#for Endurance Race
class Endurance:

    def __init__(self):
        #Telemetry text boxes
        self.telLabels = ["Motor Temp","Bat Temp","Battery %","Power","Lap Time","Lap Power"]
        self.telNames = []
        #Text Variables
        bTvar = ctk.StringVar(value = "0°C")
        bCvar = ctk.StringVar(value = "0%")
        mTvar = ctk.StringVar(value = "0°C")
        pOvar = ctk.StringVar(value = "0 kW")
        lPvar = ctk.StringVar(value = "0:00")
        aPvar = ctk.StringVar(value = "0 kWh/lap")
        speed_val = ctk.StringVar(value="0 KM/H")
        self.varNames = [mTvar,bTvar,bCvar,pOvar,lPvar,aPvar,speed_val]

    def telemetry_make(self):
        #loop to draw all the buttons and labels
        #Frame for left side data
        self.telLeft = ctk.CTkFrame(master=root,width=175,height=335,border_width=0,
                                    fg_color="transparent",border_color="#FFFFFF",corner_radius=0)
        self.telLeft.grid(row=2,column=1,padx=5,pady=5)
        
        self.telNames = []
        #Frame for right side data
        self.telRight = ctk.CTkFrame(master=root,width=175,height=335,border_width=0,
                                    fg_color="transparent",border_color="#FFFFFF",corner_radius=0)
        self.telRight.grid(row=2,column=3,padx=5,pady=5)
        rowData = [(2,1,5,1),(4,1,5,1),(6,1,5,1),(2,3,5,1),(4,3,5,1),(6,3,5,1)] #row,column,padx,pady
        framedata = [self.telLeft, self.telRight] #Left and Right side data frames
        for i in range(len(self.telLabels)):
            newlabel = ctk.CTkLabel(framedata[math.floor(i/3)], text=f'{self.telLabels[i]}',
                            text_color="#FFD239",fg_color="#1B1464",
                            width=175,height=50, font=LabelFont)
            newlabel.grid(row=rowData[i][0],column=rowData[i][1],padx=rowData[i][2],pady=rowData[i][3])

            newbutton = ctk.CTkButton(framedata[math.floor(i/3)], textvariable=self.varNames[i],
                        text_color="#FFD239",fg_color="#1B1464",
                        width=175,height=50, font=displayFont,
                        corner_radius=10, border_width=4,
                        border_color="#000000", bg_color="transparent",)
            newbutton.grid(row=rowData[i][0]+1,column=rowData[i][1],padx=rowData[i][2],pady=rowData[i][3])
            self.telNames.append(newbutton)
        #draw the error message button
        error = ctk.StringVar(value = "Initial Value")
        self.isError = False
        self.prevError = False
        self.errorMSG = ctk.CTkButton(root, textvariable=error,
                                text_color="black",fg_color='red',
                                width=800,height=60, font=WarningFont,
                                corner_radius=10, border_width=4,
                                border_color="#000000", bg_color="transparent")
        self.errorMSG.grid(row=1,column=1,columnspan=3,padx=5,pady=3)
        #Frame for middle elements
        self.telMid = ctk.CTkFrame(master=root,width=600,border_width=0,
                                    fg_color="transparent",border_color="#FFFFFF",corner_radius=0)
        self.telMid.grid(row=2,column=2,padx=5,pady=5, rowspan=2)
        #Draw the Accelerator position and the brake pressure
        accel_label = ctk.CTkLabel(self.telMid, text="Accelerator Position",
                        text_color="#FFD239",fg_color="#1B1464",
                        width=400,height=21, font=LabelFont)
        accel_label.grid(row=1,column=1,padx=5,pady=1)
        self.accel = ctk.CTkProgressBar(self.telMid, height=25, width=500,
                                        border_width=0,border_color="#000000",
                                        corner_radius=0,fg_color="#242424",
                                        progress_color="#FFD239",orientation="horizontal")
        self.accel.grid(row=2,column=1,padx=5,pady=1)
        self.accel.set(0)

        brake_label = ctk.CTkLabel(self.telMid, text="Brake Pressure",
                        text_color="#FFD239",fg_color="#1B1464",
                        width=400,height=21, font=LabelFont)
        brake_label.grid(row=4,column=1,padx=5,pady=1)

        self.brake = ctk.CTkProgressBar(self.telMid, height=25, width=500,
                                        border_width=0,border_color="#000000",
                                        corner_radius=0,fg_color="#242424",
                                        progress_color="#FFD239",orientation="horizontal")
        self.brake.grid(row=5,column=1,padx=5,pady=1)
        self.brake.set(0)

        #speedometer canvas and placement Note: canvas size/placement changes on different screen sizes for some reason?
        self.speed_frame = Frame(self.telMid,width=600, height=300, bd=0,bg="#1B1464",highlightthickness=0)
        self.speed_frame.grid(row=3,column=1,padx=5,pady=5)
        self.speed = Canvas(self.speed_frame, bd=0,bg="#1B1464",highlightthickness=0,width=600, height=300)
        self.speed.pack(side=TOP)
        #Speed digital readout is within the speedometer
        self.dig_speed = ctk.CTkLabel(self.speed_frame,textvariable=self.varNames[6], text_color="#FFD239",
                            fg_color="transparent", width=300,height=75,
                            font=speedFont,corner_radius=20)
        self.dig_speed.pack(side=BOTTOM)

        #Label that this is the endurance screen
        self.race = ctk.CTkLabel(root, text="ENDURANCE",
                                 text_color="#FFD239",fg_color="#1B1464",
                                 width=175,height=50, font=LabelFont)
        self.race.grid(row=3,column=1,padx=5,pady=3)

    # repeatedly called function for drawing the speedometer
    def draw_speed(self,speed,max_speed,gradations,velocity):
        speed.create_oval(0,0,600,600, fill="#242424",outline="")#grey outline of speedometer (600x600)
        speed.create_arc(25,25,575,575,extent = velocity,start = 180, fill="#FFD239",outline="")#Yellow speedometer (575x575)
        speed.create_oval(50,50,550,550, fill="#1B1464",outline="")#Inner Blue oval that covers the center of the other ovals (550x550)
        circle_center = [300,300]
        #Loop to draw gradations
        for i in range(int(max_speed/5)+1):
            angle = i*math.pi/((max_speed/5))
            xangle = math.cos(angle)
            yangle = -math.sin(angle)
            if (i*5)%gradations == 0:#major Dimension
                speed.create_line(circle_center[0]+299*xangle,circle_center[1]+299*yangle,
                                circle_center[0]+285*xangle,circle_center[1]+285*yangle,fill="#FFD239",width=4)
                
            else:#minor dimension
                speed.create_line(circle_center[0]+299*xangle,circle_center[1]+299*yangle,
                                circle_center[0]+290*xangle,circle_center[1]+290*yangle,fill="#FFD239",width=2)

#for Acceleration, Skidpad and Autocross
class Handling:

    def __init__(self):
        #Telemetry text boxes
        self.telLabels = ["Motor Temp","Bat Temp","Battery %","Power","Acceleration","Max Accel."]
        self.telNames = []
        #Grid coordinates of buttons((x),(y))
        self.coords = [[5,844],[200,300,400]]
        #Text Variables
        bTvar = ctk.StringVar(value = "0°C")
        bCvar = ctk.StringVar(value = "0%")
        mTvar = ctk.StringVar(value = "0°C")
        pOvar = ctk.StringVar(value = "0 kW")
        aCvar = ctk.StringVar(value = "0 m/s²")
        aPvar = ctk.StringVar(value = "0 m/s²")#zero between runs with the gps home button
        speed_val = ctk.StringVar(value="0 KM/H")
        self.varNames = [mTvar,bTvar,bCvar,pOvar,aCvar,aPvar,speed_val]
        self.yoffset = 50 #change the y value of the brake, accelerator and speedometer

    def telemetry_make(self):
        #loop to draw all the buttons and labels
        #Frame for left side data
        self.telLeft = ctk.CTkFrame(master=root,width=175,height=335,border_width=0,
                                    fg_color="transparent",border_color="#FFFFFF",corner_radius=0)
        self.telLeft.grid(row=2,column=1,padx=5,pady=5)
        
        self.telNames = []
        #Frame for right side data
        self.telRight = ctk.CTkFrame(master=root,width=175,height=335,border_width=0,
                                    fg_color="transparent",border_color="#FFFFFF",corner_radius=0)
        self.telRight.grid(row=2,column=3,padx=5,pady=5)
        framedata = [self.telLeft, self.telRight] #Left and Right side data frames
        rowData = [(2,1,5,1),(4,1,5,1),(6,1,5,1),(2,3,5,1),(4,3,5,1),(6,3,5,1)] #row,column,padx,pady
        for i in range(len(self.telLabels)):
            newlabel = ctk.CTkLabel(framedata[math.floor(i/3)], text=f'{self.telLabels[i]}',
                            text_color="#FFD239",fg_color="#1B1464",
                            width=175,height=50, font=LabelFont)
            newlabel.grid(row=rowData[i][0],column=rowData[i][1],padx=rowData[i][2],pady=rowData[i][3])

            newbutton = ctk.CTkButton(framedata[math.floor(i/3)], textvariable=self.varNames[i],
                        text_color="#FFD239",fg_color="#1B1464",
                        width=175,height=50, font=displayFont,
                        corner_radius=10, border_width=4,
                        border_color="#000000", bg_color="transparent",)
            newbutton.grid(row=rowData[i][0]+1,column=rowData[i][1],padx=rowData[i][2],pady=rowData[i][3])
            self.telNames.append(newbutton)
        #draw the error message button
        error = ctk.StringVar(value = "Initial Value")
        self.isError = False
        self.prevError = False
        self.errorMSG = ctk.CTkButton(root, textvariable=error,
                                text_color="black",fg_color='red',
                                width=800,height=60, font=WarningFont,
                                corner_radius=10, border_width=4,
                                border_color="#000000", bg_color="transparent")
        self.errorMSG.grid(row=1,column=1,columnspan=3,padx=5,pady=3)
        #Frame for middle elements
        self.telMid = ctk.CTkFrame(master=root,width=600,border_width=0,
                                    fg_color="transparent",border_color="#FFFFFF",corner_radius=0)
        self.telMid.grid(row=2,column=2,padx=5,pady=5, rowspan=2)
        #Draw the Accelerator position and the brake pressure
        accel_label = ctk.CTkLabel(self.telMid, text="Accelerator Position",
                        text_color="#FFD239",fg_color="#1B1464",
                        width=400,height=21, font=LabelFont)
        accel_label.grid(row=1,column=1,padx=5,pady=1)

        self.accel = ctk.CTkProgressBar(self.telMid, height=25, width=500,
                                        border_width=0,border_color="#000000",
                                        corner_radius=0,fg_color="#242424",
                                        progress_color="#FFD239",orientation="horizontal")
        self.accel.grid(row=2,column=1,padx=5,pady=1)
        self.accel.set(0)

        brake_label = ctk.CTkLabel(self.telMid, text="Brake Pressure",
                        text_color="#FFD239",fg_color="#1B1464",
                        width=400,height=21, font=LabelFont)
        brake_label.grid(row=4,column=1,padx=5,pady=1)
        
        self.brake = ctk.CTkProgressBar(self.telMid, height=25, width=500,
                                        border_width=0,border_color="#000000",
                                        corner_radius=0,fg_color="#242424",
                                        progress_color="#FFD239",orientation="horizontal")
        self.brake.grid(row=5,column=1,padx=5,pady=1)
        self.brake.set(0)

        #speedometer canvas and placement Note: canvas size/placement changes on different screen sizes for some reason?
        self.speed_frame = Frame(self.telMid,width=600, height=300, bd=0,bg="#1B1464",highlightthickness=0)
        self.speed_frame.grid(row=3,column=1,padx=5,pady=5)
        self.speed = Canvas(self.speed_frame, bd=0,bg="#1B1464",highlightthickness=0,width=600, height=300)
        self.speed.pack(side=TOP)
        #Speed digital readout is within the speedometer
        self.dig_speed = ctk.CTkLabel(self.speed_frame,textvariable=self.varNames[6], text_color="#FFD239",
                            fg_color="transparent", width=300,height=75,
                            font=speedFont,corner_radius=20)
        self.dig_speed.pack(side=BOTTOM)

        #Label that this is the endurance screen
        self.race = ctk.CTkLabel(root, text="HANDLING",
                                 text_color="#FFD239",fg_color="#1B1464",
                                 width=175,height=50, font=LabelFont)
        self.race.grid(row=3,column=1,padx=5,pady=3)

    # repeatedly called function for drawing the speedometer
    def draw_speed(self,speed,max_speed,gradations,velocity):
        speed.create_oval(0,0,600,600, fill="#242424",outline="")#grey outline of speedometer (600x600)
        speed.create_arc(25,25,575,575,extent = velocity,start = 180, fill="#FFD239",outline="")#Yellow speedometer (575x575)
        speed.create_oval(50,50,550,550, fill="#1B1464",outline="")#Inner Blue oval that covers the center of the other ovals (550x550)
        circle_center = [300,300]
        #Loop to draw gradations
        for i in range(int(max_speed/5)+1):
            angle = i*math.pi/((max_speed/5))
            xangle = math.cos(angle)
            yangle = -math.sin(angle)
            if (i*5)%gradations == 0:#major Dimension
                speed.create_line(circle_center[0]+299*xangle,circle_center[1]+299*yangle,
                                circle_center[0]+285*xangle,circle_center[1]+285*yangle,fill="#FFD239",width=4)
                
            else:#minor dimension
                speed.create_line(circle_center[0]+299*xangle,circle_center[1]+299*yangle,
                                circle_center[0]+290*xangle,circle_center[1]+290*yangle,fill="#FFD239",width=2)

#for Pitlane testing
                
class Testing:

    def __init__(self):
        #diagnosics Labels
        self.diaText = '''#Diagnostics
            #Motor Temp:\nBattery Temp:\nBattery Voltage:\nBattery Current:
           # LV Battery Voltage:\nMotor RPM:\nBSPD Status:
            #BPPS Status:\nTractive Status:\nFuses:\n
            '''

    def telemetry_make(self):
        self.Highlight = ctk.CTkTextbox(root,width = 500,height = 250,
                                       border_width=2,border_color="#000000",
                                       corner_radius=4,fg_color="#242424",
                                       font=diagnosticFont,
                                       text_color="#FFFFFF",wrap="word")
        self.Highlight.grid(row=0,column=0,pady=25,padx=6)
        self.Highlight.insert("0.0",text="Highlighted Data")

        self.canBox = ctk.CTkTextbox(root,width = 500,height = 250,
                                       border_width=2,border_color="#000000",
                                       corner_radius=4,fg_color="#242424",
                                       font=diagnosticFont,
                                       text_color="#FFFFFF",wrap="word")
        self.canBox.grid(row=1,column=0,pady=25,padx=6)
        self.canBox.insert("0.0",text="CAN Messages")

        self.diagnosticBox = ctk.CTkTextbox(root,width = 500,height = 550,
                                       border_width=2,border_color="#000000",
                                       corner_radius=4,fg_color="#242424",
                                       font=diagnosticFont,
                                       text_color="#FFFFFF",wrap="word")
        self.diagnosticBox.grid(row=0,rowspan=2,column=1,pady=25,padx=6)
        self.diagnosticBox.insert("0.0",text=self.diaText)
        ############################################################################

screenModes = [Endurance(),Handling(),Testing()] #list of screen classes
currentMode = 0 #current screen
tmp2 = 0
diagnosticVal = ["0","0","0","0","0",
                 "0","Good","Good","Enabled","Good"]#list of diagnostic Values
diagnosticLen = ["2.11","3.13","4.16","5.16",
                 "6.19","7.10","8.12",
                 "9.12","10.16","11.6"]#list of length of diagnostic labels


#################################################################################################
#while True:
#    speed = 0
#Final Version update loop
previousMode = 99
speed = 0
batt_temp=0
while True:
    
    if currentMode != previousMode:
        
        #screen.varNames[6].set(str(0)+" KM/H")#classes retain their values even after screen is changed
        previousMode = currentMode
        #Delete and redraw screen when changing the screen
        for widget in root.winfo_children():#clear screen
            widget.destroy()
            print("Child Killed")

        
        if not root.winfo_children():#Redraw screen
            print("Redraw on Switch")
            screen = screenModes[currentMode]
            screen.telemetry_make()
        
        root.update_idletasks()#update screen
        root.update()
        
    speed = speed +0.1
    batt_temp += 0.1
    if speed > 160: speed = 0
    if batt_temp > 70: batt_temp = 0
    #draw screen when not already drawn
    #if not root.winfo_children():
        #screen = screenModes[currentMode]
        #screen.telemetry_make()

    #Code for Endurance and Handling
    if currentMode != 2:
        screen.accel.set(0)#set accelerator position bar
        screen.brake.set(0)#set brake pressure bar

        velocity = -(speed/max_speed)*180 #convert speed to degrees
        screen.speed.delete("all") #clear canvas before re-drawing to save memory/speed
        screen.draw_speed(screen.speed,max_speed,gradations,velocity)
        
        #Set telemetry Values
        screen.varNames[1].set(str(int(batt_temp)) + "°C") #set battery temp
        screen.varNames[6].set(str(int(speed))+" KM/H") #set speed label
        
        if batt_temp < 35: #change label color for warning
            test = screen.telNames[1]
            test.configure(fg_color='#1B1464') #navy
        elif batt_temp >= 35 and batt_temp < 60 : #between 35 and 59
            test = screen.telNames[1]
            test.configure(fg_color='#d47a13') #orange
        else: 
            test = screen.telNames[1]
            test.configure(fg_color='Crimson') #red
        
    #Code for testing screen
    else:
        print("arrgh")
    
    '''
data_x = DataLogging()

#Update loop for testing
while True:
    
    #redraw the screen when mode is changed/on startup
    if not root.winfo_children():
        screen = screenModes[currentMode]
        screen.telemetry_make()
    
    #tmp = bTvar.get()
    #tmp = str(int(tmp[0:-2]) + 1) + "°C"
    #bTvar.set(tmp)
    #use this to hide error message box
    #errorMSG.configure(fg_color=test, text_color="#1B1464", border_color="#1B1464")

    #code to change the color of the telemetry buttons
    #test = telNames[0]
    #test.configure(fg_color='lime')
    
    #code for race screens here
    if currentMode !=2:
        #testing
        tmp = screen.accel.get() + 0.005
        if tmp >=1:
            tmp=0
        #end testing
        screen.accel.set(tmp)
        #testing
        tmp = screen.brake.get() + 0.005
        if tmp >=1:
            tmp=0
        #end testing
        screen.brake.set(tmp)
        #testing
        tmp = screen.varNames[1].get()
        tmp = str(int(tmp[0:-2]) + 1) + "°C"
        if int(tmp[0:-2]) >= 90:
            tmp = str(0) + "°C"
        if int(tmp[0:-2]) < 35: #change label color for warning
            test = screen.telNames[1]
            test.configure(fg_color='#1B1464') #navy
        elif int(tmp[0:-2]) >= 35 and int(tmp[0:-2]) < 60 :
            test = screen.telNames[1]
            test.configure(fg_color='#d47a13') #orange
        else: 
            test = screen.telNames[1]
            test.configure(fg_color='Crimson') #red

        screen.varNames[1].set(tmp)
        #end testing
        tmp=int(screen.varNames[6].get()[0:-5]) #testing this line only
        velocity = -(tmp/max_speed)*180 #convert speed to degrees
        screen.speed.delete("all") #clear canvas before re-drawing to save memory/speed
        screen.draw_speed(screen.speed,max_speed,gradations,velocity)
        #testing speedometer
        if tmp >= 160:
            tmp = 0
        else:
            tmp += 1
            #testing end
        screen.varNames[6].set(str(tmp)+" KM/H")

    #code for pitlane screen testing
    elif currentMode == 2:
        for val in range(len(diagnosticVal)):
            try:
                diagnosticVal[val] = str(int(diagnosticVal[val])-1)
            except:
                tmp=None
            finally:
                screen.diagnosticBox.delete(diagnosticLen[val],diagnosticLen[val].partition(".")[0]+".end")#delete previous value
                screen.diagnosticBox.insert(diagnosticLen[val],text=diagnosticVal[val])#write next value

        #code to cycle the screens for testing
        if tmp2 >= 160:
            tmp2=0
        else:
            tmp2 +=1
    '''
    time.sleep(0.01) #here to limit the update rate for testing
    
    root.update_idletasks()
    root.update()
