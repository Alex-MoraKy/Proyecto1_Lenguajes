#include "prototipos.h"

TextView *text_view;
RefPtr<TextBuffer> text_buffer;
Entry *entry;
string contacto_actual;

// Función para enviar mensajes
void boton_enviar_clicked() {
    string mensaje = entry->get_text();
    if (!mensaje.empty()) {
        ustring formato_mensaje = "<span foreground='blue'><b>Tú:</b> " + mensaje + "</span>\n";
        text_buffer->insert_markup(text_buffer->end(), formato_mensaje);
        entry->set_text("");
    }
}

// Función para recibir mensajes
void recibir_mensaje(string mensaje) {
    ustring formato_mensaje = "<span foreground='green'><b>" + contacto_actual + ":</b> " + mensaje + "</span>\n";
    text_buffer->insert_markup(text_buffer->end(), formato_mensaje);
}

// Función para crear la ventana de chat
Box* v_chat(string contacto) {
    contacto_actual = contacto; // Guardamos el nombre del contacto

    Box *vbox = manage(new Box(ORIENTATION_VERTICAL, 5));

    text_view = manage(new TextView());
    text_view->set_editable(false);
    text_buffer = TextBuffer::create();
    text_view->set_buffer(text_buffer);

    ScrolledWindow *scroll = manage(new ScrolledWindow());
    scroll->set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);
    scroll->add(*text_view);

    entry = manage(new Entry());
    Button *boton_enviar = manage(new Button("Enviar"));
    boton_enviar->signal_clicked().connect(sigc::ptr_fun(&boton_enviar_clicked));

    Button *boton_volver = manage(new Button("Volver"));
    boton_volver->signal_clicked().connect([]() {
        cambiar_contenido(v_contactos());  // Regresa a la lista de contactos
    });

    Box *hbox = manage(new Box(ORIENTATION_HORIZONTAL, 5));
    hbox->pack_start(*entry);
    hbox->pack_start(*boton_enviar, PACK_SHRINK);
    hbox->pack_start(*boton_volver, PACK_SHRINK);

    vbox->pack_start(*scroll);
    vbox->pack_start(*hbox, PACK_SHRINK);
    recibir_mensaje("holaaa");
    return vbox;
}
