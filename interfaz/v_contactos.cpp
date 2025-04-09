#include "prototipos.h"

Box* v_contactos() {
    Box* vbox = new Box(Gtk::ORIENTATION_VERTICAL, 5);
    Button* boton_chat1 = new Button("Chat con Contacto 1");
    Button* boton_chat2 = new Button("Chat con Contacto 2");
    Button* boton_volver = new Button("Cerrar Sesión");

    boton_chat1->signal_clicked().connect([]() {
        cambiar_contenido(v_chat("Contacto 1"));  // Abrir chat con Contacto 1
    });

    boton_chat2->signal_clicked().connect([]() {
        cambiar_contenido(v_chat("Contacto 2"));  // Abrir chat con Contacto 2
    });

    boton_volver->signal_clicked().connect([]() {
        cambiar_contenido(v_inicio());  // Cerrar sesión
    });

    vbox->pack_start(*boton_chat1, PACK_SHRINK);
    vbox->pack_start(*boton_chat2, PACK_SHRINK);
    vbox->pack_start(*boton_volver, PACK_SHRINK);

    return vbox;
}
