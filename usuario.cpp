
#include "prototipos.h"

// --------------------------------------- //
// Variables

// --------------------------------------- //
// Funciones

int main() {

	int user_socket = 0;                // Descriptor de archivo del socket
    struct sockaddr_in user_address;    // Estructura para almacenar la dirección del usuario
    char buffer[MSG_MAX_SIZE] = {0};    // Buffer para recibir datos del servidor
    string message;                     // Mensaje que enviará el cliente

    while (true) {
	    // --------------------------------------- //
	    // Pedir mensaje al usuario
	    cout << "Ingrese el mensaje a enviar: ";
	    getline(cin, message);  					// Leer mensaje desde la entrada estándar

	    // --------------------------------------- //
	    // Crear el socket del cliente
	    user_socket = socket(AF_INET, SOCK_STREAM, 0);
	    if (user_socket < 0) {
	        cerr << "Error al crear el socket" << endl;
	        return -1;
	    }

	    // --------------------------------------- //
	    // Configurar la dirección del servidor
	    user_address.sin_family = AF_INET;  				// Tipo de dirección: IPv4
	    user_address.sin_port = htons(ACTUAL_PORT);  		// Convertir el puerto al formato de red

	    // --------------------------------------- //
	    // Detección de errores

	    // Dirección IP de texto a binario
	    if (inet_pton(AF_INET, "127.0.0.1", &user_address.sin_addr) <= 0) {
	        cerr << "Dirección inválida o no soportada" << endl;
	        return -1;
	    }

	    // Conectar al servidor
	    if (connect(user_socket, (struct sockaddr*)&user_address, sizeof(user_address)) < 0) {
	        cerr << "Conexión fallida" << endl;
	        return -1;
	    }

	    // --------------------------------------- //

	    // Enviar el mensaje al servidor
	    send(user_socket, message.c_str(), message.length(), 0);
	    //cout << "Mensaje enviado." << endl;

	    // Recibir la respuesta del servidor
	    read(user_socket, buffer, MSG_MAX_SIZE);
	    //cout << "Respuesta del servidor: " << buffer << endl;

	}

    // Cerrar el socket
    close(user_socket);

    return 0;
}