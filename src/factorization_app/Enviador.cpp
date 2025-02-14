#include <string>

#include "Enviador.hpp"

Enviador::Enviador(Queue<Trabajo*>* trabajosListos, Trabajo* stop) :
  Consumer(stop) {
  this->trabajosListos = trabajosListos;
  this->queueConsumer = trabajosListos;
}

Enviador::~Enviador() {}

void Enviador::consume(Trabajo* trabajo) {
  // Si el trabajo es diferente a la condicion de parada envia la respuesta
  if (trabajo != this->stopCondition) {
    // Envía la respuesta
    trabajo->respuesta.send();

    // Cierra el socket
    trabajo->respuesta.getSocket().close();

    // Borra el trabajo
    delete trabajo;
  } else {
    // Termina el ciclo consumeForever
    this->done = true;
  }
}

int Enviador::run() {
  this->consumeForever();
  return 0;
}
