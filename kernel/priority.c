#include "kernel.h"

/* Table de processus avec priorités */
static process_t prio_procs[] = {
    {1, "init",     READY, 3},
    {2, "shell",    READY, 1},
    {3, "logger",   READY, 2},
    {4, "network",  READY, 4}
};

#define PRIO_COUNT (sizeof(prio_procs)/sizeof(process_t))

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

static void draw_prio_table() {
    clear_screen();

    set_color(0x1F);
    print("+---------------------------------------------+\n");
    print("|     ORDONNANCEMENT PAR PRIORITE             |\n");
    print("+---------------------------------------------+\n\n");
    set_color(0x07);

    print("PID   NOM         PRIO   ETAT\n");
    print("---------------------------------------------\n");

    for (unsigned int i = 0; i < PRIO_COUNT; i++) {
        char pid[2]  = {'0' + prio_procs[i].pid, 0};
        char prio[2] = {'0' + prio_procs[i].priority, 0};

        print(pid);  print("    ");
        print(prio_procs[i].name); print("     ");
        print(prio); print("     ");
        print_state_colored(prio_procs[i].state);
        print("\n");
    }

    print("\nTicks systeme : ");
    char t[2] = {'0' + (timer_get_ticks() % 10), 0};
    print(t);
}

void show_scheduler_priority() {

    /* remettre tous les processus en READY */
    for (unsigned int i = 0; i < PRIO_COUNT; i++)
        prio_procs[i].state = READY;

    for (unsigned int step = 0; step < PRIO_COUNT; step++) {

        int max_prio = -1;
        int idx = -1;

        /* selection du processus READY le plus prioritaire */
        for (unsigned int i = 0; i < PRIO_COUNT; i++) {
            if (prio_procs[i].state == READY &&
                prio_procs[i].priority > max_prio) {
                max_prio = prio_procs[i].priority;
                idx = i;
            }
        }

        if (idx == -1)
            break;

        prio_procs[idx].state = RUNNING;

        timer_tick();
        log_event("PRIORITE : processus en execution");

        draw_prio_table();
        print("\nExecution du processus prioritaire...\n");
        keyboard_getchar();

        prio_procs[idx].state = WAITING;
    }

    log_event("Ordonnancement par priorite termine");
    print("\n\nOrdonnancement par priorite termine.\n");
    print("Appuyez pour revenir au menu...");
    keyboard_getchar();
}

