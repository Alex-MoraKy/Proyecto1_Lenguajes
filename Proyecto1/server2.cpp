#include "prototipos.h"
#include "variables.h"



int main() {

    ///flag
    struct Connection clients[MAX_CLIENTS] = {0}; 
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    fd_set readfds;

    //Con esto se crea el socket para acceder al servidor desde afuera
    //el socket pasivo
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //Configurar la dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //Aceptar conexiones de cualquier dirección IP
    address.sin_port = htons(ACTUAL_PORT); //Puerto en el que el servidor escuchará


    //Asociar el socket con la dirección configurada antes
    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //Escuchar las conexiones entrantes, 3 en espera 
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Escuchando... Puerto actual: " << ACTUAL_PORT << endl;

    while (true) {
        // Limpiar el conjunto de descriptores de archivo
        //FD == File descriptor 
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds); // Añadir el socket del servidor al conjunto de descriptores

        int max_sd = server_fd;

        // Añadir los sockets de los clientes al conjunto de descriptores
        for (int i = 0; i < MAX_CLIENTS; i++) {

            int sd = clients[i].socket;
            cout << "se tiene el socket: " << sd << " de: "<< clients[i].owner <<endl; 
            

            if (sd > 0) {
                //se añade el socket al set de sockets en readfds
                FD_SET(sd, &readfds);
            }
            if (sd > max_sd) {
                max_sd = sd;
            }
        }
        cout << endl; 
        
        
        // Usar select para esperar actividad en los sockets
        if (select(max_sd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("select error");
            exit(EXIT_FAILURE);
        }

        //Verificar si hay una nueva conexión entrante
        if (FD_ISSET(server_fd, &readfds)) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("accept failed");
                continue;
            }

            //una vez aceptada la conexion el cliente manda un mensaje para identificarse, 
            char client[32] = {0};
            int valread = read(new_socket, client, sizeof(client));

            cout << "llego el usuario: " << client <<endl<<endl;
            
            // Añadir el nuevo socket a la lista de sockets de clientes
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i].socket == 0) {

                    /*aqui se agarra un espacio en blanco en el array y se le asigna un 
                    nuevo cliente 
                    
                    si es un socket de recibir tendra el nombre del usuario, si es uno de enviar
                    tan solo dira "sender"*/           
                    clients[i].socket = new_socket;
                    strcpy(clients[i].owner, client);
                    break;
                }
            }
        }

        // Verificar si alguno de los clientes tiene datos para leer
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = clients[i].socket;

            // El ISSET arroja 0 si no es parte del set de FileDescriptors
            // y otro numero si tiene un mensaje o quiere realizar una accion

            if (FD_ISSET(sd, &readfds)) {

                //ahora desreferenciamos el msg que nos llegó 
                Message msg;
                int valread = read(sd, &msg, sizeof(msg));

                if (valread == 0) {
                    // El cliente cerró la conexión
                    cout << "Cliente desconectado: " << clients[i].owner << endl;
                    close(sd);
                    clients[i].socket = 0;  // Eliminar cliente de la lista
                    strcpy(clients[i].owner, "");

                } else {
                    // Imprimir el mensaje recibido del cliente
                    cout << "Mensaje de cliente " << clients[i].owner << ": " << msg.data << "para: " << msg.receiver << endl;

                    //ahora enviemos el mensaje a dicha persona; 
                    
                    for (int j = 0; j < MAX_CLIENTS; j++){


                        if(strcmp(clients[j].owner, msg.receiver) == 0){
                            //ya que se identifico el usuario se le envia el mensaje
                            
                            string wholeMsg = string(msg.sender) + ": " +string(msg.data); 
                            
                            cout << "el mensaje completo es: " << wholeMsg << endl; 

                            ssize_t bytesSent = send(clients[j].socket, wholeMsg.c_str(), MSG_MAX_SIZE, 0); 
                            cout <<"se enviaron: " << bytesSent << " bytes" << endl; 
                            if (bytesSent < 0) {
                                cout << "Error al enviar el mensaje" << endl;
                                exit(-1); 
                            }
                            cout << "se envió el mensaje de: " << msg.sender << " a " << msg.receiver <<endl; 
                        }

                    }

                }
            }
        }
    }

    return 0;
}
