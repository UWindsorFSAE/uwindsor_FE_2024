import sqlite3
import random
import time

connection = sqlite3.connect("fsae.db")

cursor = connection.cursor()
#cursor.execute("CREATE TABLE fsae_database (Date TEXT, Time TEXT, Parameter TEXT, Value INTEGER )")

table_schema = '''
    CREATE TABLE IF NOT EXISTS telemetry_data (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        Speed REAL,
        MotorTemperature REAL,
        CoolantTemperature REAL,
        CoolantFlowRate REAL,
        MotorCurrent REAL,
        BatteryVoltage REAL,
        BatteryTemperature REAL,
        LVBatteryVoltage REAL,
        GPSLocation TEXT,
        Acceleration3Axis TEXT,
        Direction3Axis TEXT,
        LapTime REAL
    );
'''
cursor.execute(table_schema)

# Function to generate simulated GPS data
def generate_gps_data():
    latitude = random.uniform(-90, 90)
    longitude = random.uniform(-180, 180)
    return "Latitude: {}, Longitude: {}".format(latitude, longitude)

# Function to generate simulated acceleration data
def generate_acceleration_data():
    acceleration_x = random.uniform(-5, 5)
    acceleration_y = random.uniform(-5, 5)
    acceleration_z = random.uniform(-5, 5)
    return "X: {}, Y: {}, Z: {}".format(acceleration_x, acceleration_y, acceleration_z)

# Function to generate simulated magnetic field data
def generate_magnetic_field_data():
    magnetic_x = random.uniform(-1, 1)
    magnetic_y = random.uniform(-1, 1)
    magnetic_z = random.uniform(-1, 1)
    return "X: {}, Y: {}, Z: {}".format(magnetic_x, magnetic_y, magnetic_z)

# Main loop to read sensor data and insert into database
while True:
    # Simulate sensor readings
    gps_data = generate_gps_data()
    acceleration_data = generate_acceleration_data()
    magnetic_field_data = generate_magnetic_field_data()

    # Insert data into the database
    cursor.execute('''INSERT INTO telemetry_data 
                    (GPSLocation, Acceleration3Axis, Direction3Axis) 
                    VALUES (?, ?, ?)''', (gps_data, acceleration_data, magnetic_field_data))
    
    # Commit the transaction
    connection.commit()

    # Print confirmation message
    print("Data inserted successfully.")

    # Delay between readings (adjust as needed)
    time.sleep(1)

# Close connection when done (This part will not be reached in an infinite loop)
connection.close()