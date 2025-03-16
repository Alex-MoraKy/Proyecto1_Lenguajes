
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

using namespace std;

#define PORT 8080

int server_fd;

void signalHandler(int signum) {
    cout << "\nSeñal recibida: " << signum << ". Cerrando servidor..." << endl;
    close(server_fd);
    exit(signum);
}

int main() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket;
    char buffer[1024] = {0};

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Fallo en la creación del socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Error en el bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Error en el listen");
        exit(EXIT_FAILURE);
    }

    cout << "Servidor escuchando en el puerto " << PORT << endl;

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Fallo en el accept");
            continue;
        }

        read(new_socket, buffer, 1024);
        cout << "Mensaje recibido: " << buffer << endl;
        send(new_socket, "Mensaje recibido", strlen("Mensaje recibido"), 0);
        close(new_socket);
    }
    return 0;
}
