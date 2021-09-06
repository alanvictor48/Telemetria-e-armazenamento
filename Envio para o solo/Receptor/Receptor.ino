#include <SPI.h>
#include <RF24.h>

// Pinos CE e CSN
RF24 radio(7, 8);

const byte endereco[6] = "teste";

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);

  // Inicia a comunicação com o modulo
  radio.begin();

  // Define o endereço do receptor (data pipe 0)
  radio.openReadingPipe(0, endereco);

  // Entra no modo de recebimento
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char recebido[50] = "";

    // Se recebeu algum pacote, lê o conteudo na variável recebido
    radio.read(&recebido, sizeof(recebido));

    // Imprime o que foi recebido
    Serial.println(recebido);
  }
}
