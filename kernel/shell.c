#include "kernel.h"

static void read_cmd(char* buf, int max) {
    int i = 0;
    char c;

    while (i < max - 1) {
        c = keyboard_getchar();

        if (c == '\n') {
            break;
        }
        if (c == '\b' && i > 0) {
            i--;
            print("\b \b");
        }
        else if (c >= ' ' && c <= '~') {
            buf[i++] = c;
            char tmp[2] = {c, 0};
            print(tmp);
        }
    }
    buf[i] = 0;
    print("\n");
}

void shell() {
    char cmd[32];

    clear_screen();
    print("=== MINI-SHELL ===\n");
    print("Tapez 'help' pour la liste des commandes.\n\n");

    while (1) {
        print("> ");
        read_cmd(cmd, 32);

        if (!__builtin_strcmp(cmd, "help")) {
            print("Commandes disponibles :\n");
            print("  help   - afficher l'aide\n");
            print("  ps     - liste des processus\n");
            print("  ticks  - afficher le timer systeme\n");
            print("  log    - journal d'execution\n");
            print("  clear  - nettoyer l'ecran\n");
            print("  exit   - retour au menu\n");
        }
        else if (!__builtin_strcmp(cmd, "ps")) {
            show_process_manager();
        }
        else if (!__builtin_strcmp(cmd, "ticks")) {
            print("Ticks systeme : ");
            char t[4] = {'0' + (timer_get_ticks() % 10), 0};
            print(t);
            print("\n");
        }
        else if (!__builtin_strcmp(cmd, "log")) {
            show_log();
        }
        else if (!__builtin_strcmp(cmd, "clear")) {
            clear_screen();
        }
        else if (!__builtin_strcmp(cmd, "exit")) {
            break;
        }
        else if (cmd[0] != 0) {
            print("Commande inconnue.\n");
        }
    }
}

