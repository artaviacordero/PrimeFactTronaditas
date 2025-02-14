#ifndef DISTRIBUIDOR_HPP
#define DISTRIBUIDOR_HPP

#include <random>
#include <string>
#include <vector>

#include "ClienteGenerador.hpp"
#include "Consumer.hpp"
#include "Trabajo.hpp"

class ClienteGenerador;

/**
 * @brief Distribuye trabajos pendientes entre los nodos hijos de manera
 * aleatoria. Crea un hilo que se encarga de hacer la cosulta HTTP y esperar
 * la respuesta para cada trabajoPendiente
 */
class Distribuidor : public Consumer<Trabajo*> {
 private:
  /**
   * @brief Dirección IP del servidor donde están los nodos hijos
   */
  std::string servidor = "127.0.0.1";

  /**
   * @brief Vector que contiene los puertos en los que están escuchando los
   * nodos hijos
   */
  std::vector<std::string> puertosDeHijos;

  /**
   * @brief Motor aleatorio para obtener puertos de forma aleatoria
   */
  std::mt19937 motorAleatorio;

  /**
   * @brief Retorna aleatoriamente un puerto de puertosHijos
   */
  std::string obtienePuertoAleatorio();

  /**
   * @brief Cola de clientes listos
   */
  Queue<ClienteGenerador*>* clientesListos;

  /**
   * @brief Crea un hilo ClienteGenerador para cada trabajo pendiente
   * 
   * @param trabajo Trabajo a enviar al hilo ClienteGenerador
   */
  virtual void consume(Trabajo* trabajo);

  /**
   * @brief Método run de Thread
   */
  virtual int run();

 public:
  /**
   * @brief Constructor predeterminado eliminado
   */
  Distribuidor() = delete;

  /**
   * @brief Constructor
   *
   * @param trabajosPendientes cola de trabajos pendientes
   * @param clientesListos cola de trabajos listos
   * @param stop condición de parada
   */
  Distribuidor(Queue<Trabajo*>* trabajosPendientes,
    Queue<ClienteGenerador*>* clientesListos, Trabajo* stop);
  ~Distribuidor();
};

#endif  // DISTRIBUIDOR_HPP
