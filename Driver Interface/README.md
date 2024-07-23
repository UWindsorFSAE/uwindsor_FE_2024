# FSAE-HMI-2024
Code for main driver screen, datalogging and VCU controls

## Data Aquired/Stored
- Speed (calcuated from motor RPM and gear ratio on VCU)
- Motor temperature
- Coolant Temperature (3x Thermocouple)
- Coolant Flow Rate
- Motor current
- Battery Voltage
- Battery Temperature
- LV Battery Voltage
- GPS Location (logitude, Latitude)
- Acceleration 3-axis (Yaw, Pitch, Roll)
- Direction 3-axis (X, Y, Z)
- Max Acceleration (Handling Events only)
- Top Speed (Reset from function button)
- Drive mode (Drive or Neutral)
- Lap time (endurance only)

## How It Works
#### Main_Screen.py
The screen is connected to a Raspberry Pi (henceforth Rpi) by HDMI that is under the dash. The Rpi is connected to the CAN bus over spi that is level shifted to 5V. The CAN bus is connected to the VCU directly. This script recieves all sensor data from the VCU and logs the data to the database along with a unique id and timestamp. This script also handles the switch screen button and the screen function button (reset). Additionally, this code calculates the top speed, lap time, max acceleration, battery charge %, power and lap power (avg power for the lap*lap time -> kWh) from the data it recieves.
#### VCU Code
This code interfaces with the HV CAN loop to collect data from the inverter, BMS and motor over CAN. It also handles the interrupt for the Drive/Neutral button + LED. All Sensor data will be collected by the VCU and sent to the Raspberry Pi over a seperate CAN loop. The VCU will interface with the I2C bus over differential I2C, which will be connected to the 3x thermocouples, GPS, Accelerometer/Gyroscope and Magnetometer. The VCU will also control 4 relays and a number of GPIOs/ADCs will be used to collect analog sensor data and send signals. Additionally, there will be safety stop parameters that will either trigger the shutdown circuit or put the car into neutral. These parameters include max battery temp (each set of parallel cells has a thermistor, the highest measured temp should be less than the shutdown value), motor temp, brake pressure (significantly below default value).
#### Unmade-file.py
This file converts the data from the database to different graphs and an excel or csv file(undecided) and saves the files to the SD Card. A USB stick can be plugged into the Rpi to copy the data over.

## Libraries
| Library | Usage |
|---------|-------|
|Tkinter and customTkinter | Screen & UI |
|sqlite3 | Database Interfacing |
|adafruit-circuitpython-lsm6ds | Accelerometer and Gyroscope |
|adafruit-circuitpython-gps | GPS Module |
|adafruit-circuitpython-mmc56x3 | Magnetometer |
|RPi.GPIO | Raspberry Pi's GPIO & Interrupts |

See library documentation for information on how to use

# VCU Pinout
### Description
This file contains the pinout of each pin, extra functions and any other useful info  (voltage divider, level shifter, etc.) **All ADC voltage dividers are input voltage x0.6, and all level shifters are 5v to 3.3v bi-directional.**
### Left I/O Connector (20pin)
From top to bottom of connector
| Pin number | Function | MCU PIN | Notes |
| -- | -- | -- | -- |
| 1 | ADC15 | PF6 | x0.6 voltage divider |
| 2 | ADC14 | PF7 | x0.6 voltage divider |
| 3 | GP10 | PA15 | 5V to 3.3V level shifter |
| 4 | ADC13 | PA0 | x0.6 voltage divider |
| 5 | ADC12 | PA1 | x0.6 voltage divider |
| 6 | CAN1 Low | N/A ||
| 7 | CAN1 High | N/A ||
| 8 | ADC11 | PC1 | x0.6 voltage divider |
| 9 | GP11 | PD4 | 5V to 3.3V level shifter |
| 10| GP12 | PD3 | 5V to 3.3V level shifter |
| 11| GP13 | PD5 | 5V to 3.3V level shifter |
| 12| GP14 | PD6 | 5V to 3.3V level shifter |
| 13| GP17 | PD7 | 5V to 3.3V level shifter |
| 14| GP16 | PE3 | 5V to 3.3V level shifter |
| 15| GP15 | PE4 | 5V to 3.3V level shifter |
| 16| ADC10 | PF8 | x0.6 voltage divider |
| 17| ADC9 | PF9 | x0.6 voltage divider |
| 18| GP18 | PE6 | 5V to 3.3V level shifter |
| 19| GP19 | PG9 | 5V to 3.3V level shifter |
| 20| GP20 | PG15 | 5V to 3.3V level shifter |

### Right I/O Connector (20pin)
From top to bottom of connector
| Pin number | Function | MCU Pin | Notes |
| -- | -- | -- | -- |
| 1 | GP1 | PB8 | 5V to 3.3V level shifter |
| 2 | GP2 | PC6 | 5V to 3.3V level shifter |
| 3 | GP3 | PB9 | 5V to 3.3V level shifter |
| 4 | ADC2 | PA6 | x0.6 voltage divider |
| 5 | ADC3 | PA7 | x0.6 voltage divider |
| 6 | GP4 | PB12 | 5V to 3.3V level shifter |
| 7 | ADC1 | PB1 | x0.6 voltage divider |
| 8 | GP5 | PB15 | 5V to 3.3V level shifter |
| 9 | GP6 | PB14 | 5V to 3.3V level shifter |
| 10 | PA5 | PA5 | Bare Pin, MAX 3.3V
| 11 | CAN2 High | N/A ||
| 12 | CAN2 Low | N/A ||
| 13 | GP7 | PB13 | 5V to 3.3V level shifter |
| 14 | ADC4 | PC4 | x0.6 voltage divider |
| 15 | ADC5 | PF5 | x0.6 voltage divider |
| 16 | ADC6 | PF4 | x0.6 voltage divider |
| 17 | ADC7 | PF10 | x0.6 voltage divider |
| 18 | GP8 | PD12 | 5V to 3.3V level shifter |
| 19 | GP9 | PD11 | 5V to 3.3V level shifter |
| 20 | ADC8 | PF3 | x0.6 voltage divider |

### Differential I2C Connectors (2x2pin, bottom right)
From left to right
| Pin number | Function | MCU Pin | Notes |
| -- | -- | -- | -- |
| 1 | DSDA- | N/A ||
| 2 | DSDA+ | N/A ||
| 3 | DSCL+ | N/A ||
| 4 | DSCL- | N/A ||
| N/A | SDA | PF0 ||
| N/A | SCL | PF1 ||

### Relay Control Connectors (4x2pin, bottom left)
From left to right
| Pin number | Function | MCU Pin | Notes |
| -- | -- | -- | -- |
| 1 | Relay 1+ | PG12 | MCU controls MOSFET |
| 2 | Relay 1- |||
| 3 | Relay 2+ | PG11 | MCU controls MOSFET |
| 4 | Relay 2- |||
| 5 | Relay 3+ | PG13 | MCU controls MOSFET |
| 6 | Relay 3- |||
| 7 | Relay 4+ | PG10 | MCU controls MOSFET |
| 8 | Relay 4- |||

### CAN and LV battery voltage measurement
No direct connection to a terminal, 12V goes through a schottky diode with forward voltage that depends on current draw (~0.4V @ 1A)
| Function | MCU Pin | Notes |
| -- | -- | -- |
| LV Battery ADC | PC5 | Voltage divider = Input x 0.25 - 1.4 |
| CAN 1 TX | PD1 ||
| CAN 1 RX | PD0 | Optically Isolated|
| CAN 2 TX | PB6 ||
| CAN 2 RX | PB5 | Optically Isolated|