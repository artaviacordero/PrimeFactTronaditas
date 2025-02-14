#include "Trabajo.hpp"

/*
 * CONSTRUCTOR/DESTRUCTOR
*/

Trabajo::Trabajo(const std::string& datos,
  HttpRequest& solicitud, HttpResponse& respuesta) :
  solicitud(solicitud),
  respuesta(respuesta),
  datosIngresados(datos),
  factorizacionesTerminadas(0) {
  }

Trabajo::~Trabajo() {
  for (auto factorizacion : this->factorizaciones) {
    delete factorizacion;
  }
}
