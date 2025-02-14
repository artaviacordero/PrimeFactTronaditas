#include "Factorizador.hpp"

/*
 * CONSTRUCTOR/DESTRUCTOR
*/

Factorizador::Factorizador(Queue<Factorizacion*>* factorizacionesPendientes,
                          Queue<Factorizacion*>* factorizacionesListas,
                          Factorizacion* stop) : Consumer(stop) {
  this->factorizacionesPendientes = factorizacionesPendientes;
  this->factorizacionesListas = factorizacionesListas;
  this->queueConsumer = factorizacionesPendientes;
}

Factorizador::~Factorizador() {}

/*
 * MÉTODOS PRIVADOS
*/

void Factorizador::consume(Factorizacion* factorizacion) {
  if (factorizacion != this->stopCondition) {
    // Calcula los factores para el número de la factorización
    calculadora.calculaFactores(*factorizacion);
    this->produce(factorizacion);
  } else {
    // Termina el ciclo consumeForever
    this->done = true;
  }
}

void Factorizador::produce(Factorizacion* factorizacion) {
  assert(this->factorizacionesListas);
  this->factorizacionesListas->push(factorizacion);
}

int Factorizador::run() {
  this->consumeForever();
  return 0;
}
