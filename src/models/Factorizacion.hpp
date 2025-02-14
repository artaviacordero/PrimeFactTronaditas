#ifndef FACTORIZACION_HPP
#define FACTORIZACION_HPP

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Trabajo.hpp"

class Trabajo;

/**
 * @brief Clase que representa una entrada del usuario
 * Esta clase representa una entrada que el usuario haya ingresado.
 * Un entrada puede ser considerada un línea de un archivo, o un valor
 * ingresado manualmente a través del teclado.
 */
class Factorizacion {
 private:
  /**
   * @brief Variable booleana que determina si la entrada es válida
   * 
   * Una entrada puede tomar muchos valores admitidos, pero sólo entradas
   * con un valor numérico mayor a 0 son entrada válidas. Se asume falso.
   */
  bool valido = false;

  /**
   * @brief Valor numérico de la entrada
   * 
   * Este atributo almacena el valor numérico de la entrada del usuario.
   */
  int64_t numero;

  /**
   * @brief Valor alfanumérico de la entrada.
   * 
   * Este atributo almacena el valor de la entrada en forma de texto
   */
  std::string valor_alfanumerico;

  /**
   * @brief Lista de factores primos de la entrada
   * 
   * Vector de enteros de 64 bits en el que se almacenan todos los factores
   * primos del 'numero'
   */
  std::vector<std::pair<int64_t, int64_t>> factores;

  /**
   * @brief Trabajo al cual pertenece la factorizacion
   */
  Trabajo* trabajo;

  /**
   * @brief Valida que el valor recibido pueda convertirse en un int64_t
   * 
   * Realiza las validaciones sobre el string valor_alfanumerico para
   * convertirlo en un int64_t si es posible.
   */
  void convierteAlfanumerico();

 public:
  /**
   * @brief Constructor de Entrada
   * 
   * Este constructor recibe un string , el cual almacena una cadena de
   * de caracteres.
   * 
   * @param valor Valor alfanumerico de la entrada
   */
  Factorizacion(std::string valor, Trabajo* trabajo);

  /**
   * @brief Destructor de Entrada
   * 
   * Este destructor no realiza ninguna acción
   */
  ~Factorizacion();

  /**
   * @brief Retorna el valor de 'numero'
   * 
   * Devuelve un entero de 64 bits con el valor del atributo 'numero'
   * 
   * @return int64_t valor del atributo 'numero'
   */
  int64_t obtieneNumero();

  /**
   * @brief Agrega un factor a la lista de factores
   * 
   * Agrega un número a la lista de factores de la entrada
   * 
   * @param factor Pareja de un factor más su potencia
   */
  void agregaFactor(std::pair<int64_t, int64_t> factor);

  /**
   * @brief Devuelve this->trabajo
   * 
   * @return Puntero al trabajo al que pertenece la factorización
   */
  Trabajo* obtieneTrabajo();

  /**
   * @brief Operador << para imprimir en salida estándar
   * 
   * Sobrecarga el operador << para imprimir la entrada en la salida estándar
   * 
   * @param os Stream de salida en el cual imprimir
   * @param entrada Instancia de entrada de la cual se imprimirán los datos
   * 
   * @return ostream Devulve el stream de salida
   */
  friend std::ostream& operator << (std::ostream& os,
                                    const Factorizacion& factorizacion);
};

#endif  // FACTORIZACION
