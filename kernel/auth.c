#include "kernel.h"

static void read_line(char* buf, int max, int hidden) {
    int i = 0;
    char c;

    while (i < max - 1) {
        c = keyboard_getchar();

        if (c == '\n') break;

        if (c == '\b' && i > 0) {
            i--;
            print("\b \b");
        } else if (c >= ' ' && c <= '~') {
            buf[i++] = c;
            if (hidden)
                print("*");
            else {
                char s[2] = {c, 0};
                print(s);
            }
        }
    }

    buf[i] = 0;
    print("\n");
}

int login() {
    char user[16];
    char pass[16];

    print("\n=== AUTHENTIFICATION ===\n");

    print("Utilisateur : ");
    read_line(user, 16, 0);

    print("Mot de passe : ");
    read_line(pass, 16, 1);

    if (!__builtin_strcmp(user, "admin") &&
        !__builtin_strcmp(pass, "admin")) {

        print("\nAcces autorise.\n");
        return 1;
    }

    print("\nAcces refuse.\n");
    return 0;
}

