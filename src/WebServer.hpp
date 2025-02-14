#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include "HttpServer.hpp"
#include "WebApp.hpp"

#define DEFAULT_PORT "8080"

class WebServer : public HttpServer {
  DISABLE_COPY(WebServer);

 private:
  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;

  /// Instancia de la aplicación web
  WebApp* app = nullptr;

 public:
  /// Constructor
  WebServer();
  /// Destructor
  ~WebServer();
  /// Start the simulation
  int start(int argc, char* argv[]);
  /// Finish the simulation
  void finish();

 protected:
  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;

 protected:
  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends a page for a non found resouce in this server
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // WEBSERVER_H
