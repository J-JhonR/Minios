#include "kernel.h"

/* Table de processus simulée */
static process_t sched_procs[] = {
    {1, "init",     READY, 3},
    {2, "shell",    READY, 2},
    {3, "logger",   READY, 1},
    {4, "network",  READY, 2}
};

#define SCHED_COUNT (sizeof(sched_procs)/sizeof(process_t))

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

static void draw_sched_table(const char* title) {
    clear_screen();

    set_color(0x1F);
    print("+---------------------------------------------+\n");
    print("| ");
    print(title);
    print("\n+---------------------------------------------+\n\n");
    set_color(0x07);

    print("PID   NOM         PRIO   ETAT\n");
    print("---------------------------------------------\n");

    for (unsigned int i = 0; i < SCHED_COUNT; i++) {
        char pid[2]  = {'0' + sched_procs[i].pid, 0};
        char prio[2] = {'0' + sched_procs[i].priority, 0};

        print(pid);  print("    ");
        print(sched_procs[i].name); print("     ");
        print(prio); print("     ");
        print_state_colored(sched_procs[i].state);
        print("\n");
    }

    print("\nTicks systeme : ");
    char t[2] = {'0' + (timer_get_ticks() % 10), 0};
    print(t);
}

/* ================= FCFS ================= */
void show_scheduler_fcfs() {

    for (unsigned int i = 0; i < SCHED_COUNT; i++)
        sched_procs[i].state = READY;

    for (unsigned int i = 0; i < SCHED_COUNT; i++) {
        sched_procs[i].state = RUNNING;

        timer_tick();
        log_event("FCFS : processus en execution");

        draw_sched_table("ORDONNANCEMENT FCFS");
        print("\nExecution du processus courant...");
        keyboard_getchar();

        sched_procs[i].state = READY;
    }

    log_event("FCFS termine");
    print("\n\nFCFS termine. Appuyez pour revenir au menu...");
    keyboard_getchar();
}

/* ================= ROUND ROBIN ================= */
void show_scheduler_rr() {

    for (unsigned int i = 0; i < SCHED_COUNT; i++)
        sched_procs[i].state = READY;

    const int tours = 2;

    for (int t = 0; t < tours; t++) {
        for (unsigned int i = 0; i < SCHED_COUNT; i++) {
            sched_procs[i].state = RUNNING;

            timer_tick();
            log_event("RR : quantum ecoule");

            draw_sched_table("ORDONNANCEMENT ROUND ROBIN");
            print("\nQuantum ecoule...");
            keyboard_getchar();

            sched_procs[i].state = READY;
        }
    }

    log_event("Round Robin termine");
    print("\n\nRound Robin termine. Appuyez pour revenir au menu...");
    keyboard_getchar();
}

