
#include "prototipos.h"

// --------------------------------------- //
// Variables Globales
// --------------------------------------- //
TextView *text_view;
RefPtr<TextBuffer> text_buffer;
Entry *entry;

// --------------------------------------- //
// Funciones
// --------------------------------------- //

// Función para enviar mensajes
void on_send_button_clicked() {
    string message = entry->get_text();
    if (!message.empty()) {
        ustring formatted_message = "<span foreground='blue'><b>Tú:</b> " + message + "</span>\n";
        text_buffer->insert_markup(text_buffer->end(), formatted_message);
        entry->set_text("");
    }
}
// --------------------------------------- //
// Función para recibir mensajes
void recibir_mensaje(const string& mensaje) {
    ustring formatted_message = "<span foreground='green'><b>Contacto:</b> " + mensaje + "</span>\n";
    text_buffer->insert_markup(text_buffer->end(), formatted_message);
}
// --------------------------------------- //
// Función para crear la ventana
void create_main_window(ApplicationWindow &window) {
    window.set_title("Mensajería - Proyecto 1");
    window.set_default_size(400, 300);

    text_view = manage(new TextView());
    text_view->set_editable(false);
    text_buffer = TextBuffer::create();
    text_view->set_buffer(text_buffer);

    ScrolledWindow *scroll = manage(new ScrolledWindow());
    scroll->set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);
    scroll->add(*text_view);

    entry = manage(new Entry());
    Button *send_button = manage(new Button("Enviar"));
    send_button->signal_clicked().connect(sigc::ptr_fun(&on_send_button_clicked));


    Box *hbox = manage(new Box(ORIENTATION_HORIZONTAL, 5));
    hbox->pack_start(*entry);
    hbox->pack_start(*send_button, PACK_SHRINK);

    Box *vbox = manage(new Box(ORIENTATION_VERTICAL, 5));
    vbox->pack_start(*scroll);
    vbox->pack_start(*hbox, PACK_SHRINK);

    window.add(*vbox);
    window.show_all_children();

    recibir_mensaje("¡Hola! ¿Cómo estás?");
}

// Función principal
int main(int argc, char *argv[]) {
    auto app = Application::create(argc, argv, "com.proyecto1.mensajeria");
    ApplicationWindow window;
    create_main_window(window);
    return app->run(window);
}
