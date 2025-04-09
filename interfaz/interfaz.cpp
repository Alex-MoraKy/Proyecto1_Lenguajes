#include "prototipos.h"

ApplicationWindow* ventana_principal = nullptr;
Box* contenedor_principal = nullptr;

void cambiar_contenido(Box* nuevo_contenido) {
    if (contenedor_principal) {
        ventana_principal->remove();  // Eliminar contenido anterior
    }

    contenedor_principal = nuevo_contenido;
    ventana_principal->add(*contenedor_principal);
    ventana_principal->show_all_children();
}
void ejecutar_ventana(int argc, char* argv[]) {
    auto app = Application::create(argc, argv, "com.proyecto1.mensajeria");
    ventana_principal = new ApplicationWindow();
    ventana_principal->set_title("Mensajería");
    ventana_principal->set_default_size(400, 300);

    cambiar_contenido(v_inicio());  // Inicia con la ventana de inicio

    app->run(*ventana_principal);
}

int main(int argc, char *argv[]) {
    pid_t pid = fork();  // Crear un proceso hijo

    if (pid < 0) {
        cerr << "Error en fork()" << endl;
        return 1;
    }

    if (pid == 0) {
        // **Proceso hijo**: Ejecuta una copia de la ventana
        ejecutar_ventana(argc, argv);
    } else {
        // **Proceso padre**: Ejecuta la otra ventana
        ejecutar_ventana(argc, argv);
    }

    return 0;
}