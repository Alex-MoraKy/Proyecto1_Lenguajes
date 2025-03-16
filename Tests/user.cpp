#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    std::string message;

    // Pedir mensaje al usuario
    std::cout << "Ingrese el mensaje a enviar: ";
    std::getline(std::cin, message);

    // Crear socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Error al crear el socket" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir dirección IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Dirección inválida o no soportada" << std::endl;
        return -1;
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Conexión fallida" << std::endl;
        return -1;
    }

    // Enviar mensaje
    send(sock, message.c_str(), message.length(), 0);
    std::cout << "Mensaje enviado: " << message << std::endl;

    // Recibir respuesta
    read(sock, buffer, 1024);
    std::cout << "Respuesta del servidor: " << buffer << std::endl;

    // Cerrar socket
    close(sock);
    return 0;
}

