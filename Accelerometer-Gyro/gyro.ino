#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <SD.h>

/* global variables */
const int chipSelect = 10;
Adafruit_MMA8451 mma = Adafruit_MMA8451();
//for keeping track of time
unsigned long curr_Time;
const unsigned long MAXTIME_COEFF = 30000;
unsigned long end_Time;

/* LED Pins */
const int MSB_LED = 2;
const int LSB_LED = 3;


/* Displays Current Divice mode using leds:
 *   0 0 == no power 
 *   0 1 == awaiting sd_card 
 *   1 0 == data being collected 
 *   1 1 == data collection complete
 */
void display_mode(bool led_1, bool led_2) {
  //first led
  if (led_1) {
    digitalWrite(MSB_LED, HIGH);
  }
  else {
    digitalWrite(MSB_LED, LOW);
  }

  //second led
  if (led_2) {
    digitalWrite(LSB_LED, HIGH);
  }
  else {
    digitalWrite(LSB_LED, LOW);
  }
}

/* Function that handles the time
 *  in between when the device is powered and
 *  the SD card is inserted
 */
void initialize_SD(){
   // dispplaying status
   Serial.print("Initializing SD card...");

  // waiting for the SD card to be inserted
  while (!SD.begin(chipSelect)) {
    //displaying current mode
    Serial.println("Card failed, or not present");
    display_mode(false, true);
    delay(10);
  }

  // updating state and max run time
  display_mode(true, false);
  end_Time = millis() + MAXTIME_COEFF; //factoring in current time to find end time
  
  // marking in file the beggining of data collection
  Serial.println("card initialized.");
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("\nBEGGINING DATA COLLECTION");
    dataFile.close();
  }
}

void setup(void) {
  /* setting up pins */
  Serial.begin(9600);
  pinMode(MSB_LED, OUTPUT);
  pinMode(LSB_LED, OUTPUT);
  
  /* Initializing Gyroscope */
  Serial.println("INITIALIZING Adafruit MMA8451!!");
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  mma.setRange(MMA8451_RANGE_2_G);

  /* Initializing LED */
  initialize_SD();
}

void loop() {
  //keeping track of time
  curr_Time = millis();
  if (curr_Time < end_Time) {
    collect_data();
    display_mode(true, false);
  }
  else {
    //data collection completed
    blink_2_led(MSB_LED, LSB_LED); //blinking 1 1
    Serial.println("ENDED DATA COLLECTION");
  }
  delay(10);
}

/* Blinks LED at 0.5hz */
void blink_2_led(int led_1, int led_2) {
  digitalWrite(led_1, HIGH); 
  digitalWrite(led_2, HIGH); 
  delay(1000);            
  digitalWrite(led_1, LOW); 
  digitalWrite(led_2, LOW);  
  delay(1000);            
}

/* Main Function to collect and record data */
void collect_data() {  //keeping track of time
  //getting sensor data
  // Read the 'raw' data in 14-bit counts
  mma.read();
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
