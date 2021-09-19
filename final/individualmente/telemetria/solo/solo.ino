#include <SPI.h>
#include <RF24.h>

// Pinos CE e CSN
RF24 radio(7, 8);
char releaseParachute[2] = "0";

uint8_t count = 0;

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);

  // Inicia a comunicação com o modulo
  radio.begin();

  // Define o endereço do receptor (data pipe 0)
  // Define o endereço do transmissor
  radio.openWritingPipe(endereco[1]);
  radio.openReadingPipe(1, endereco[0]);

  // Entra no modo de envio
  radio.stopListening();
}

void loop() {

  switch(count){
    case 0:
      releaseParachute[0] = '0';
      break;
    case 1:
      releaseParachute[0] = '1';
      break;
  }
  count = (count+1) % 2;
  
  // int transmitidoERecebido = radio.write(&releaseParachute, sizeof(releaseParachute));
  // if(transmitidoERecebido) {
  //   Serial.println(transmitidoERecebido);
  // }
  
  radio.write(&releaseParachute, sizeof(releaseParachute));
  delay(2000);
}

