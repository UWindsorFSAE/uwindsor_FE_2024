// Sqlite_CRUD_Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Should be configured for RPi cuz it runs with bare g++ terminal command {"g++ Sqlite_CRUD_Tutorial.cpp -o sqlite_demo -lsqlite3"}
// The RPi needs to have sqlite downloaded using the commands 
/*
sudo apt-get update
sudo apt-get install sqlite3 libsqlite3-dev
sqlite3 --version
*/
// It needs 1 file along with this one called sqlite3.h. it needs to be in the same directory


#include <iostream>
#include <stdio.h>
#include <sstream> 
#include <sqlite3.h>
#include "sqlite3.h"
#include <filesystem>


//#include <cstdio>
//#include <wiringPi.h>

using namespace std;


const char* DBDir; // change this directory to where ever you want the database to be created/saved

static int createDBIfMissing();
static int createTablesIfMissing();
static int addDefaultValuesIntoTable();
static int insertValuesIntoDB(string SensorID, double sensorValue);
static int onlyFunctionThatTalksToDB(const char* purpose, const char* sqlQuerryToExecute);
static int initializeDatabase();
static int testDB();



int main(int arge, char* argv[])
{
    string path = argv[0];
	path = path.substr(0, path.find_last_of("\\"));
    //path = path.substr(0, path.find_last_of("\\"));
    //path = path.substr(0, path.find_last_of("\\"));
	string DBName = "\\LoggedData.db";
    path.append(DBName);
	cout << "Path of the DB: " << path << endl;
	DBDir = path.c_str();

    initializeDatabase();

    testDB();


    cout << "Hello World!" << endl;
    
}

static int initializeDatabase() {
    
    createDBIfMissing();
    createTablesIfMissing();
    addDefaultValuesIntoTable();

    return 0;

}

static int createDBIfMissing() {

    onlyFunctionThatTalksToDB( "creating a databse" , NULL);

    return 0;
 
}

static int testDB(){

    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    insertValuesIntoDB("SPEED", 15);
    return 0;

}

static int createTablesIfMissing() {
    
   
    //now pass in the SQL querry. This is going to be the tables we need added if they are not already there
    string sqlQuerryEvents =
        "PRAGMA foreign_keys = ON;"// Makes sure that the ENUM values are enforced (Makes sure the EventType falls under one of the divided catergories)

        "CREATE TABLE IF NOT EXISTS EVENT_TYPE_LIST("
        "Type CHAR(5) PRIMARY KEY NOT NULL,"//This is going to be the event code for each different 
        "Seq INTEGER);"

        "CREATE TABLE IF NOT EXISTS DATALOG(" //Name of the table is datalog                

        "ENTRYID    INTEGER PRIMARY KEY AUTOINCREMENT, "// Basically how we are going to be orgaizing this DB - As data gets logged they get their unique ID
        "EVENTTYPE  CHAR(5) NOT NULL DEFAULT 'UNKWN' REFERENCES EVENT_TYPE_LIST(Type),"
        "EVENTDATA  REAL,"
        "TIMESTAMP  DATETIME NOT NULL DEFAULT (strftime('%Y-%m-%d %H:%M:%f', 'now', 'localtime'))"

        ");";

    onlyFunctionThatTalksToDB("Adding Tables (Event types and Data Log)" , sqlQuerryEvents.c_str());


    return 0;

}

static int addDefaultValuesIntoTable() {

    string sqlQuerryAddIntoEvents =
        "	INSERT OR REPLACE INTO EVENT_TYPE_LIST  (Type, Seq) VALUES "
        "    (  'UNKWN' ,00	)   "
        "   ,(	'SPEED' ,5	)   "  
        "	,(	'MOTMP'	,10	)	"
        "	,(	'CLT1T'	,15	)	"
        "	,(	'CLT2T'	,20	)	"
        "	,(	'CLT3T'	,25	)	"
        "	,(	'CLFLR'	,30	)	"
        "	,(	'MOTCR'	,35	)	"
        "	,(	'HVVLT'	,40	)	"
        "	,(	'HVTMP'	,45	)	"
        "	,(	'LVTMP'	,50	)	"
        "	,(	'LONG_'	,55	)	"
        "	,(	'LAT__'	,60	)	"
        "	,(	'YAW__'	,65	)	"
        "	,(	'PITCH'	,70	)	"
        "	,(	'ROLL_'	,75	)	"
        "	,(	'ACC_X'	,80	)	"
        "	,(	'ACC_Y'	,85	)	"
        "	,(	'ACC_Z'	,90	)	"
        "	,(	'MGN_X' ,95	)	"
        "	,(	'MGN_Y'	,100)	"
        "	,(	'MGN_Z'	,105)	"
        "	,(	'MAX_A'	,110)	"
        "	,(	'TOPSP'	,115)	"
        "	,(	'LAP_T'	,120)	"
        "	,(	'DRI_M'	,125);	";


    onlyFunctionThatTalksToDB( "Adding pre-requisite data into Event Type List", sqlQuerryAddIntoEvents.c_str());

    return 0;

}

static int insertValuesIntoDB(string SensorID, double sensorValue) {

    string sqlQuerryAddIntoLogData =
        "	INSERT INTO DATALOG  (EVENTTYPE, EVENTDATA) VALUES ('" + SensorID + "'," + to_string(sensorValue) + ");";

    onlyFunctionThatTalksToDB("Inserting values into DataLog DB", sqlQuerryAddIntoLogData.c_str());

    return 0;

}

static int onlyFunctionThatTalksToDB( const char* taskBeingPerformed, const char* sqlQuerryToExecute) {

    sqlite3* DB;

    if (sqlQuerryToExecute == NULL) {

        int exit = 0;
        exit = sqlite3_open(DBDir, &DB);
        cout << "DB Exists Now" << endl;

    }
    else {

        char* zErrMsg;
        int exit = sqlite3_open(DBDir, &DB);
        int rc = sqlite3_exec(DB, sqlQuerryToExecute, NULL, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            cerr << "Error talking to Database while performing: " << taskBeingPerformed << endl;
            cout << zErrMsg;
            sqlite3_free(zErrMsg);
        }
        else {
            cout << "Sucessflly modifed the databse for: " << taskBeingPerformed << endl;
        }
    }

    sqlite3_close(DB);

    return 0;

}
