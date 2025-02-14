#ifndef TRABAJO_HPP
#define TRABAJO_HPP

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

#include "Factorizacion.hpp"

class Factorizacion;

/**
 * @brief Clase que representa el proceso para el calculo de la facorización
 * 
 * ProcesoFactorizacion es una estructura que almacena todos los datos
 * necesarios para realizar el proceso completo de factorización prima:
 * desde dividir los datos del usuario en números separados, realizar
 * el cálculo de las factorizaciones y enviar los resultados a la respuesta
 * HTTP.
 */
class Trabajo {
 public:
  std::string puerto;
  /**
   * @brief Referencia a la solicitud HTTP a la que pertenece el proceso
   */
  HttpRequest solicitud;

  /**
   * @brief Referencia a la respuesta HTTP a la que pertenece al proceso
   */
  HttpResponse respuesta;

  /**
   * @brief String para almacenar el texto ingresado por el usuario
   */
  std::string datosIngresados;

  /**
   * @brief Cola de factorizaciones
   */
  std::vector<Factorizacion*> factorizaciones;

  /**
   * @brief Contador de factorizaciones completadas
   */
  size_t factorizacionesTerminadas;

  /**
   * @brief Constructor de ProcesoFactorizacion
   * 
   * Recibe un string con los datos ingresados por el usuario, una
   * solicitud HttpRequest y una respuesta HttpResponse. Genera una
   * ListaEntradas a partir del string con los datos ingresados por el
   * usario.
   * 
   * @param datos string con los datos ingresados por el usuario
   * @param solicitud Solicitud HTTP a la cual corresponde el trabajo
   * @param respuesta Respuesta HTTP a la cual enviar los resultados
   */
  Trabajo(const std::string& datos, HttpRequest &solicitud,
          HttpResponse &respuesta);

  /**
   * @brief Destructor de ProcesoFactorizacion
   * 
   * Destructor vacío
   */
  ~Trabajo();
};

#endif  // TRABAJO
