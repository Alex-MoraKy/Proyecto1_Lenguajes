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

#include <csignal>   	// Manejo de señales (SIGINT y SIGTERM)
#include <cstdlib>		// Funciones generales, gestión de memoria, conversiones y control del programa.

#include <unistd.h>		// Acceso a llamadas del sistema en Unix/Linux (Crear o leer sockets por ejemplo)
#include <netinet/in.h> // Structs y constantes para sockets, especialmente para IPv4.
#include <sys/socket.h> // Funciones de sockets para linux.
#include <arpa/inet.h>  // Manipulación de direcciones IP.

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

int ACTUAL_PORT = 8080;     // Puerto actual del servidor.
int MSG_MAX_SIZE = 1024;	// Tamaño del buffer de mensajes.