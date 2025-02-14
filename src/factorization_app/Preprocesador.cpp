#include <stdexcept>
#include <cinttypes>
#include <sstream>

#include "Preprocesador.hpp"

/*
 * CONSTRUCTOR/DESTRUCTOR
*/

Preprocesador::Preprocesador(Queue<Trabajo*>* trabajosPendientes,
  Queue<Factorizacion*>* factorizacionesPendientes,
  Queue<Factorizacion*>* factorizacionesListas,
  Trabajo* stop) : Consumer(stop) {
    this->trabajosPendientes = trabajosPendientes;
    this->queueConsumer = trabajosPendientes;
    this->factorizacionesPendientes = factorizacionesPendientes;
    this->factorizacionesListas = factorizacionesListas;
}

Preprocesador::Preprocesador() : Consumer(nullptr) {
    this->trabajosPendientes = nullptr;
    this->factorizacionesPendientes = nullptr;
    this->factorizacionesListas = nullptr;
}

Preprocesador::~Preprocesador() {
}


/*
 * MÉTODOS PUBLICOS
*/

void Preprocesador::produce(Factorizacion* factorizacion) {
  assert(this->factorizacionesPendientes);
  assert(this->factorizacionesListas);
  // Inserta las factorizaciones válidas en la cola de factorizaciones
  // pendientes. Una factorización válida es aquella que tiene un número
  // mayor o igual a 2. SI la factorizacion no es válida la inserta a la
  // cola de factorizaciones listas
  if (factorizacion->obtieneNumero() >= 2) {
    this->factorizacionesPendientes->push(factorizacion);
  } else {
    this->factorizacionesListas->push(factorizacion);
  }
}

void Preprocesador::consume(Trabajo* trabajo) {
  if (trabajo != this->stopCondition) {
    // Hace split a los tokens separados por ,
    std::stringstream entrada(trabajo->datosIngresados);
    std::vector<std::string> tokens = this->split(entrada);

    // Crea una Factorización para cada token y la inserta en el vector
    // de fatorizaciones del trabajo.
    for (size_t index = 0; index < tokens.size(); ++index) {
      Factorizacion* factorizacion = new Factorizacion(tokens[index], trabajo);
        trabajo->factorizaciones.push_back(factorizacion);
    }

    // Inserta las factorizaciones válidas en la cola de factorizaciones
    // pendientes. Una factorización válida es aquella que tiene un número
    // mayor o igual a 2.
    for (size_t index = 0; index < trabajo->factorizaciones.size(); ++index) {
      // Inserta las factorizaciones a sus respectivas colas
      this->produce(trabajo->factorizaciones[index]);
    }
  } else {
    // Termina el ciclo consumeForever
    this->done = true;
  }
}

std::vector<std::string> Preprocesador::split(std::stringstream& entrada) {
  // Busca tokens en el string con los datos del usuario (split)
  // Inserta en el vector tokens cada dato y retorna el vector
  std::string token;
  std::vector<std::string> tokens;
  while (std::getline(entrada, token, ',')) {
    tokens.push_back(token);
  }

  return tokens;
}

int Preprocesador::run() {
  this->consumeForever();
  return 0;
}
