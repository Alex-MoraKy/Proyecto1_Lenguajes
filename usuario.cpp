
#include "prototipos.h"

// --------------------------------------- //
// Variables

// --------------------------------------- //
// Funciones

// Verificar credenciales
bool credenciales_correctas(string username, string password) {
    ifstream database("db.txt");

    if (!database) {
        cerr << "Error: No se pudo abrir el archivo de credenciales." << endl;
        return false;
    }

    // Analizar línea por línea y comparar strings
    string linea, usuario, clave;

    while (getline(database, linea)) {
        istringstream ss(linea);  // Convertir línea en flujo
        ss >> usuario;  // Leer el nombre de usuario

        // Lee el resto de la línea como contraseña
        getline(ss, clave);  // Manejando los posibles espacios   

        // Limpiar posibles espacios extra al principio o final de la contraseña
        clave.erase(0, clave.find_first_not_of(" \t")); // Eliminar espacios al principio
        clave.erase(clave.find_last_not_of(" \t") + 1); // Eliminar espacios al final

        // Verificar si el usuario y la contraseña coinciden
        if (usuario == username && clave == password) {
            database.close();
            return true;
        }
    }

    database.close();
    return false;
}

// Crear nuevo usuario
void crear_nuevo_usuario(string username, string password) {
    ifstream lectura_database("db.txt");
    
    // Si el archivo no existe, se creará en la siguiente parte
    if (!lectura_database) {
        cerr << "Nota: El archivo de credenciales no existe, se creará uno nuevo." << endl;
    }

    string linea, usuario, clave;
    while (getline(lectura_database, linea)) {
        istringstream ss(linea);
        ss >> usuario;            // Leer el usuario
        getline(ss, clave);       // Leer el resto de la línea como contraseña

        if (usuario == username) {
            cout << "Error: El usuario ya existe." << endl;
            lectura_database.close();
            return;
        }
    }
    
    lectura_database.close();  // Cerrar archivo antes de abrir en modo escritura

    // Abrir el archivo en modo escritura (append)
    ofstream escritura_database("db.txt", ios::app);
    if (!escritura_database) {
        cerr << "Error: No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    // Verificar si el archivo está vacío antes de agregar una nueva línea
    ifstream check_database("db.txt");
    check_database.seekg(0, ios::end);
    bool archivo_vacio = (check_database.tellg() == 0);
    check_database.close();

    // Si no está vacío, añadir un salto de línea antes del nuevo usuario
    if (!archivo_vacio) {
        escritura_database << "\n";
    }

    // Escribir usuario y contraseña en un nuevo renglón
    escritura_database << username << " " << password;
    escritura_database.close();
    
}

// --------------------------------------- //
// Usuario
int main() {

	// Iniciar sesión o login
	string comando_consola;
	string username, password;

	cout << ">>> ";
	cin >> comando_consola;

	if (comando_consola == "login") {
        cout << "Usuario: ";
        cin >> username;
        cout << "Contraseña: ";
        cin >> password;

        if (!credenciales_correctas(username, password)) {
            cout << "Error: Credenciales incorrectas." << endl;
            return 1; // Indicar error en la ejecución
        }

        cout << "Inicio de sesión exitoso." << endl;

    } else if (comando_consola == "register") {
        cout << "Nuevo Usuario: ";
        cin >> username;
        cout << "Contraseña: ";
        cin >> password;

        crear_nuevo_usuario(username, password);
        cout << "Usuario registrado con éxito." << endl;

    } else {
        cout << "Error: Comando desconocido." << endl;
        return 1;
    }

	int user_socket = 0;                // Descriptor de archivo del socket
    struct sockaddr_in user_address;    // Estructura para almacenar la dirección del usuario
    char buffer[MSG_MAX_SIZE] = {0};    // Buffer para recibir datos del servidor
    string message;                     // Mensaje que enviará el cliente

    while (true) {
	    // --------------------------------------- //
        // Pedir mensaje al usuario
        cout << "Ingrese el mensaje a enviar: ";

        // Stringstream para almacenar todo el mensaje (getline da problemas)
        string word;
        stringstream message_stream;  

        // Leer palabra por palabra hasta que el usuario presione Enter
        while (cin >> word) {
            // Concatenar las palabras con un espacio
            message_stream << word << " ";  
            if (cin.peek() == '\n') {  // Termina la lectura con un '\n'
                break;
            }
        }

        // Asignar el stringstream al mensaje
        string message = message_stream.str();		
        
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
	    // cout << "Mensaje enviado." << endl;

	    // Recibir la respuesta del servidor
	    read(user_socket, buffer, MSG_MAX_SIZE);
	    // cout << "Respuesta del servidor: " << buffer << endl;

	}

    // Cerrar el socket
    close(user_socket);

    return 0;
}