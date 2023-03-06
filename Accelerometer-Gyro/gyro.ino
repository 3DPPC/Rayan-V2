#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <SD.h>

//global variables
const int chipSelect = 10; //port connected to SD data
Adafruit_MMA8451 mma = Adafruit_MMA8451();
unsigned long myTime; //to keep track of time
unsigned long MAXTIME = 30000; //max time to run
int blink_pin = 2; //pin to control led

void setup(void) {
  //setting up pins
  Serial.begin(9600);
  pinMode(blink_pin, OUTPUT);    // sets the digital pin 13 as output
  
  //setting up gyro
  Serial.println("INITIALIZING Adafruit MMA8451!!");
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  mma.setRange(MMA8451_RANGE_2_G);

  //setting up SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {   // see if the card is present and can be initialized:
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  //marking in the file when data starts
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println("\n----STARTING DATA COLLECTION----");
    dataFile.close();
  }
}

void loop() {
  //keeping track of time
  myTime = millis();
  if (myTime < MAXTIME) {
    collect_data();
  }
  //once data collection is completed blink led and stop data collection
  else {
    blink_led();
    Serial.println("ENDED DATA COLLECTION");
  }
  delay(10);
}

//blinks an led at 1hz
void blink_led() {
  digitalWrite(blink_pin, HIGH); // sets the digital pin 13 on
  delay(1000);            // waits for a second
  digitalWrite(blink_pin, LOW);  // sets the digital pin 13 off
  delay(1000);            // waits for a second
}

void collect_data() {
  //-----getting sensor data--------
  mma.read();   // Read the 'raw' data in 14-bit counts
  /* Get the orientation of the sensor */
  uint8_t o = mma.getOrientation();
  String direct = "";
  
  switch (o) {
    case MMA8451_PL_PUF: 
      direct = ("Portrait Up Front");
      break;
    case MMA8451_PL_PUB: 
      direct = ("Portrait Up Back");
      break;    
    case MMA8451_PL_PDF: 
      direct = ("Portrait Down Front");
      break;
    case MMA8451_PL_PDB: 
      direct = ("Portrait Down Back");
      break;
    case MMA8451_PL_LRF: 
      direct = ("Landscape Right Front");
      break;
    case MMA8451_PL_LRB: 
      direct = ("Landscape Right Back");
      break;
    case MMA8451_PL_LLF: 
      direct = ("Landscape Left Front");
      break;
    case MMA8451_PL_LLB: 
      direct = ("Landscape Left Back");
      break;
  }

  /* Get a new sensor event */ 
  sensors_event_t event; 
  mma.getEvent(&event);
  
  // preparing to write to file -----------------------------------
  String dataString = String(mma.x) + "," + String(mma.y) + "," + String(mma.z) + "," + String(event.acceleration.x) + "," + String(event.acceleration.y) + "," + String(event.acceleration.z) + "," + direct;
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}