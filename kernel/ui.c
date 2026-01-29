#include "kernel.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
void set_color(unsigned char c);

static unsigned short* vga = (unsigned short*)0xB8000;
static int row = 0;
static int col = 0;
static unsigned char color = 0x07; // gris clair sur fond noir

static void put_char(char c) {

    /* Retour à la ligne */
    if (c == '\n') {
        col = 0;
        row++;
        return;
    }

    /* Backspace */
    if (c == '\b') {
        if (col > 0) {
            col--;
            vga[row * VGA_WIDTH + col] = (color << 8) | ' ';
        }
        return;
    }

    if (row >= VGA_HEIGHT)
        return;

    vga[row * VGA_WIDTH + col] = (color << 8) | c;
    col++;

    if (col >= VGA_WIDTH) {
        col = 0;
        row++;
    }
}

void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = (color << 8) | ' ';
    }

    row = 0;
    col = 0;
}

void print(const char* str) {
    while (*str) {
        put_char(*str++);
    }
}

void set_color(unsigned char c) {
    color = c;
}


