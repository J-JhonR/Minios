#include "kernel.h"

#define IPC_MAX_MSG 10
#define IPC_MSG_LEN 64

typedef struct {
    int pid;
    char msg[IPC_MSG_LEN];
} ipc_message_t;

static ipc_message_t mailbox[IPC_MAX_MSG];
static int msg_count = 0;

void ipc_send(int pid, const char* msg) {
    if (msg_count >= IPC_MAX_MSG) {
        print("Boite de messages pleine.\n");
        return;
    }

    mailbox[msg_count].pid = pid;

    int i = 0;
    while (msg[i] && i < IPC_MSG_LEN - 1) {
        mailbox[msg_count].msg[i] = msg[i];
        i++;
    }
    mailbox[msg_count].msg[i] = 0;

    msg_count++;
    log_event("IPC : message envoye");
}

void ipc_receive(int pid) {
    clear_screen();
    print("=== RECEPTION IPC ===\n\n");

    int found = 0;

    for (int i = 0; i < msg_count; i++) {
        if (mailbox[i].pid == pid) {
            print("- ");
            print(mailbox[i].msg);
            print("\n");
            found = 1;
        }
    }

    if (!found) {
        print("Aucun message pour ce processus.\n");
    }

    print("\nAppuyez pour revenir...");
    keyboard_getchar();
}

void show_ipc() {
    clear_screen();
    print("=== IPC : FILE DE MESSAGES ===\n\n");
    print("Simulation : messages predefinis\n\n");

    ipc_send(2, "Message du noyau vers shell");
    ipc_send(3, "Journal pret pour lecture");

    print("Messages envoyes.\n");
    print("Lecture pour PID 2 :\n");
    ipc_receive(2);
}

