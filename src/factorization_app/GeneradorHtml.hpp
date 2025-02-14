#ifndef GENERADORHTML_HPP
#define GENERADORHTML_HPP

#include "Trabajo.hpp"
#include "Factorizacion.hpp"
#include "Consumer.hpp"

/**
 * @brief Genera el HTML con las factorizaciones y las envía al cliente
 */
class GeneradorHtml : public Consumer<Factorizacion*> {
 private:
  /**
   * @brief Cola donde se consumen las factorizaciones listas
   */
  Queue<Factorizacion*>* factorizacionesListas = nullptr;

  /**
   * @brief Cola de Trabajos listos
   */
  Queue<Trabajo*>* trabajosListos = nullptr;

  /**
   * @brief Inserta los datos en el HttpResponse
   * 
   * Inserta el HTML con las factorizaciones en el HttpResponse
   * 
   * @param trabajo Trabajo que contiene las factorizaciones a imprimir
   */
  void generaHTML(Trabajo& trabajo);

  /**
   * @brief Consume una factorización lista
   * 
   * Consume una factorización lista e incrementa el contador de
   * factorizaciones listas del Trabajo al que pertenece la factorizacion.
   * Cuando se han procesado todas las factorizaciones del trabajo, llama a
   * generaHTML y envía la respuesta al cliente.
   * 
   * @param factorizacion Factorización lista
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
   * @param factorizaciones_listas Cola de factorizaciones listas
   * @param stop Condición para detener consumeForever
   */
  GeneradorHtml(Queue<Factorizacion*>* factorizacionesListas,
    Queue<Trabajo*>* trabajosListos, Factorizacion* stop);

  /**
   * @brief Destructor
   */
  ~GeneradorHtml();
};

#endif  // GENERADORHTML_HPP
