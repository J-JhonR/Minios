#include "kernel.h"

#define LOG_MAX 32
#define LOG_LEN 64

static char logs[LOG_MAX][LOG_LEN];
static int log_index = 0;

void log_event(const char* msg) {
    int i = 0;
    while (msg[i] && i < LOG_LEN - 1) {
        logs[log_index][i] = msg[i];
        i++;
    }
    logs[log_index][i] = 0;

    log_index = (log_index + 1) % LOG_MAX;
}

void show_log() {
    clear_screen();
    print("========= JOURNAL D'EXECUTION =========\n\n");

    for (int i = 0; i < LOG_MAX; i++) {
        if (logs[i][0] != 0) {
            print("- ");
            print(logs[i]);
            print("\n");
        }
    }

    print("\nAppuyez sur une touche pour revenir...");
    keyboard_getchar();
}

