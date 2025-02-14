#include "ClienteEnviador.hpp"

ClienteEnviador::ClienteEnviador(Queue<ClienteGenerador*>* clientesListos,
    ClienteGenerador* stop) : Consumer(stop) {
  this->queueConsumer = clientesListos;
}

ClienteEnviador::~ClienteEnviador() {
}

int ClienteEnviador::run() {
  this->consumeForever();
  return 0;
}

void ClienteEnviador::consume(ClienteGenerador* cliente) {
  if (cliente != this->stopCondition) {
    // Envía la respuesta al usuario
    cliente->trabajo->respuesta.send();

    // Mata el hilo generador y lo borra
    cliente->waitToFinish();
    delete cliente;
  } else {
    this->done = true;
  }
}
