#ifndef KERNEL_H
#define KERNEL_H

void clear_screen();
void print(const char* str);
void set_color(unsigned char color);
																

/* clavier */
char keyboard_getchar();
int keyboard_get_scancode();


/* auth */
int login();

void show_main_menu();
/* Processus */
typedef enum {
    READY,
    RUNNING,
    WAITING
} process_state_t;

typedef struct {
    int pid;
    const char* name;
    process_state_t state;
    int priority;   /* plus grand = plus prioritaire */
} process_t;
void show_process_manager();

/* Ordonnancement */
void show_scheduler_fcfs();
void show_scheduler_rr();

/* Timer */
void timer_tick();
unsigned int timer_get_ticks();

/* Journal */
void log_event(const char* msg);
void show_log();

/* Shell */
void shell();

/* Priorite*/
void show_scheduler_priority();

/* IPC - file de messages */
void ipc_send(int pid, const char* msg);
void ipc_receive(int pid);
void show_ipc();

/* Synchronisation (mutex) */
void mutex_lock();
void mutex_unlock();
void show_mutex_demo();

/* Synchronisation (mutex) */
void mutex_lock();
void mutex_unlock();
void show_mutex_demo();


#endif

