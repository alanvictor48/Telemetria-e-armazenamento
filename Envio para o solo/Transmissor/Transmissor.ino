#include <SPI.h>
#include <RF24.h>

// Pinos CE e CSN
RF24 radio(7, 8);

const byte endereco[6] = "teste";

void setup() {
  // Inicializa a comunicação com o modulo
  radio.begin();

  // Define o endereço do transmissor
  radio.openWritingPipe(endereco);

  // Prepara para o modo de envio
  radio.stopListening();
}

void sendMessage(float altitude, float temperature, float acelerometer) {
  char content[50];
  sprintf(content, "%f, %f, %f\n", altitude, temperature, acelerometer);
  
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
  sendMessage(altitude(), temperature(), acelerometer());
}
