#include <cassert>
#include <stdexcept>
#include <string>

#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket& client) {
  // TODO(jhc): Store client connections (sockets) into a collection
  // in order to support HTTP/1.1 and later

  // While the same client asks for HTTP requests in the same connection
  while (true) {
    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client);

    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse httpResponse(client);

    // Give subclass a chance to respond the HTTP request
    this->handleHttpRequest(httpRequest, httpResponse);
    const bool handled = httpResponse.handled;

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion().compare("HTTP/1.0") == 0) {
      // The socket will not be more used, close the connection
      client.close();
      break;
    }

    // TODO(jhc): This version handles just one client request per connection
    break;
  }
}
