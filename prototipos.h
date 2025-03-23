/* Archivo header de prototipos. 
- Declaración de librerías.
- Declaración de funciones.
- Declaración de constantes. 
- Declaración de variables.*/

// --------------------------------------- //
//                Librerías                //
// --------------------------------------- //

#include <iostream>  	// Prints
#include <cstring>		// Manejo de strings.

#include <fstream>		// Manejo de archivos
#include <sstream>		// Manipulación de cadenas de texto

#include <csignal>   	// Manejo de señales (SIGINT y SIGTERM)
#include <cstdlib>		// Funciones generales, gestión de memoria, conversiones y control del programa.

#include <unistd.h>		// Acceso a llamadas del sistema en Unix/Linux (Crear o leer sockets por ejemplo)
#include <netinet/in.h> // Structs y constantes para sockets, especialmente para IPv4.
#include <sys/socket.h> // Funciones de sockets para linux.
#include <arpa/inet.h>  // Manipulación de direcciones IP.
#include <sys/wait.h>  // Para waitpid()

using namespace std; 	// Evitar std::

// --------------------------------------- //
//                Constantes               //
// --------------------------------------- //


// --------------------------------------- //
//                Funciones                //
// --------------------------------------- //


// --------------------------------------- //
//                Variables                //
// --------------------------------------- //

int ACTUAL_PORT = 8089;     // Puerto actual del servidor.
int MSG_MAX_SIZE = 1024;	// Tamaño del buffer de mensajes.
int MAX_CLIENTS = 6;	// Tamaño del buffer de mensajes.


//esta estructura se usa para enviar mensajes 
struct Message {
    char sender[32];
    char receiver[32] = {0};
    char data[1024];
};


//estructura que se usa para identificar los sockets en el server
struct Connection{
    int socket = 0;
    char owner[32] = {0};
};
