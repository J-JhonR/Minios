#include "kernel.h"

static process_t processes[] = {
    {1, "init",     RUNNING, 3},
    {2, "shell",    READY,   2},
    {3, "logger",   WAITING, 1},
    {4, "network",  READY,   2}
};

#define PROC_COUNT (sizeof(processes)/sizeof(process_t))

static const char* state_to_str(process_state_t s) {
    switch (s) {
        case READY:   return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        default:      return "UNKNOWN";
    }
}

static void print_state_colored(process_state_t state) {
    if (state == RUNNING)
        set_color(0x2F);   // vert
    else if (state == READY)
        set_color(0x07);   // gris
    else
        set_color(0x6F);   // jaune

    print(state_to_str(state));
    set_color(0x07);
}

void show_process_manager() {
    clear_screen();

    set_color(0x1F);
    print("+---------------------------------------------+\n");
    print("|        GESTION DES PROCESSUS                |\n");
    print("+---------------------------------------------+\n\n");
    set_color(0x07);

    print("PID   NOM         PRIO   ETAT\n");
    print("---------------------------------------------\n");

    for (unsigned int i = 0; i < PROC_COUNT; i++) {
        char pid[2]  = {'0' + processes[i].pid, 0};
        char prio[2] = {'0' + processes[i].priority, 0};

        print(pid);  print("    ");
        print(processes[i].name); print("     ");
        print(prio); print("     ");
        print_state_colored(processes[i].state);
        print("\n");
    }

    print("\nAppuyez sur une touche pour revenir au menu...");
    keyboard_getchar();
}

