#include "kernel.h"

static void boot_message(const char* msg) {
    print("[OK] ");
    print(msg);
    print("\n");
}

void kernel_main() {
    clear_screen();

    set_color(0x1F);
    print("====================================\n");
    print("           MINI-OS v1.0             \n");
    print("====================================\n");
    set_color(0x07);

    print("Initialisation du systeme...\n\n");

    boot_message("Mode texte VGA actif");
    boot_message("Clavier initialise");
    boot_message("Timer systeme charge");
    boot_message("Journal d'execution pret");
    boot_message("Ordonnanceur initialise");
    boot_message("Modules IPC et synchronisation charges");

    print("\nSysteme pret.\n");
    print("------------------------------------\n\n");

    /* Boucle de securite : tant que le login echoue */
    while (!login()) {
        set_color(0x4F); // rouge clair
        print("\nEchec d'authentification.\n");
        set_color(0x07);
        print("Veuillez reessayer.\n\n");
    }

    /* Succès → nettoyage + menu */
    clear_screen();
    show_main_menu();

    while (1) { }
}

