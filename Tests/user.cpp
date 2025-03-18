
#include "prototipos.h"

int main() {
    int sock = 0;                       // Descriptor de archivo del socket
    struct sockaddr_in serv_addr;       // Estructura para almacenar la dirección del servidor
    char buffer[MSG_MAX_SIZE] = {0};    // Buffer para recibir datos del servidor
    string message;                // Mensaje que enviará el cliente

    // Pedir mensaje al usuario
    cout << "Ingrese el mensaje a enviar: ";
    getline(cin, message);  // Leer mensaje desde la entrada estándar

    // 1. Crear el socket del cliente
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Error al crear el socket" << endl;
        return -1;
    }

    // 2. Configurar la dirección del servidor
    serv_addr.sin_family = AF_INET;  // Tipo de dirección: IPv4
    serv_addr.sin_port = htons(PORT);  // Convertir el puerto al formato de red

    // 3. Convertir la dirección IP de texto a binario
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cerr << "Dirección inválida o no soportada" << endl;
        return -1;
    }

    // 4. Conectar al servidor
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Conexión fallida" << endl;
        return -1;
    }

    // 5. Enviar el mensaje al servidor
    send(sock, message.c_str(), message.length(), 0);
    cout << "Mensaje enviado: " << message << endl;

    // 6. Recibir la respuesta del servidor
    read(sock, buffer, MSG_MAX_SIZE);
    cout << "Respuesta del servidor: " << buffer << endl;

    // 7. Cerrar el socket
    close(sock);
    return 0;
}

