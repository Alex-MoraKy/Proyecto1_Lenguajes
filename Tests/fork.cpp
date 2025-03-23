#include "../prototipos.h"


int main() {

    pid_t segundoHijo;
    pid_t primerHijo = fork();  // Crear el proceso hijo

    

    if (primerHijo < 0) {
        // Error en la creación del fork
        std::cerr << "Error en fork" << std::endl;
        return 1;
    }

    

    if (primerHijo == 0) {
        std::cout << "Soy el hijo, mi PID es: " << getpid() << std::endl;
        //aqui se ejecutaria por ejemplo la operacion de read 
    } else {
        // Esto se ejecuta en el proceso padre
        std::cout << "Soy el padre, el PID de mi hijo es: " << primerHijo << std::endl;

        //hacemos que el padre cree otro hijo 
        segundoHijo = fork(); 

        if(segundoHijo < 0){
            // Error en la creación del fork
            std::cerr << "Error en fork" << std::endl;
            return 1;
        }

        if (segundoHijo == 0) {
            // Esto se ejecuta en el segundo proceso hijo
            std::cout << "Soy el segundo hijo, mi PID es: " << getpid() << std::endl;
           //aqui se ejecutaria por ejemplo la operacion de send
        }

    }




    return 0;
}