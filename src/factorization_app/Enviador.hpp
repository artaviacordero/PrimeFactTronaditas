#ifndef ENVIADOR_HPP
#define ENVIADOR_HPP

#include "Trabajo.hpp"
#include "Factorizacion.hpp"
#include "Consumer.hpp"

/**
 * @brief Genera el HTML con las factorizaciones y las envía al cliente
 */
class Enviador : public Consumer<Trabajo*> {
 private:
  /**
   * @brief Cola donde se consumen los trabajos listos
   */
  Queue<Trabajo*>* trabajosListos = nullptr;

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
   * @param factorizaciones_listas Cola de factorizaciones listas
   * @param stop Condición para detener consumeForever
   */
  Enviador(Queue<Trabajo*>* trabajosListos, Trabajo* stop);

  /**
   * @brief Destructor
   */
  ~Enviador();
};

#endif  // ENVIADOR_HPP
