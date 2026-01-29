#include "kernel.h"

/*
 * Keymap QWERTY US (scancodes Set 1)
 * Sans Shift (simplifié, volontairement)
 */
static unsigned char keymap[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,  'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,  '\\','z','x','c','v','b','n','m',',','.','/',
    0,  '*', 0,  ' '
};

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/*
 * Lecture clavier simple :
 * - 1 pression = 1 caractère
 * - pas de répétition infinie
 */
char keyboard_getchar() {
    unsigned char sc;

    /* attendre une touche pressée */
    do {
        sc = inb(0x60);
    } while (sc & 0x80);

    /* attendre le relâchement */
    while (!(inb(0x60) & 0x80));

    return keymap[sc];
}
int keyboard_get_scancode() {
    unsigned char sc;

    do {
        sc = inb(0x60);
    } while (sc & 0x80);

    while (!(inb(0x60) & 0x80));

    return sc;
}


