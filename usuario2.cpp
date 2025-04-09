
#include "prototipos.h"
#include "variables.h"

/*
Es lo mismo que usario.cpp solo que ahora recibe y envia mensajes ya que cree dos procesos con el fork
*/

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


bool VerificarExistencia(string username){
    ifstream database("db.txt");

    if (!database) {
        cerr << "Error: No se pudo abrir el archivo de credenciales." << endl;
        return false;
    }

    // Analizar línea por línea y comparar strings
    string linea, usuario;

    while (getline(database, linea)) {
        istringstream ss(linea);  // Convertir línea en flujo
        ss >> usuario;  // Leer el nombre de usuario

        // Verificar si el usuario y la contraseña coinciden
        if (usuario == username) {
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

//establece conexion a un socket 
int EstablecerConexion(int* userSocket, struct sockaddr_in* serverAddress) 
{
    // --------------------------------------- //
	// Crear el socket del cliente
	*userSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (*userSocket < 0) {
	    cerr << "Error al crear el socket" << endl;
	    return -1;
	}

	// --------------------------------------- //
	// Configurar la dirección del servidor
	serverAddress->sin_family = AF_INET;  				// Tipo de dirección: IPv4
	serverAddress->sin_port = htons(ACTUAL_PORT);  		// Convertir el puerto al formato de red

	// --------------------------------------- //
	// Detección de errores

	// Dirección IP de texto a binario el servidor 
	if (inet_pton(AF_INET, "127.0.0.1", &serverAddress->sin_addr) <= 0) {
	    cerr << "Dirección inválida o no soportada" << endl;
	    return -1;
	}

	// Conectar al servidor
	if (connect(*userSocket, (struct sockaddr*)serverAddress, sizeof(*serverAddress)) < 0) {
	    cerr << "Conexión fallida" << endl;
	    return -1;
	}

    //en caso de exito 
    return 0; 
}

void mostrarEncabezadoChat(string destinatario) {
    cout << "\n===============================\n";
    cout << "==   CHATEANDO CON: " << destinatario << "\n";
    cout << "===============================\n" << endl;
}

void ReceiveMessages(int* userSocket)
{
    while(1){

    char buffer[1024]; 
    int bytes_received;

    // Leer del socket
    bytes_received = read(*userSocket, buffer, MSG_MAX_SIZE); // Leer los datos del socket
    if (bytes_received < 0) {
        perror("Error al leer del socket");
        break;
    }
    // Limpiar la línea donde se esté escribiendo
    cout << "\033[2K\r"; // borra la línea actual

    // Imprimir el mensaje recibido en azul
    cout << "\033[1;34m" << buffer << "\033[0m" << endl;

    // Volver a imprimir el prompt, bien alineado
    cout << "Ingrese el mensaje a enviar:" << flush;


    }
    
    cout << "ya no recibe" << endl; 
    close(*userSocket);
}


//recibe de la linea de comandos mensajes y luego los envia al server 

void SendMessages(int* userSocket, string sender, string receiver)
{

    // se usará una estructura msg para enviar los mensajes,
    Message msg;
    strcpy(msg.sender, sender.c_str());
    strcpy(msg.receiver, receiver.c_str());

    while (true)
    {   
        cout << "Ingrese el mensaje a enviar: " << flush;
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
        
        //metemos el mensaje en la estructura creada previamente
        strcpy(msg.data, message.c_str()); 

        //se envía un puntero a donde se ubica el mensaje 
        ssize_t bytesSent = send(*userSocket, &msg, sizeof(msg), 0);

        if (bytesSent < 0) {
            printError("Error al enviar el mensaje");
            exit(-1); 
        }
        cout << "\033[1A\033[2K\r";
        cout << "\033[2K\r"; // Limpiar línea
        cout << "\033[1;32m" << sender << ": " << message << "\033[0m" << endl;

    }

    cout << "nos salimos" <<endl; 
    close(*userSocket);
}


void mostrarMenu() {
    cout << "\n=============================\n";
    cout << "==         M E N U         ==\n";
    cout << "=============================\n";
    cout << "1. Iniciar sesion\n";
    cout << "2. Registrarse\n";
    cout << "3. Salir\n";
    cout << "Opción: ";
}

void printError(string mensaje) {
    cout << "\033[1;31m" << mensaje << "\033[0m\n";
}

int IniciarMensajeria(string username) {
    //definir a quien enviar mensajes 
    
    cout <<endl; 
    string receiver;
    cout << "Usuario a enviar mensajes: ";
    cin >> receiver;

    if(!VerificarExistencia(receiver)){
        cout << "Error: El usuario no existe en sus contactos." << endl;
        return 1; // Indicar error en la ejecución
    }

    mostrarEncabezadoChat(receiver);

    //definimos un sockaddr_in para guardar la direccion del server 
    struct sockaddr_in serverAddress;    

    //Ahora iniciaremos dos procesos, uno que reciba mensajes, y el otro que los envie 
    //creamos el primer proceso hijo
    pid_t segundoHijo;
    pid_t primerHijo = fork();  


    //revisammos que no haya error en la creacion
    if (primerHijo < 0) {
        printError("Error en fork");
        return 1;
    }

    //si arroja 0 es que es el primer hijo, aquí ejecutaremos el "sender"
    if (primerHijo == 0) {

        int sendSocket = 0;                

        //string para enviar al servidor de que este socket solo envia y no recibe
        string sender = "sender";

        //Ahora establecmos conexion por medio de esta funcion 
        int resultCode = EstablecerConexion(&sendSocket, &serverAddress);

        //aquí se manda un mensaje para que el server vea quien es el 
        //que esta enviando, en este caso como es el sender es trivial saber quien es
        //por lo que solo se manda "sender"

        //lo importante va en los metadatos del Message

        send(sendSocket, sender.c_str(), sizeof(sender.c_str()), 0);

        if(resultCode){
            printError("Error: no se puedo dar la conexión");
            return 1; 
        }

        //esta funcion se encarga de enviar mensajes, recibe el socket creado, y 
        //el user que envia y al que le envian
        SendMessages(&sendSocket, username, receiver); 

    } else {
        //hacemos que el padre cree otro hijo 
        segundoHijo = fork(); 
            
        //revisammos que no haya error en la creacion
        if(segundoHijo < 0){
            printError("Error en fork");
            return 1;
        }
            
        //si arroja 0 es que es el segundo hijo, aquí ejecutaremos el "receiver"
        if (segundoHijo == 0) {

        
            int receiveSocket = 0;       

            //Ahora establecmos conexion por medio de esta funcion 
            int resultCode = EstablecerConexion(&receiveSocket, &serverAddress);

            //aquí se manda un mensaje para que el server vea quien es el 
            //socket donde se está recibiendo mensajes.
            send(receiveSocket, username.c_str(), sizeof(username.c_str()), 0);

            if(resultCode){
                printError("Error: no se puedo dar la conexión");
                return 1; 
            }

            //esta funcion se encarga de enviar mensajes, recibe el socket creado, y 
            //el user que envia y al que le envian
            ReceiveMessages(&receiveSocket); 
                
        } else{
            //con esto no cierra el socket hasta que los hijos culminen
            waitpid(segundoHijo, NULL, 0);
            waitpid(primerHijo, NULL, 0);
            cout <<"culminaron " <<primerHijo << " "<< segundoHijo << endl;
            cout << "se cerro el socket" << endl;
        }
    }

    return 0;
}


// --------------------------------------- //
// Usuario
int main(int argc, char *argv[]) {
    int retornar = 0;
    int opcion;
    string username, password;
    bool salir = false;

    while (!salir) {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Usuario: ";
                cin >> username;
                cout << "Contraseña: ";
                cin >> password;

                if (!credenciales_correctas(username, password)) {
                    printError("Error: Credenciales incorrectas.");
                    break;
                }
                retornar = IniciarMensajeria(username);

                break;
            case 2:
                cout << "Nuevo Usuario: ";
                cin >> username;
                cout << "Contraseña: ";
                cin >> password;
        
                crear_nuevo_usuario(username, password);
                cout << "Usuario registrado con éxito." << endl;
                break;
            case 3:
                salir = true;
                cout << "Saliendo...\n";
                break;
            default:
                printError("Opción no válida :(. Intente de nuevo.");
                break;
        }

    }


	// // Iniciar sesión o login
	// string comando_consola;
	// string username, password;
    
	// cout << ">>> ";
	// cin >> comando_consola;
    
	// if (comando_consola == "login") {
    //     cout << "Usuario: ";
    //     cin >> username;
    //     cout << "Contraseña: ";
    //     cin >> password;

    //     if (!credenciales_correctas(username, password)) {
    //         cout << "Error: Credenciales incorrectas." << endl;
    //         return 1; // Indicar error en la ejecución
    //     }

    //     cout << "Inicio de sesión exitoso." << endl;

    // } else if (comando_consola == "register") {
    //     cout << "Nuevo Usuario: ";
    //     cin >> username;
    //     cout << "Contraseña: ";
    //     cin >> password;

    //     crear_nuevo_usuario(username, password);
    //     cout << "Usuario registrado con éxito." << endl;

    // } else {
    //     cout << "Error: Comando desconocido." << endl;
    //     return 1;
    // }

    // //definir a quien enviar mensajes 
    // cout <<endl; 
    // string receiver;
	// cout << "Usuario a enviar mensajes: ";
	// cin >> receiver;

    // if(!VerificarExistencia(receiver)){
    //     cout << "Error: El usuario no existe en sus contactos." << endl;
    //     return 1; // Indicar error en la ejecución
    // }

    // //definimos un sockaddr_in para guardar la direccion del server 
    // struct sockaddr_in serverAddress;    

    // //Ahora iniciaremos dos procesos, uno que reciba mensajes, y el otro que los envie 
    // //creamos el primer proceso hijo
    // pid_t segundoHijo;
    // pid_t primerHijo = fork();  

    
    // //revisammos que no haya error en la creacion
    // if (primerHijo < 0) {
    //     std::cerr << "Error en fork" << std::endl;
    //     return 1;
    // }

  
    // //si arroja 0 es que es el primer hijo, aquí ejecutaremos el "sender"
    // if (primerHijo == 0) {

    //     int sendSocket = 0;                

    //     //string para enviar al servidor de que este socket solo envia y no recibe
    //     string sender = "sender";

    //     //Ahora establecmos conexion por medio de esta funcion 
    //     int resultCode = EstablecerConexion(&sendSocket, &serverAddress);

    //     //aquí se manda un mensaje para que el server vea quien es el 
    //     //que esta enviando, en este caso como es el sender es trivial saber quien es
    //     //por lo que solo se manda "sender"

    //     //lo importante va en los metadatos del Message

    //     send(sendSocket, sender.c_str(), sizeof(sender.c_str()), 0);

    //     if(resultCode){
    //         cerr <<"no se puedo dar la conexión"<<endl;
    //         return 1; 
    //     }

    //     //esta funcion se encarga de enviar mensajes, recibe el socket creado, y 
    //     //el user que envia y al que le envian
    //     SendMessages(&sendSocket, username, receiver); 

    // } else {
    //     //hacemos que el padre cree otro hijo 
    //     segundoHijo = fork(); 
            
    //     //revisammos que no haya error en la creacion
    //     if(segundoHijo < 0){
    //         std::cerr << "Error en fork" << std::endl;
    //         return 1;
    //     }
            
    //     //si arroja 0 es que es el segundo hijo, aquí ejecutaremos el "receiver"
    //     if (segundoHijo == 0) {

        
    //         int receiveSocket = 0;       

    //         //Ahora establecmos conexion por medio de esta funcion 
    //         int resultCode = EstablecerConexion(&receiveSocket, &serverAddress);

    //         //aquí se manda un mensaje para que el server vea quien es el 
    //         //socket donde se está recibiendo mensajes.
    //         send(receiveSocket, username.c_str(), sizeof(username.c_str()), 0);

    //         if(resultCode){
    //             cerr <<"no se puedo dar la conexión"<<endl;
    //             return 1; 
    //         }

    //         //esta funcion se encarga de enviar mensajes, recibe el socket creado, y 
    //         //el user que envia y al que le envian
    //         ReceiveMessages(&receiveSocket); 
                
    //     } else{
    //         //con esto no cierra el socket hasta que los hijos culminen
    //         waitpid(segundoHijo, NULL, 0);
    //         waitpid(primerHijo, NULL, 0);
    //         cout <<"culminaron " <<primerHijo << " "<< segundoHijo << endl;
    //         cout << "se cerro el socket" << endl;
    //     }
	// }

    

    return retornar;
}

