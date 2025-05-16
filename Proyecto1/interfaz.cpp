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

int main(int argc, char *argv[]) {
    auto app = Application::create(argc, argv, "com.proyecto1.mensajeria");

    ventana_principal = new ApplicationWindow();
    ventana_principal->set_title("Mensajería");
    ventana_principal->set_default_size(400, 300);

    cambiar_contenido(v_inicio());  // Inicia con la ventana de inicio

    return app->run(*ventana_principal);
}