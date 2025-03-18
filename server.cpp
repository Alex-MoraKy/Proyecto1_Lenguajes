
#include "prototipos.h"

// --------------------------------------- //
// Variables

int server_file_descriptor;  	// Descriptor de archivo del socket del servidor.

// --------------------------------------- //
// Funciones

/* Capturar interrupciones del sistema (SIGINT, SIGTERM) y cerrar el servidor de manera segura.
signal_id: Número de la señal recibida. */
void signalHandler(int signal_id) {

    cout << "\nSeñal recibida: " << signal_id << ". Cerrando servidor..." << endl;

    close(server_file_descriptor); 	// Cerrar el socket del servidor.
    exit(signal_id); 				// Terminar el proceso con el código de la señal recibida.
}

// --------------------------------------- //
// Servidor
int main() {

	// --------------------------------------- //
	struct sockaddr_in server_address;  	// Struct "sockaddr_in " que guarda la dirección del servidor.
    int addrlen = sizeof(server_address);   // Longitud de la dirección del servidor.
    int new_socket;                     	// Descriptor del socket para la conexión entrante.
    char buffer[MSG_MAX_SIZE];            			// Buffer temporal para almacenar mensajes recibidos.
    
    // --------------------------------------- //
    // Configurar la función "signalHandler" en caso de cierre.
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    // --------------------------------------- //
    // Crear el socket del servidor.
    server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    // Si el descriptor no recibe datos -> error en la creación del socket.
    if (server_file_descriptor == 0) {
        perror("Fallo en la creación del socket");
        exit(EXIT_FAILURE);
    }

    // --------------------------------------- //
    // Configurar la estructura de la dirección del servidor.
    server_address.sin_family = AF_INET; 			// AF_INET es una constante que especifica que se trabajará con IPv4.
    server_address.sin_addr.s_addr = INADDR_ANY; 	// INADDR_ANY es una constante que indica que un servidor debe aceptar conexiones en cualquier dirección IP disponible.
    server_address.sin_port = htons(ACTUAL_PORT); 			// Convertir el número de puerto a formato de red.

    // --------------------------------------- //
    // Posibles errores

    // Asocia el socket con la dirección y puerto especificados.
    if (bind(server_file_descriptor, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error en el bind. No se puedo asociar el socket con la dirección y puerto.");
        exit(EXIT_FAILURE);
    }

    // Pone el servidor en modo escucha para aceptar conexiones entrantes.
    if (listen(server_file_descriptor, 3) < 0) {
        perror("Error en el listen");
        exit(EXIT_FAILURE);
    }

    // --------------------------------------- //
	cout << "Escuchando... Puerto actual: " << ACTUAL_PORT << endl;

	// Apertura de servidor hasta que se cierre por alguna señal.
	while (true) {

        // Espera una conexión entrante y la almacena en la variable "new_socket".
        new_socket = accept(server_file_descriptor, (struct sockaddr*)&server_address, (socklen_t*)&addrlen);

        if (new_socket < 0) {  // Error en la recepción del socket
            perror("Fallo en el accept");
            continue;
        }

        // Lee los datos enviados por el cliente.
        read(new_socket, buffer, MSG_MAX_SIZE);
        cout << "Mensaje recibido: " << buffer << endl;

        /* Responde al cliente con un mensaje de confirmación.
        send(new_socket, "Mensaje recibido", strlen("Mensaje recibido"), 0); */
        
        // Cierra la conexión con el cliente.
        close(new_socket);
    }

	return 0;
}