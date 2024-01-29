#include <cstring>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_map>
#include <utility>

#include "httpStatus.h"
#include "routerAlgorithm.h"

class HttpHandler {
public:
  HttpHandler(int port) : port(port) {}

  void setEndpointHandler(const std::string &path,
                          std::pair<std::string, std::string> statusCode) {
    router->insert(path, endpointHandlers, statusCode);
  }

  void setEndpointHandler(const std::string &path, const std::string &message,
                          std::pair<std::string, std::string> statusCode) {
    router->insert(path, endpointHandlers, statusCode, message);
  }

  int start() {
    int server_socket = createSocket();
    if (server_socket == -1) {
      return -1;
    }
    sockaddr_in server_address = createAddress();

    if (bind(server_socket,
             reinterpret_cast<struct sockaddr *>(&server_address),
             sizeof(server_address)) < 0) {
      perror("Error binding socket");
      close(server_socket);
    }

    if (listen(server_socket, 5) < 0) {
      perror("Error listening");
      close(server_socket);
    }

    std::cout << "Server listening on port " << port << std::endl;

    while (true) {
      int client_socket = createClient(server_socket);
      if (client_socket < 0) {
        break;
      }

      handle(client_socket);
    }

    close(server_socket);
    return 0;
  }

private:
  const int port;
  static const int BUFFER_SIZE = 1024;
  PathStructure *endpointHandlers = new PathStructure;
  RouterAlgorithm *router = new RouterAlgorithm;

  void handle(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    std::string response;

    if (bytes_received < 0) {
      perror("Error reading from socket");
      return;
    }

    std::string request(buffer);

    size_t path_start = request.find(' ') + 1;
    size_t path_end = request.find(' ', path_start);
    std::string path = request.substr(path_start, path_end - path_start);

    auto foundNode = router->search(path, endpointHandlers);

    if (foundNode == nullptr) {
      response = "HTTP/1.1 " + HttpStatus::NOT_FOUND +
                 "\r\nContent-Length: 13\r\n\r\n404 Not Found";

      send(client_socket, response.c_str(), response.size(), 0);
      close(client_socket);
    }

    if (foundNode->message.empty()) {
      response =
          "HTTP/1.1 " + HttpStatus::OK + "\r\nContent-Length: 6\r\n\r\n200 OK";
    } else {
      response =
          createEndpointHandler(foundNode->message, foundNode->status.first);
    }

    send(client_socket, response.c_str(), response.size(), 0);
    close(client_socket);
  }

  int createClient(int server_socket) {
    int client_socket = accept(server_socket, nullptr, nullptr);
    if (client_socket < 0) {
      perror("Error accepting connection");
    }

    return client_socket;
  }

  int createSocket() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
      perror("Error creating socket");
    }

    // Set the SO_REUSEADDR option on the socket. This allows the server to be
    // restarted immediately after it is killed, without having to wait for the
    // socket to be closed.
    int optval = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
               sizeof(int));

    return server_socket;
  }

  sockaddr_in createAddress() {
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    return server;
  }

  std::string createEndpointHandler(const std::string &response_text,
                                    const std::string &statuscode) const {
    return "HTTP/1.1 " + statuscode +
           "\r\nContent-Length: " + std::to_string(response_text.length()) +
           "\r\n\r\n" + response_text;
  }
};

int main() {
  HttpHandler server(8080);

  server.setEndpointHandler("/hello", "Hello World", HttpStatus::ok());
  server.setEndpointHandler("/user/{name:string}", "Hello World",
                            HttpStatus::ok());

  server.start();

  return 0;
}
