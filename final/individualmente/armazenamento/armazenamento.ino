/*
  The model file will be:

  Time, Altitude, Temperature, Acelerometer
  42.1, 42.1, 42.1, 42.1
  
*/

#include <SPI.h>
#include <SD.h>

#define CS_PIN 10

File myFile;

void setup() {
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");

  
  myFile = SD.open("data.txt", FILE_WRITE);

  if(myFile) {
    Serial.print("Writing...");
    
    myFile.println("Time, Altitude, Temperature, Acelerometer");
    myFile.close();
    
    Serial.println("Done.");
  } else {
    Serial.println("Error opening data.txt");
  }
}

void writeOnSD(float time, float altitude, float temperature, float acelerometer) {
  char string[40];
  myFile = SD.open("data.txt", FILE_WRITE);
  
  if(myFile) {
    Serial.print("Writing...");

    sprintf(string, "%.3f, %.3f, %.3f, %.3f\n", time, altitude, temperature, acelerometer);
    
    myFile.print(string);
    myFile.close();

    Serial.println("Done.");
  } else {
    Serial.println("Error opening data.txt");
  }
}

float altitude() {
  return 42.1;
}

float temperature() {
  return 42.1;
}

float acelerometer() {
  return 42.1;
}

void loop() {
  writeOnSD(millis() / 1000.0, altitude(), temperature(), acelerometer());
  delay(1000);
}