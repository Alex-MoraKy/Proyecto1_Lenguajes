
#include "prototipos.h"

Box* v_inicio() {
    Box* vbox = new Box(Gtk::ORIENTATION_VERTICAL, 5);
    Label* label_usuario = new Label("Usuario:");
    Entry* entry_usuario = new Entry();
    Label* label_clave = new Label("Contraseña:");
    Entry* entry_clave = new Entry();
    entry_clave->set_visibility(false);

    Button* boton_login = new Button("Iniciar Sesión");
    Button* boton_registro = new Button("Registrarse");

    boton_login->signal_clicked().connect([]() {
        cambiar_contenido(v_contactos());  // Cambia a la ventana de contactos
    });

    boton_registro->signal_clicked().connect([]() {
        cambiar_contenido(v_registro());  // Cambia a la ventana de registro
    });

    vbox->pack_start(*label_usuario, PACK_SHRINK);
    vbox->pack_start(*entry_usuario, PACK_SHRINK);
    vbox->pack_start(*label_clave, PACK_SHRINK);
    vbox->pack_start(*entry_clave, PACK_SHRINK);
    vbox->pack_start(*boton_login, PACK_SHRINK);
    vbox->pack_start(*boton_registro, PACK_SHRINK);

    return vbox;
}
