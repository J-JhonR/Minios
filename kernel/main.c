#include "kernel.h"

#define NORMAL_COLOR 0x07   // gris
#define SELECT_COLOR 0x1F   // blanc sur bleu
#define TITLE_COLOR  0x1E   // jaune

static const char* menu_items[] = {
    "Gestion des processus",
    "Ordonnancement (FCFS / Round Robin)",
    "Ordonnancement par priorite",
    "Journal d'execution",
    "IPC (communication inter-processus)",
    "Synchronisation (mutex)",
    "Mini-shell de commandes",
    "Quitter"
};

#define MENU_COUNT 8

void draw_menu(int selected) {
    clear_screen();

    /* Titre */
    set_color(TITLE_COLOR);
    print("============================================\n");
    print("               MINI-OS v1.0                 \n");
    print("        Systeme d'exploitation              \n");
    print("============================================\n\n");
    set_color(NORMAL_COLOR);

    print("+------------------------------------------+\n");

    for (int i = 0; i < MENU_COUNT; i++) {

        print("| ");

        if (i == selected) {
            set_color(SELECT_COLOR);
            print("> ");
        } else {
            set_color(NORMAL_COLOR);
            print("  ");
        }

        print(menu_items[i]);

        set_color(NORMAL_COLOR);
        print("\n");
    }

    print("+------------------------------------------+\n");
    print("\nUtilisez les fleches HAUT/BAS et ENTREE\n");
}

void show_main_menu() {
    int selected = 0;

    while (1) {
        draw_menu(selected);
        int sc = keyboard_get_scancode();

        if (sc == 0x48 && selected > 0) {
            selected--;
        }
        else if (sc == 0x50 && selected < MENU_COUNT - 1) {
            selected++;
        }
        else if (sc == 0x1C) { /* ENTREE */

            if (selected == 0) {
                show_process_manager();
            }
            else if (selected == 1) {
                clear_screen();
                print("Choisir l'algorithme :\n\n");
                print("  [1] FCFS\n");
                print("  [2] Round Robin\n\n");
                print("Votre choix : ");

                char c = keyboard_getchar();
                if (c == '1') show_scheduler_fcfs();
                else if (c == '2') show_scheduler_rr();
            }
            else if (selected == 2) {
                show_scheduler_priority();
            }
            else if (selected == 3) {
                show_log();
            }
            else if (selected == 4) {
                show_ipc();
            }
            else if (selected == 5) {
                show_mutex_demo();
            }
            else if (selected == 6) {
                shell();
            }
            else if (selected == 7) {
                clear_screen();
                print("Arret du systeme...\n");
                while (1) { }
            }
        }
    }
}

