#include <cstring>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_map>
#include <stdio.h>
#include <string.h>

class HttpHandler {
public:
  HttpHandler(int port) : port(port) {}

  void setEndpointHandler(const std::string &path,
                          const std::string &message) {
    endpointHandlers[path] = create_endpoint_handler(message);
  }

  void start() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
      perror("Error creating socket");
    }

    sockaddr_in server_address = create_socket();

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

    main_loop(server_socket);
    close(server_socket);
  }

private:
  const int port;
  static const int BUFFER_SIZE = 1024;
  int server_socket;
  std::unordered_map<std::string, std::function<void(int)>> endpointHandlers;

  void handle(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);

    if (bytes_received < 0) {
      perror("Error reading from socket");
      return;
    }

    std::string request(buffer);

    size_t path_start = request.find(' ') + 1;
    size_t path_end = request.find(' ', path_start);
    std::string path = request.substr(path_start, path_end - path_start);

    auto it = endpointHandlers.find(path);
    if (it != endpointHandlers.end()) {
      it->second(client_socket);
    } else {
      const char *response =
          "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
      send(client_socket, response, strlen(response), 0);
      close(client_socket);
    }
  }

  void main_loop(int server_socket) {
    while (true) {
      int client_socket = accept(server_socket, nullptr, nullptr);
      if (client_socket < 0) {
        perror("Error accepting connection");
        continue;
      }

      // Handle the incoming request in a new thread or process
      handle(client_socket);
    }
  }

  sockaddr_in create_socket() {
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    return server;
  }

  std::function<void(int)> create_endpoint_handler(const std::string &responseText) {
    return [responseText](int client_socket) {
      std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " +
                             std::to_string(responseText.length()) + "\r\n\r\n" +
                             responseText;

      send(client_socket, response.c_str(), response.size(), 0);
      close(client_socket);
    };
  }
};

int main() {
  HttpHandler server(8080);

  server.setEndpointHandler("/hello", "Hello World");

  server.start();

  return 0;
}
