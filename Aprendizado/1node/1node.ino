#include <SPI.h>
#include <RF24.h>

#define radioID 0

// Pinos CE e CSN
RF24 radio(7, 8);

const byte endereco[0][6] = {"1node", "2node"};
int dadoDeEnvio, dadosRecebidos;

void setup() {

  // Define como sera a comunicaçao
  #if radioID == 0
    radio.openWritingPipe(endereco[0]);
    radio.openReadingPipe(1, endereco[1]);
  #else
    radio.openWritingPipe(endereco[1]);
    radio.openReadingPipe(1, endereco[0]);
  #endif
  
  // Os dois aparelhos ficarao o estado de "escuta"
  radio.startListening();
}

void loop() {
  dadoDeEnvio = 255;
  
  radio.stopListening();
  radio.write(&dadoDeEnvio, sizeof(int));
  radio.startListening();

  if(radio.available()) {
    radio.read(&dadosRecebidos, sizeof(int));
  }
}
