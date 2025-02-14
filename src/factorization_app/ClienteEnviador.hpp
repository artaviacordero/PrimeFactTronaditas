#ifndef CLIENTEENVIADOR_HPP
#define CLIENTEENVIADOR_HPP

#include "ClienteGenerador.hpp"
#include "Consumer.hpp"
#include "Queue.hpp"

/**
 * @brief Clase que consume de la cola de hilosListos. Para cada hilo listo,
 * envía los datos de la respuesta HTTP al usuario final y termina el hilo
 * ClienteGenerador.
 */
class ClienteEnviador : public Consumer<ClienteGenerador*> {
 private:
  /**
   * @brief Envía la respuesta obtenida por un cliente y lo termina
   * @param cliente ClienteGenerador que contiene la respuesta HTTP
   */
  virtual void consume(ClienteGenerador* cliente);

  /**
   * @brief Método run de Thread. Inicia consumeForever()
   */
  virtual int run();

 public:
  /**
   * @brief Constructor prederminado eliminado
   */
  ClienteEnviador() = delete;

  /**
   * @brief Constructor
   * @param clientesListos cola de la cual consumir clienteGenerador que
   * ya terminaron
   * @param stop Condición de parada
   */
  ClienteEnviador(Queue<ClienteGenerador*>* clientesListos,
    ClienteGenerador* stop);

  /**
   * @brief Destructor
   */
  ~ClienteEnviador();
};


#endif
