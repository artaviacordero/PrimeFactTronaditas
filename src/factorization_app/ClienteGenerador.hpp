#ifndef CLIENTEGENERADOR_HPP
#define CLIENTEGENERADOR_HPP

#include <string>

#include "Distribuidor.hpp"
#include "Queue.hpp"
#include "Socket.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "Trabajo.hpp"

class Distribuidor;

/**
 * @brief Hilo que hace una consulta HTTP a un nodo hijo, a partir de un
 * trabajo. Luego espera por la respuesta y la almacena en la respuesta
 * del trabajo. Una vez ha recibido la respuesta, se envía a sí mismo a
 * la cola de clientesListos.
 */
class ClienteGenerador : public Thread {
 private:
  /**
   * @brief Dirección IP o dominio del servidor al cual enviar la consulta
   */
  std::string servidor;

  /**
   * @brief Puerto para comunicarse con el servidor
   */
  std::string puerto;

  /**
   * @brief Cola de clientes listos
   */
  Queue<ClienteGenerador*>* clientesListos;

  /**
   * @brief Envía una solicitud TCP/HTTP al servidor
   *
   * Lee los datos del trabajo y lo envía al servidor con la dirección:
   * servidor:puerto/fact?number=trabajo->datosIngresados
   * Una vez enviada la solicitud, espera por la respuesta y se envía a sí
   * mismo a la cola de clientesListos
   */
  void enviaSolicitud();

  /**
   * @brief Lee la respuesta HTML enviada por el servidor y la almacena en
   * la respuesta del trabajo
   */
  void recibeRespuesta(Socket& socket);

  /**
   * @brief Método run de Thread
   */
  virtual int run();

 public:
  /**
   * @brief Trabajo que va a ser enviado a alguno de los nodos hijos
   */
  Trabajo* trabajo;

  /**
   * @brief Constructor predeterminado eliminado
   */
  ClienteGenerador() = delete;

  /**
   * @brief Constructor
   * 
   * @param trabajo Trabajo cuyos datos van a ser enviados al servidor
   * @param servidor Dirección IP del servidor al cual enviar la consulta
   * @param puerto Puerto para comunicarse con el servidor
   * @param clientesListos Cola de clientes listos
   */
  ClienteGenerador(Trabajo* trabajo, std::string servidor, std::string puerto,
    Queue<ClienteGenerador*>* clientesListos);

  /**
   * @brief Destructor
   */
  ~ClienteGenerador();
};

#endif  // CLIENTEGENERADOR_HPP
