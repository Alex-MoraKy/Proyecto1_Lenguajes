
#include "prototipos.h"

Box* v_registro() {
    Box* vbox = new Box(Gtk::ORIENTATION_VERTICAL, 5);
    Label* label_usuario = new Label("Nuevo Usuario:");
    Entry* entry_usuario = new Entry();
    Label* label_clave = new Label("Nueva Contraseña:");
    Entry* entry_clave = new Entry();
    entry_clave->set_visibility(false);

    Button* boton_registrar = new Button("Registrar");
    Button* boton_volver = new Button("Volver");

    boton_volver->signal_clicked().connect([]() {
        cambiar_contenido(v_inicio());  // Regresar a inicio
    });

    vbox->pack_start(*label_usuario, PACK_SHRINK);
    vbox->pack_start(*entry_usuario, PACK_SHRINK);
    vbox->pack_start(*label_clave, PACK_SHRINK);
    vbox->pack_start(*entry_clave, PACK_SHRINK);
    vbox->pack_start(*boton_registrar, PACK_SHRINK);
    vbox->pack_start(*boton_volver, PACK_SHRINK);

    return vbox;
}