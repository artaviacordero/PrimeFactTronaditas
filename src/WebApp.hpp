#ifndef WEBAPP_PROYECTO
#define WEBAPP_PROYECTO

#include <string>
#include <vector>

// Hilos/Comunicación
#include "Distribuidor.hpp"
#include "ClienteEnviador.hpp"
#include "ClienteGenerador.hpp"
#include "Factorizador.hpp"
#include "Preprocesador.hpp"
#include "Enviador.hpp"
#include "GeneradorHtml.hpp"
#include "Queue.hpp"

// Trabajo
#include "Trabajo.hpp"

// Factorización Prima
#include "Factorizacion.hpp"

class WebApp {
 private:
  /**
   * @brief Puerto del servidor/app raíz
   */
  std::string raiz = "8090";

  /**
   * @brief Puerto al que escucha el servidor al que está asociada la app
   */
  std::string miPuerto;

  /**
   * @brief Cola de clientes que ya terminaron
   * 
   */
  Queue<ClienteGenerador*> clientesListos;

  /**
   * @brief Cola de Trabajos pendientes por procesar
   */
  Queue<Trabajo*> trabajosPendientes;

  /**
   * @brief Cola de Trabajos listos por producir
   */
  Queue<Trabajo*> trabajosListos;

  /**
   * @brief Cola de Factorizaciones por procesar
   */
  Queue<Factorizacion*> factorizacionesPendientes;

  /**
   * @brief Cola de factorizaciones listas
   */
  Queue<Factorizacion*> factorizacionesListas;

  /**
   * @brief Hilo Distribuidor
   */
  Distribuidor* distribuidor = nullptr;

  /**
   * @brief Hilo preprocesador
   */
  Preprocesador* preprocesador = nullptr;

  /**
   * @brief Arreglo de hilos factorizadores
   */
  std::vector<Factorizador*> factorizadores;

  /**
   * @brief Hilo Enviador
   */
  GeneradorHtml* generadorHtml = nullptr;

  /**
   * @brief Hilo Enviador
   */
  Enviador* enviador = nullptr;

  /**
   * @brief Hilo enviador de datos recibidos por el cliente
   * 
   * Envía los datos recibidos por el cliente, los envía al usuario final
   * y termina el cliente
   */
  ClienteEnviador* clienteEnviador = nullptr;

  /**
   * @brief Remueve texto no necesario incluído en la URI
   * 
   * @param uri, string de la URI
   * @returns ret, string sin los datos innecesarios de la "ruta", dejando
   * únicamente la lista de entradas.
   */
  std::string parsea(const std::string& uri);

 public:
  /**
   * @brief Construye las colas de trabajos e hilos
   */
  WebApp() = delete;

  /**
   * @brief Construye las colas de trabajos e hilos
   */
  explicit WebApp(std::string puerto);

  /**
   * @brief Destruye las colas de trabajos e hilos
   */
  ~WebApp();

  /**
   * @brief Recibe la solicitud HTTP y la respuesta para una consulta HTTP
   * 
   * Recibe un HttpRequest y un HttpResponse. Si le corresponde procesar la
   * solicitud, genera un Trabajo a partir de esos datos.
   * 
   * @param solicitud Solicitud HttpRequest recibida por referencia
   * @param respuesta Respuesta HttpResponde recibida por referencia
   */
  bool recibeSolicitud(HttpRequest& solicitud, HttpResponse& respuesta);
};

#endif
