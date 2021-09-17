#include <SPI.h>
#include <RF24.h>
#include <SD.h>

// LEDs para teste
#define LED0 4

File myFile;

// Pinos CE e CSN
RF24 radio(7, 8);
bool releaseParachute;

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  Serial.begin(9600);

  pinMode(LED0, OUTPUT);
  digitalWrite(LED0, LOW);

  Serial.print("Initializing SD card...");
  while(!SD.begin(4)) {
    Serial.println("Initialization failed!");
    delay(100);
  }
  Serial.println("Initialization done.");

  // Se conectando com o cartão SD
  myFile = SD.open("data.txt", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing...");
    
    myFile.println("Time, Altitude, Temperature, Acelerometer\n");
    myFile.close();
    
    Serial.println("Done.");
  } else {
    Serial.println("Error opening data.txt");
  }
  // Inicializa a comunicação com o modulo de rádio
  radio.begin();

  // Define o endereço do transmissor
  radio.openWritingPipe(endereco[0]);
  radio.openReadingPipe(1, endereco[1]);

  // Prepara para o modo de envio
  radio.stopListening();
}

void sendMessage(float time, float altitude, float temperature, float acelerometer) {
  char content[40];
  
  sprintf(content, "%.3f, %.3f, %.3f, %.3f\n", time, altitude, temperature, acelerometer);
  
  radio.write(&content, sizeof(content));
}

float altitude() {
  return 100.5;
}

float temperature() {
  return 21;
}

float acelerometer() {
  return 31.5;
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

void loop() {
  float data[4];
  data[0] = millis() / 1000.0;
  data[1] = altitude();
  data[2] = temperature();
  data[3] = acelerometer();
  
  sendMessage(data[0], data[1], data[2], data[3]);

  radio.startListening();
  if(radio.available()) {
    radio.read(&releaseParachute, sizeof(releaseParachute));

    if(releaseParachute){
      Serial.println("Ligando Led 0!");
      digitalWrite(LED0, HIGH);
    }
  }
  radio.stopListening();

  writeOnSD(data[0], data[1], data[2], data[3]);
}
