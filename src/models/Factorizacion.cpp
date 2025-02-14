#include <stdexcept>
#include <cinttypes>

#include "Factorizacion.hpp"

/*
 * CONSTRUCTOR/DESTRUCTOR
*/

Factorizacion::Factorizacion(std::string valor, Trabajo* trabajo) :
                            valor_alfanumerico(valor), trabajo(trabajo) {
  this->convierteAlfanumerico();
}

Factorizacion::~Factorizacion() {}

void Factorizacion::convierteAlfanumerico() {
  if (this->valor_alfanumerico.length() > 0) {
    try {
      this->numero = stoll(this->valor_alfanumerico, nullptr, 10);
      if (this->numero >= 2) {
        // String para verificar que el largo del número sea igual
        // al largo del valor alfanumérico.
        // Esto es para corregir que el programa acepte número como 25bla
        // como válidos.
        std::string verificacion = std::to_string(this->numero);
        if (verificacion.length() == this->valor_alfanumerico.length()) {
          valido = true;
        } else {
          this->numero = -1;
        }
      }
    }
    catch(const std::invalid_argument& e) {
      this->numero = -1;
    }
    catch(const std::out_of_range& e) {
      this->numero = -1;
    }
  }
}

int64_t Factorizacion::obtieneNumero() {
  return numero;
}

void Factorizacion::agregaFactor(std::pair<int64_t, int64_t> factor) {
  // Agrega la pareja <factor, potencia> a factores
  this->factores.push_back(factor);
}


Trabajo* Factorizacion::obtieneTrabajo() {
  return this->trabajo;
}

std::ostream& operator << (std::ostream& os,
                          const Factorizacion& factorizacion) {
  // Imprime la identación para el <li>
  os << "    ";

  // Etiqueta de apertura del <li>
  if (factorizacion.valido) {
    os << "<li>";
  } else {
    // Si la factorización no es valida
    os << "<li class='err'>";
  }

  // Imprime el valor alfanumérico de la factorización
  os << factorizacion.valor_alfanumerico << ": ";

  // Imprime los factores y sus potencias
  // Si la factorización es válida
  if (factorizacion.valido && factorizacion.numero >= 2) {
    // Imprime los <factor,potencia>, separados por *
    for (size_t i = 0; i < factorizacion.factores.size(); ++i) {
      // Imprime el factor
      os << factorizacion.factores[i].first;
      // Imprime la potencia, si es mayor que 1
      if (factorizacion.factores[i].second > 1) {
        os << "^" << factorizacion.factores[i].second;
      }
      // Imprime *, si no es el último <factor,potencia>
      if (i < factorizacion.factores.size() - 1) {
        os << " * ";
      }
    }
  } else {
    // Imprime el mensaje de error
    if (factorizacion.numero >= 0) {
      os << "NA";
    } else {
      os << "error";
    }
  }

  // Cierra el <li>
  os << "</li>";

  return os;
}
