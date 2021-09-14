#include <SPI.h>
#include <RF24.h>

// LED para teste
// Acende quando o paraquedas for ativado
#define LED 4

// Pinos CE e CSN
RF24 radio(7, 8);
boolean releaseParachute = false;

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  // Inicializa a comunicação com o modulo
  radio.begin();

  // Define o endereço do transmissor
  radio.openWritingPipe(endereco[0]);
  radio.openReadingPipe(1, endereco[1]);

  // Prepara para o modo de envio
  radio.stopListening();
}

void sendMessage(float time, float altitude, float temperature, float acelerometer) {
  char content[50];
  sprintf(content, "%.3f, %.3f, %.3f, %.3f\n", time, altitude, temperature, acelerometer);
  
  radio.write(&content, sizeof(content));
}

float altitude() {
  return 10.5;
}

float temperature() {
  return 21;
}

float acelerometer() {
  return 31.5;
}

void loop() {
  sendMessage(millis() / 1000.0, altitude(), temperature(), acelerometer());

  radio.startListening();
  if(radio.available()) {
    radio.read(&releaseParachute, sizeof(boolean));

    if(releaseParachute) {
      digitalWrite(LED, HIGH);
    }
  }
  radio.stopListening();
}
