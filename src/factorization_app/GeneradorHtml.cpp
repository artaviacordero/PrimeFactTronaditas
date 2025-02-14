#include <string>

#include "GeneradorHtml.hpp"

GeneradorHtml::GeneradorHtml(Queue<Factorizacion*>* factorizacionesListas,
  Queue<Trabajo*>* trabajosListos, Factorizacion* stop) : Consumer(stop) {
  this->factorizacionesListas = factorizacionesListas;
  this->queueConsumer = factorizacionesListas;
  this->trabajosListos = trabajosListos;
}

GeneradorHtml::~GeneradorHtml() {}

void GeneradorHtml::generaHTML(Trabajo& trabajo) {
  // Headers HTTP
  trabajo.respuesta.setHeader("Server", "AttoServer v1.0");
  trabajo.respuesta.setHeader("Content-type", "text/html; charset=ascii");

  // Cuerpo de la respuesta
  std::string titulo = "Prime factorization for " + trabajo.datosIngresados;
  trabajo.respuesta.body() << "<!DOCTYPE html>\n"
  << "<html lang=\"en\">\n"
  << "  <meta charset=\"ascii\"/>\n"
  << "  <title>" << titulo << "</title>\n"
  << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
  << "  <h1>" << titulo << "</h1>\n"
  << "  <ul>\n";

  // Escribe los resultados de las factorizaciones
  for (auto factorizacion : trabajo.factorizaciones) {
    assert(factorizacion);
    trabajo.respuesta.body() << *factorizacion << std::endl;
  }

  // Resto del cuerpo de la respuesta
  trabajo.respuesta.body() << "  </ul>\n"
  << "  <hr><p><a href=\"/\">Back</a></p><hr>\n"
  << "  Generado desde el proceso en puerto " << trabajo.puerto << "\n"
  << "</html>\n";
}

void GeneradorHtml::consume(Factorizacion* factorizacion) {
  if (factorizacion != this->stopCondition) {
    Trabajo& trabajo = *factorizacion->obtieneTrabajo();
    trabajo.factorizacionesTerminadas++;
    /* Si la cantidad terminadas de factorizaciones es igual al
     * total de factorizaciones del trabajo, entonces lo mete a la cola de
     * trabajos terminados*/
    if (trabajo.factorizacionesTerminadas == trabajo.factorizaciones.size()) {
      this->generaHTML(trabajo);
      this->trabajosListos->push(&trabajo);
    }
  } else {
    // Termina el ciclo consumeForever
    this->done = true;
  }
}

int GeneradorHtml::run() {
  this->consumeForever();
  return 0;
}
