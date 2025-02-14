# Factorizacion Prima

#### Equipo:  Tronaditas
#### Integrantes: Frank Alvarado, Daniel Artavia, Pablo Otarola

## Factorización Prima
En este proyecto se implementa la factorización prima de un número, la cual corresponde a la representación de un número por medio de sus factores primos.

### Instrucciones de compilación (Build)
Para descargar y compilar el código, se deben ejecutar los siguientes comandos:

```bash
git clone https://git.ucr.ac.cr/ci0117-2020iii_tronaditas/proyecto1_factorizacionprimawebserver.git
cd proyecto1_factorizacionprimawebserver
cd webserv
make
```

### Manual de usuario
Una vez compilado el código, se debe cambiar/mover al directorio _proyecto1_factorizacionprimawebserver/webserv_
```bash
cd proyecto1_factorizacionprimawebserver/webserv
```

Dentro del directorio _proyecto1_factorizacionprimawebserver/webserv, se debe ejecutar el siguiente comando
```bash
./bin/webserv
```

El programa intentará usar el puerto 8080 para escuchar por consultas HTTP. Si el puerto está ocupado, puede ingresar un número de puerto por argumento:
```bash
./bin/webserv 8081
```

Para este ejemplo, se usará el puerto 8080

![Paso 1 - Correr el servidor](Graficos/iniciar_ejecucion.png "Aplicación corriendo en el puerto 8080")

Posteriormente, para abrir la interfaz del programa, debe abrir algún navegador web y dirigirse a http://localhost:8080 NOTA: es importante que use http:// y que agregue :8080 al final, ya que algunos navegadores, como Firefox, buscan, por defecto, crear una conexión HTTPS, y no va a poder abrir la interfaz de la aplicación.

Una vez en la dirección del programa, verá la siguiente interfaz:

![Paso 2 - Acceder a la aplicación](Graficos/pagina_principal.png "Interfaz de la aplicación en el navegador")

La interfaz ofrece un campo de entrada de números en el que usted puede ingresar el número al cual desea factorizar:

![Paso 3 - Ingresar números en la interfaz](Graficos/ingresar_numero.png "Número 25 ingresado para factorizar")

El navegador mostrará en pantalla los resultados de la factorización

![Paso 4 - Resultados de la factorización](Graficos/factorizacion_numero.png "Resultados de la factorización")

Adicionalmente, puede editar la URL en la barra de direcciones del navegador e ingresar una lista de valores separados por coma, de cualquiera de las siguientes maneras:

![Paso 5 - Lista en la barra de direcciones](Graficos/Lista_de_numeros.png "Lista en la barra de direcciones con variables GET")
![Paso 6 - Lista en la barra de direcciones](Graficos/Lista_de_numeros_2.png "Lista en la barra de direcciones")

La aplicación calculará la factorización para cada uno de los elementos de la lista, si es posible. Si alguna de las entradas no es válida, mostrará un mensaje de error. Por ejemplo, para la lista de las imágenes anteriores, se obtiene el siguiente resultado:

![Paso 7 - Resultado de la lista de entradas](Graficos/factorizacion_lista_numeros.png "Resultado generado por la lista de entradas")

Finalmente, para terminar la aplicación, dirijase a la terminal en la que se encuentra corriendo el servidor y presione la combinación de teclas Ctrl+C

![Paso 8 - Terminar el servidor](Graficos/terminar_ejecucion.png "Terminar el servidor")


## Diseño de la implementación concurrente:
El siguiente es un diagrama que muestra cómo se piensa implementar una versión concurrente de este programa:

![Diagrama de clases](Graficos/diagrama_clases.svg "Diagrama de clases del servidor+app")
![Diagrama de actividades](Graficos/diagrama_actividades.svg "Diagrama de actividades del servidor+app")
