#ifndef PREPROCESADOR
#define PREPROCESADOR

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "Consumer.hpp"
#include "Queue.hpp"
#include "Trabajo.hpp"

#include "Factorizacion.hpp"

/**
 * @brief Hace un 'split' de los datos ingresados por el cliente y genera
 * objetos Factorizacion a partir de ellos.
 * 
 * Procesa el string de datos_ingresados de un Trabajo, genera objetos
 * Factorización y los coloca en la cola de factorizaciones pendientes
 */
class Preprocesador : public Consumer<Trabajo*> {
 private:
  /**
   * @brief Cola en la que se insertan las factorizaciones pendientes
   */
  Queue<Factorizacion*>* factorizacionesPendientes = nullptr;

  /**
   * @brief Cola en la que se insertan las factorizaciones listas
   */
  Queue<Factorizacion*>* factorizacionesListas = nullptr;

  /**
   * @brief Cola donde se consumen los trabajos pendientes
   */
  Queue<Trabajo*>* trabajosPendientes = nullptr;

  /**
   * @brief Inserta una Factorización en la cola de factorizaciones pendientes
   * 
   * @param factorizacion Factorización a insertar en la cola
   */
  void produce(Factorizacion* factorizacion);

  /**
   * @brief Obtiene los distintos tokens de la entrada
   * 
   * @param entrada donde contiene un string con el formato numero+','
   * @return tokens, vector que contiene los distintos numeros 
   */
  std::vector<std::string> split(std::stringstream& entrada);

  /**
   * @brief Genera Factorizaciones a partir de un Trabajo
   * 
   * Hace 'split' a Trabajo.datos_ingresados y genera Factorizaciones
   * a partir de esos datos. Si la Factorización generada es válida, la
   * inserta en la cola de factorizaciones pendientes
   * 
   * @param trabajo Trabajo a preprocesar
   */
  virtual void consume(Trabajo* trabajo);

  /**
   * @brief Inicial el ciclo consumeForever de la clase Consumer
   * @return retorna un entero, siempre es 0
   */
  virtual int run();

 public:
  /**
   * @brief Constructor
   * 
   * @param trabajos_pendientes Cola de Trabajos pendientes
   * @param factorizaciones_pendientes Cola de factorizaciones pendientes
   * @param stop Condición para detener consumeForever
   */
  Preprocesador(Queue<Trabajo*>* trabajosPendientes,
                Queue<Factorizacion*>* factorizacionesPendientes,
                Queue<Factorizacion*>* factorizacionesListas, Trabajo* stop);

  /**
   * @brief Constructor sin parametros
   */
  Preprocesador();

  /**
   * @brief Destructor
   */
  ~Preprocesador();
};

#endif  // FACTORIZACION
