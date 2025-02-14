#ifndef CALCULADORA_FACTORES
#define CALCULADORA_FACTORES

#include <cinttypes>
#include <cmath>
#include <vector>

#include "Factorizacion.hpp"

/**
 * @brief Clase que representa una calculadora de Factores Primos
 */
class CalculadoraFactores {
 private:
  /**
   * @brief Valida que una entrada sea válida para calcular sus factores primos
   * Para que una entrada sea válida, su atributo 'numero' debe ser mayor o
   * igual a 2. Esta retorna 'true' si la entrada tiene un valor numérico mayor
   * o igual a 2.
   * 
   * @param Entrada* entrada Puntero a una instancia de Entrada a validar
   * @return bool Valor booleano que es true si la entrada es válida
   */
  bool esValida(Factorizacion& factorizacion);

 public:
  // Constructor/Destructor

  /**
   * @brief Constructor vacío
   * Este constructor no realiza ninguna acción.
   */
  CalculadoraFactores();

  /**
   * @brief Destructor vacío
   * Este destructor no realiza ninguna acción
   */
  ~CalculadoraFactores();

  /**
   * @brief Calcula los factores primos de un número
   * 
   * Receibe una entrada y almacena -en la lista de factores de la entrada-
   * su factorización prima. Antes de realizar la factorización, verifica que
   * la entrada sea válida.
   * Primero divide el número a la mitad las veces que pueda hasta que
   * obtenga todas las veces que 2 es un factor. Luego hace un ciclo sobre
   * los números impares desde 3 al techo de la raíz cuadrada de n. Finalmente,
   * si luego de dividir hasta la raíz de n, todavía queda un número mayor que 2,
   * agrega el número restante.
   * 
   * @param Entrada* entrada Puntero a una instancia de Entrada a procesar
   */
  void calculaFactores(Factorizacion& factorizacion);
};

#endif  // CALCULADORA_FACTORES
