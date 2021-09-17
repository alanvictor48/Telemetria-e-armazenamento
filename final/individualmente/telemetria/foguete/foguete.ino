#include <SPI.h>
#include <RF24.h>
#include <SD.h>

// LEDs para teste
#define LED0 4
#define LED1 2

// Pinos CE e CSN
RF24 radio(7, 8);
char releaseParachute[1] = "0";

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  Serial.begin(9600);

  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);

  // Inicializa a comunicação com o modulo de rádio
  radio.begin();

  // Define o endereço do transmissor
  radio.openWritingPipe(endereco[0]);
  radio.openReadingPipe(1, endereco[1]);

  radio.startListening();
}

void loop() {

  if(radio.available()) {
    radio.read(&releaseParachute, sizeof(releaseParachute));

    if (releaseParachute[0] == '0'){
      Serial.println("Ligando Led 0!");
      digitalWrite(LED0, HIGH);
      digitalWrite(LED1, LOW);
    } else if(releaseParachute[0] == '1') {
      Serial.println("Ligando Led 1!");
      digitalWrite(LED1, HIGH);
      digitalWrite(LED0, LOW);
    }
  }
}
