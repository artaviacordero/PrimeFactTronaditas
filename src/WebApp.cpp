#include "WebApp.hpp"

#include <unistd.h>

#include <regex>
#include <string>
#include <sstream>

// HTTP
#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"

WebApp::WebApp(std::string puerto) : miPuerto(puerto) {
  // Solo si es la raíz
  if (this->miPuerto.compare(this->raiz) == 0) {
    // Crea el distribuidor
    this->distribuidor = new Distribuidor(&this->trabajosPendientes,
      &this->clientesListos, nullptr);
    this->distribuidor->startThread();

    // Crea el enviador de clientes
    this->clienteEnviador = new ClienteEnviador(&this->clientesListos,
      nullptr);
    this->clienteEnviador->startThread();
  } else {
    // Si no es la raíz, crea el resto de hilos
    // Crea el hilo preprocesador
    this->preprocesador = new Preprocesador(&this->trabajosPendientes,
      &this->factorizacionesPendientes, &this->factorizacionesListas,
      nullptr);
    this->preprocesador->startThread();

    // Crea los hilos factorizadores
    size_t cantidad_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    for (size_t indice = 0; indice < cantidad_cpus; indice++) {
      factorizadores.push_back(new Factorizador(&factorizacionesPendientes,
        &factorizacionesListas, nullptr));
      factorizadores.back()->startThread();
    }

    // Crea el hilo generador de HTML
    this->generadorHtml = new GeneradorHtml (&this->factorizacionesListas,
      &this->trabajosListos, nullptr);
    this->generadorHtml->startThread();

    // Crea el hilo enviador
    this->enviador = new Enviador(&this->trabajosListos, nullptr);
    this->enviador->startThread();
  }
}

WebApp::~WebApp() {
  // Termina el hilo distribuidor, si es la raíz
  if (this->miPuerto.compare(this->raiz) == 0) {
    // Termina el distribuidor
    this->trabajosPendientes.push(nullptr);
    this->distribuidor->waitToFinish();
    delete this->distribuidor;

    // Termina el enviador de clientes
    this->clientesListos.push(nullptr);
    this->clienteEnviador->waitToFinish();
    delete this->clienteEnviador;
  } else {
    // Si no es la raíz, termina el resto de hilos
    // Termina el hilo preprocesador
    this->trabajosPendientes.push(nullptr);
    this->preprocesador->waitToFinish();
    delete this->preprocesador;

    // Termina los hilos factorizadores
    size_t cantidad_cpus = sysconf(_SC_NPROCESSORS_ONLN);

    // Hace n cantidad de pushes de stop_conditions
    for (size_t indice = 0; indice < cantidad_cpus; ++indice) {
      this->factorizacionesPendientes.push(nullptr);
    }
    // Hace join de los hilos factorizadores
    for (size_t indice = 0; indice < cantidad_cpus; ++indice) {
      this->factorizadores.at(indice)->waitToFinish();
      delete this->factorizadores[indice];
    }

    // Termina el hilo generadorHtml
    this->factorizacionesListas.push(nullptr);
    this->generadorHtml->waitToFinish();
    delete this->generadorHtml;

    // Termina el hilo enviador
    this->trabajosListos.push(nullptr);
    this->enviador->waitToFinish();
    delete this->enviador;
  }
}

bool WebApp::recibeSolicitud(HttpRequest& solicitud, HttpResponse& respuesta) {
  bool ret = false;

  // Parsea la URL
  std::string ruta = this->parsea(solicitud.getURI());

  // Verifica que le corresponda procesar la solicitud
  if (ruta.length() > 0) {
    // Verifica que haya al menos un número en la ruta
    std::smatch matches;
    std::regex numeros("[0-9]");
    if (std::regex_search(ruta, matches, numeros)) {
      ret = true;
    }
  }

  // Si le toca procesar la solicitud
  if (ret) {
    respuesta.keepConnectionAlive();
    Trabajo* trabajo = new Trabajo(ruta, solicitud, respuesta);
    trabajo->puerto = miPuerto;
    trabajosPendientes.push(trabajo);
  }

  return ret;
}

std::string WebApp::parsea(const std::string& uri) {
  std::string ret = "";
  const std::string operation_name = "/fact?number=";

  // Busca el string operation_name en el uri
  size_t pos = uri.find(operation_name);

  // Si viene de la forma /fact?number=n1,n2,n3...
  if (pos != std::string::npos) {
    /* Suma el tamaño del string operation_name para ubicarse donde inician los 
    datos ingreesados por el usuario*/
    pos += operation_name.size();

    // Hace ret igual a uri de pos en adelante
    ret = uri.substr(pos);
  } else {
    // Si viene de la forma /n1,n2,n3...
    std::smatch matches;

    // Crea una expresion regular para "/"
    std::regex ruta_regex("[^/]*$");

    /* Busca la expresion regular en el uri, si la encuentra hace ret igual a
     matches */
    if (std::regex_search(uri, matches, ruta_regex)) {
      ret = matches[0];
    }
  }

  return ret;
}
