#include "CalculadoraFactores.hpp"

#include <utility>

/*
 * CONSTRUCTOR/DESTRUCTOR
*/

CalculadoraFactores::CalculadoraFactores() {}

CalculadoraFactores::~CalculadoraFactores() {}


/*
 * METODOS PRIVADOS
*/

bool CalculadoraFactores::esValida(Factorizacion& factorizacion) {
  bool ret = true;

  if (factorizacion.obtieneNumero() < 2) {
    ret = false;
  }

  return ret;
}


/*
 * METODOS PÚBLICOS
*/

void CalculadoraFactores::calculaFactores(Factorizacion& factorizacion) {
  if (this->esValida(factorizacion)) {
    int64_t numero = factorizacion.obtieneNumero();
    std::pair<int64_t, int64_t> factor;

    // Mientras el número sea par, 2 es un factor
    if (!(numero % 2)) {
      factor.first = 2;
      factor.second = 0;

      while (!(numero % 2)) {
        factor.second++;
        numero = numero / 2;
      }

      factorizacion.agregaFactor(factor);
    }

    // Mientras el número sea múltiplo de 3
    if (!(numero % 3)) {
      factor.first = 3;
      factor.second = 0;

      while (!(numero % 3)) {
        factor.second++;
        numero = numero / 3;
      }

      factorizacion.agregaFactor(factor);
    }

    // Busca factores primos entre 3 y la raíz cuadrada de n
    bool salta = false;
    for (int64_t i = 5; i*i <= numero; i += 2) {
      // Si i es factor
      if (!(numero % i)) {
        factor.first = i;
        factor.second = 0;

        while (!(numero % i)) {
          factor.second++;
          numero = numero / i;
        }

        factorizacion.agregaFactor(factor);
      }
      if (salta) {
        i += 2;
      }
      salta = !salta;
    }

    // Si n es mayor que dos, lo agrega como factor primo
    if (numero > 2) {
      factor.first = numero;
      factor.second = 1;
      factorizacion.agregaFactor(factor);
    }
  }
}
