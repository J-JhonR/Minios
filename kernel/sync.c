#include "kernel.h"

/* Mutex simulé */
static int mutex_locked = 0;
static int owner_pid = -1;

void mutex_lock() {
    if (mutex_locked) {
        print("Mutex deja verrouille. Attente...\n");
    } else {
        mutex_locked = 1;
        owner_pid = 1; // processus courant simulé
        print("Mutex verrouille par le processus.\n");
        log_event("MUTEX : verrouille");
    }
}

void mutex_unlock() {
    if (!mutex_locked) {
        print("Mutex deja libre.\n");
    } else {
        mutex_locked = 0;
        owner_pid = -1;
        print("Mutex libere.\n");
        log_event("MUTEX : libere");
    }
}

void show_mutex_demo() {
    clear_screen();
    print("=== SYNCHRONISATION : MUTEX ===\n\n");
    print("Simulation d'acces a une ressource partagee\n\n");

    print("[1] Verrouiller la ressource\n");
    print("[2] Liberer la ressource\n");
    print("[Q] Quitter\n\n");

    while (1) {
        char c = keyboard_getchar();

        if (c == '1') {
            mutex_lock();
        }
        else if (c == '2') {
            mutex_unlock();
        }
        else if (c == 'q' || c == 'Q') {
            break;
        }
    }
}

