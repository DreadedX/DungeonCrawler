#include "Game.h"
#include "util/Log.h"
// #include <gtkmm/main.h>
// #include <gtkmm/messagedialog.h>

int main() {
    // Gtk::Main kit(argc, argv);
    // Gtk::MessageDialog Hello("Hello world!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
    // Hello.set_secondary_text("This is an example diablog");
    // Hello.run();

    // This is placholder launcher code
    char test[] = "Launching game";
    Log::print(test, DEBUG);
    Game::init();

    return 0;
}
