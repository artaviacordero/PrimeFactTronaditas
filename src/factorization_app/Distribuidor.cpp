#include <chrono>
#include <random>

#include "Distribuidor.hpp"

Distribuidor::Distribuidor(Queue<Trabajo*>* trabajosPendientes,
  Queue<ClienteGenerador*>* clientesListos,
  Trabajo* stop) : Consumer(stop) {
  this->queueConsumer = trabajosPendientes;
  this->clientesListos = clientesListos;

  // Guarda los números de puertos en puertosHijos
  this->puertosDeHijos.push_back("8091");
  this->puertosDeHijos.push_back("8092");
  this->puertosDeHijos.push_back("8093");
  this->puertosDeHijos.push_back("8094");

  // Motor aleatorio para obtener puertos
  /*
  * Basado en: http://jeisson.ecci.ucr.ac.cr/concurrente/2020c/ejemplos/
  * source.php?file1=mpi/lucky_number_reduce/lucky_number_reduce.cpp
  */
  // Try to get a seed from hardware, if available
  std::random_device::result_type semilla = std::random_device()();

  // This object generates random numbers using the Mersenne-Twister algoritym
  auto tiempo = std::chrono::system_clock::now();
  this->motorAleatorio = std::mt19937(semilla
    + tiempo.time_since_epoch().count());
}

Distribuidor::~Distribuidor() {}

int Distribuidor::run() {
  this->consumeForever();
  return 0;
}

void Distribuidor::consume(Trabajo* trabajo) {
  if (trabajo != this->stopCondition) {
    // Obtiene el puerto del hijo al que mandar la solicitud
    std::string puerto = this->obtienePuertoAleatorio();

    // Crea un hilo ClienteGenerador
    ClienteGenerador* cliente = new ClienteGenerador(trabajo, this->servidor,
      puerto, this->clientesListos);

    // Arranca el hilo ClienteGenerador
    cliente->startThread();
  } else {
    this->done = true;
  }
}

std::string Distribuidor::obtienePuertoAleatorio() {
  // Distribución uniforme de enteros
  std::uniform_int_distribution<int> distribucion(0,
    this->puertosDeHijos.size() - 1);

  // Obtiene el puerto
  std::string ret = this->puertosDeHijos[distribucion(this->motorAleatorio)];

  return ret;
}
