
// #include "prototipos.h"

// // --------------------------------------- //
// // Variables Globales
// // ----------------------------------t----- //
// // TextView *text_view;
// // RefPtr<TextBuffer> text_buffer;
// // Entry *entry;

// // --------------------------------------- //
// // Funciones
// // --------------------------------------- //

// /*
// // Función para enviar mensajes
// void boton_enviar_clicked() {
//     string mensaje = entry->get_text();
//     if (!mensaje.empty()) {
//         ustring formato_mensaje = "<span foreground='blue'><b>Tú:</b> " + mensaje + "</span>\n";
//         text_buffer->insert_markup(text_buffer->end(), formato_mensaje);
//         entry->set_text("");
//     }
// }
// // --------------------------------------- //
// // Función para recibir mensajes
// void recibir_mensaje(string mensaje) {
//     ustring formato_mensaje = "<span foreground='green'><b>Contacto:</b> " + mensaje + "</span>\n";
//     text_buffer->insert_markup(text_buffer->end(), formato_mensaje);
// }
// // --------------------------------------- //
// // Función para crear la ventana
// void create_main_window(ApplicationWindow &window) {
//     window.set_title("Chat Usuario");
//     window.set_default_size(400, 300);

//     text_view = manage(new TextView());
//     text_view->set_editable(false);
//     text_buffer = TextBuffer::create();
//     text_view->set_buffer(text_buffer);

//     ScrolledWindow *scroll = manage(new ScrolledWindow());
//     scroll->set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);
//     scroll->add(*text_view);

//     entry = manage(new Entry());
//     Button *boton_enviar = manage(new Button("Enviar"));
//     boton_enviar->signal_clicked().connect(sigc::ptr_fun(&boton_enviar_clicked));


//     Box *hbox = manage(new Box(ORIENTATION_HORIZONTAL, 5));
//     hbox->pack_start(*entry);
//     hbox->pack_start(*boton_enviar, PACK_SHRINK);

//     Box *vbox = manage(new Box(ORIENTATION_VERTICAL, 5));
//     vbox->pack_start(*scroll);
//     vbox->pack_start(*hbox, PACK_SHRINK);

//     window.add(*vbox);
//     window.show_all_children();

// }

// */

// int ACTUAL_PORT = 8089;     // Puerto del servidor
// int MSG_MAX_SIZE = 1024;    // Tamaño del buffer de mensajes
// int MAX_CLIENTS = 6;        // Número máximo de clientes
// // ApplicationWindow *ventana_activa = nullptr;

// // --------------------------------------- //
// // Función principal


// int main(int argc, char *argv[]) {
//     auto app = Application::create(argc, argv, "com.proyecto1.mensajeria");

//     ventana_principal = new ApplicationWindow();
//     ventana_principal->set_title("Mensajería");
//     ventana_principal->set_default_size(400, 300);

//     cambiar_contenido(v_inicio());  // Iniciar con la pantalla de inicio

//     return app->run(*ventana_principal);
// }


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
