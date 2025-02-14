#include "ClienteGenerador.hpp"

ClienteGenerador::ClienteGenerador(Trabajo* trabajo, std::string servidor,
  std::string puerto, Queue<ClienteGenerador*>* clientesListos) :
  servidor(servidor), puerto(puerto), trabajo(trabajo) {
  this->clientesListos = clientesListos;
}

ClienteGenerador::~ClienteGenerador() {
}

int ClienteGenerador::run() {
  this->enviaSolicitud();
  return 0;
}

void ClienteGenerador::enviaSolicitud() {
  try {
    // Conexión con el nodo hijo
    TcpClient cliente;
    Socket& socket = cliente.connect(this->servidor.c_str(),
      this->puerto.c_str());

    // Envía la solicitud
    socket << "GET /fact?number=" << this->trabajo->datosIngresados
    << " HTTP/1.1\r\n";
    socket << "Host: " << this->servidor << "\r\n\r\n";
    socket.send();

    // Recibe la respuesta
    this->recibeRespuesta(socket);

    // Informa que puede ser terminado
    this->clientesListos->push(this);
  } catch (std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void ClienteGenerador::recibeRespuesta(Socket& socket) {
  // Recibe datos del nodo hijo
  std::string linea;

  // Agrega los headers a la respuesta
  trabajo->respuesta.setHeader("Server", "AttoServer v1.0");
  trabajo->respuesta.setHeader("Content-type", "text/html; charset=ascii");

  // Inserta el HTML en la respuesta
  bool separadorRecibido = false;
  while (socket.readLine(linea)) {
    // Solo toma en cuenta el contenido después de la línea vacía.
    if (separadorRecibido) {
      this->trabajo->respuesta.body() << linea;
    } else {
      if (linea.compare("\r") == 0) {
        separadorRecibido = true;
      }
    }
  }
}
