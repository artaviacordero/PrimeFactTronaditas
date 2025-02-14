#include <signal.h>

#include <atomic>
#include <cstring>
#include <mutex>
#include <thread>

#include "WebServer.hpp"

// Mutex para activar el hilo que mata al servidor
std::mutex kill_server_mtx;

// Espera a que una señal desbloquee el mutex y mata al server
void serverKiller(WebServer* server) {
  kill_server_mtx.lock();
  server->finish();
  kill_server_mtx.unlock();
}

// Subrutina a ser llamada cuando ocurra la señal SIGINT
// Si una señal es recibida, desbloquea el mutex
void signal_handler(int) {
  kill_server_mtx.unlock();
}

int main(int argc, char* argv[]) {
  // Bloquea el mutex para matar el servidor
  kill_server_mtx.lock();

  // Crea una estructura sigaction y la limpia
  struct sigaction signal_action;
  memset(&signal_action, 0, sizeof(signal_action));

  // Define la subrutina a llamar cuando ocurra la señal
  signal_action.sa_handler = signal_handler;

  // Asocia la señal con el sigaction
  sigaction(SIGINT, &signal_action, NULL);

  // Crea una instancia de servidor web
  WebServer server;

  // Crea hilo para matar el servidor en caso de ser necesario
  std::thread server_killer(serverKiller, &server);

  // Inicia el servidor
  int ret = server.start(argc, argv);

  // Termina el matador de servidor
  server_killer.join();

  return ret;
}
