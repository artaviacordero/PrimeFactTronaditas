#ifndef FACTORIZADOR_HPP
#define FACTORIZADOR_HPP

#include <cinttypes>

#include "common/Consumer.hpp"
#include "common/Queue.hpp"

#include "CalculadoraFactores.hpp"
#include "Factorizacion.hpp"

/**
 * @brief Calcula los factores de una Factorizacion
 */
class Factorizador : public Consumer<Factorizacion*> {
 private:
  /**
   * @brief Calculadora que usará el Factorizador para calcular los factores
   */
  CalculadoraFactores calculadora;

  /**
   * @brief Cola donde se consumen las factorizaciones pendientes
   */
  Queue<Factorizacion*>* factorizacionesPendientes = nullptr;

  /**
   * @brief Cola en la que insertar las factorizaciones listas
   */
  Queue<Factorizacion*>* factorizacionesListas = nullptr;

  /**
   * @brief Inserta una factorización en cola produccion
   * 
   * @param factorizacion Factorización lista para insertar en la cola
   */
  void produce(Factorizacion* factorizacion);

  /**
   * @brief Consume una factorizacióny le calcula sus factores
   * 
   * Recibe una factorización de la cola de factorizaciones pendientes y
   * la envía a CalculadoraFactores::calculaFactores
   * 
   * @param factorizacion Factorización pendiente a procesar
   */
  virtual void consume(Factorizacion* factorizacion);

  /**
   * @brief Inicial el ciclo consumeForever de la clase Consumer
   * @return retorna un entero, siempre es 0
   */
  virtual int run();

 public:
  /**
   * @brief Constructor
   * 
   * @param factorizacionesPendientes Cola de factorizaciones pendientes
   * @param factorizacionesListas Cola de factorizaciones listas
   * @param stop Condición para detener consumeForever
   */
  Factorizador(Queue<Factorizacion*>* factorizacionesPendientes,
    Queue<Factorizacion*>* factorizacionesListas, Factorizacion* stop);

  /**
   * @brief Destructor
   */
  ~Factorizador();
};


#endif  // FACTORIZADOR_HPP
