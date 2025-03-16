#include <gtkmm.h>
#include <iostream>

class ChatWindow : public Gtk::Window {
public:
    ChatWindow() {
        set_title("Mensajería - Proyecto 1");
        set_default_size(400, 300);

        // Configurar el área de mensajes (scroll + texto)
        scroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        text_view.set_editable(false);
        text_buffer = Gtk::TextBuffer::create();
        text_view.set_buffer(text_buffer);
        scroll.add(text_view);

        // Configurar la entrada de texto y el botón
        send_button.set_label("Enviar");
        send_button.signal_clicked().connect(sigc::mem_fun(*this, &ChatWindow::on_send_button_clicked));

        // Agregar elementos a la caja horizontal
        hbox.pack_start(entry);
        hbox.pack_start(send_button, Gtk::PACK_SHRINK);

        // Agregar elementos a la caja vertical
        vbox.pack_start(scroll);
        vbox.pack_start(hbox, Gtk::PACK_SHRINK);

        // Agregar el layout a la ventana
        add(vbox);
        show_all_children();
    }

protected:
    void on_send_button_clicked() {
        std::string message = entry.get_text();
        if (!message.empty()) {
            text_buffer->insert(text_buffer->end(), "Tú: " + message + "\n");
            entry.set_text(""); // Limpiar entrada
        }
    }

private:
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL, 5}; // Caja vertical
    Gtk::ScrolledWindow scroll; // Área desplazable
    Gtk::TextView text_view; // Área de mensajes
    Glib::RefPtr<Gtk::TextBuffer> text_buffer; // Buffer de texto

    Gtk::Box hbox{Gtk::ORIENTATION_HORIZONTAL, 5}; // Caja horizontal
    Gtk::Entry entry; // Campo de entrada
    Gtk::Button send_button; // Botón de enviar
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.proyecto1.mensajeria");
    ChatWindow window;
    return app->run(window);
}
