/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
  SD card attached to SPI bus as follows:
  
   ** MOSI - pin 11
   ** MISO - pin 12
   ** CLK - pin 13
   ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  The model file wil be:

  Time, Altitude, Temperature, Acelerometer
  10, 10, 10, 10
  
*/

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
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

void writeOnSD(float time, float altitude, float temperature, float aceleracao, File file) {
  char string[40];
  file = SD.open("data.txt", FILE_WRITE);
  
  if(file) {
    Serial.print("Writing...");

    sprintf(string, "%.3f, %.3f, %.3f, %.3f\n", time, altitude, temperature, aceleracao);
    
    file.print(string);
    file.close();

    Serial.println("Done.");
  } else {
    Serial.println("Error opening data.txt");
  }
}

float altitude() {
  return 402.1;
}

float temperature() {
  return 42.1;
}

float acelerometer() {
  return 42.1;
}

void loop() {
  writeOnSD(millis() / 1000.0, altitude(), temperature(), acelerometer(), myFile);
  delay(1000);
}