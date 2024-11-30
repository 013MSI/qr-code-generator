#include "constants.h"
#include "qrActions.h"
#include "Menu.h"
#include "fmt/color.h"
#include <iostream>
#include <string>

using namespace std;

void welcome();
void exit();

int main() {
    // create menu
    Menu menu;
    menu.addItem('g', "🛠  Generate")
        ->addItem('s', "🔍 Scan")
        ->addItem('q', "⤵️  Quit");

    // print banner
    welcome();

    // print menu for the first time and get action
    fmt::print(fmt::emphasis::underline, "Pick an action to get started\n");
    menu.print();
    char option = menu.getOption();

    // do action
    while (option != QUIT) {
        if (option == GENERATE) {
            generate();
        } else if (option == SCAN) {
            scan();
        }
        // print menu and get action
        fmt::print(fmt::emphasis::underline, "\nActions\n");
        menu.print();
        option = menu.getOption();
    }

    // print exit message
    exit();

    return 0;
}

void welcome() {
    // SOURCE: https://patorjk.com/software/taag/#p=display&f=Bulbhead&t=yin-yang%0A
    // DESCRIPTION: ascii art generator
    // used ChatGPT to create cout statements for the art generated using the above source
    cout << " _  _  ____  _  _       _  _    __    _  _   ___     ___    __    ____  ___ \n";
    cout << "( \\/ )(_  _)( \\( ) ___ ( \\/ )  /__\\  ( \\( ) / __)   / __)  /__\\  (_  _)/ __)\n";
    cout << " \\  /  _)(_  )  ( (___) \\  /  /(__)\\  )  ( ( (_-.  ( (__  /(__)\\   )(  \\__ \\\n";
    cout << " (__) (____)(_)\\_)      (__) (__)(__)(_)\\_) \\___/   \\___)(__)(__) (__) (___/\n\n";
    cout << "                       😼 QR Code Generator & Scanner\n\n";
    cout << "                   Create colorful QR codes quickly and easily\n\n";
}

void exit() {
    cout << "\n😼 Exited QR Code Generator & Scanner.\n\n";
}
