; =========================================
; Mini-OS Kernel – Boot animé + Langue
; =========================================

BITS 16
ORG 0x1000

start:
    mov ax, cs
    mov ds, ax

    mov ax, 0xB800
    mov es, ax

    call clear_screen

    ; ===== BOOT ANIMATION =====
    mov si, logo
    call print_string

    mov si, load1
    call print_string
    call delay

    mov si, load2
    call print_string
    call delay

    mov si, load3
    call print_string
    call delay

    mov si, load4
    call print_string
    call delay

    mov si, boot_ok
    call print_string
    call delay

    call clear_screen

    ; ===== CHOIX DE LANGUE =====
    mov si, lang_msg
    call print_string

wait_lang:
    mov ah, 0x00
    int 0x16
    cmp al, '1'
    je set_fr
    cmp al, '2'
    je set_en
    jmp wait_lang

set_fr:
    mov byte [lang], 1
    jmp welcome

set_en:
    mov byte [lang], 2

welcome:
    call clear_screen

    cmp byte [lang], 1
    je msg_fr
    mov si, welcome_en
    jmp show

msg_fr:
    mov si, welcome_fr

show:
    call print_string

    mov byte [cursor_x], 0
    mov byte [cursor_y], 10
    call update_cursor
    jmp keyboard_loop

; =========================================
; Clavier simple
; =========================================
keyboard_loop:
    mov ah, 0x00
    int 0x16

    cmp al, 0x08
    je backspace

    cmp al, 0x0D
    je newline

    call update_cursor
    mov ah, 0x0E
    int 0x10
    inc byte [cursor_x]
    jmp keyboard_loop

backspace:
    cmp byte [cursor_x], 0
    je keyboard_loop
    dec byte [cursor_x]
    call update_cursor
    mov ah, 0x0E
    mov al, ' '
    int 0x10
    call update_cursor
    jmp keyboard_loop

newline:
    mov byte [cursor_x], 0
    inc byte [cursor_y]
    call update_cursor
    jmp keyboard_loop

; =========================================
; Fonctions utilitaires
; =========================================
print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

update_cursor:
    mov ah, 0x02
    mov bh, 0
    mov dh, [cursor_y]
    mov dl, [cursor_x]
    int 0x10
    ret

clear_screen:
    xor di, di
    mov cx, 80*25
.clear:
    mov ax, 0x0720
    stosw
    loop .clear
    ret

delay:
    mov cx, 0x7FFF
.d1:
    mov dx, 0x7FFF
.d2:
    dec dx
    jnz .d2
    dec cx
    jnz .d1
    ret

; =========================================
; Données
; =========================================
cursor_x db 0
cursor_y db 0
lang     db 0

logo db 13,10
     db "################################",13,10
     db "#        MINI-OS v1.0          #",13,10
     db "################################",13,10,13,10,0

load1 db "[####                ] 25%",13,10,0
load2 db "[########            ] 50%",13,10,0
load3 db "[############        ] 75%",13,10,0
load4 db "[####################] 100%",13,10,13,10,0

boot_ok db "System initialized successfully",13,10,0

lang_msg db "Choose language / Choisir la langue",13,10
         db "1) Francais",13,10
         db "2) English",13,10,0

welcome_fr db "Bienvenue sur Mini-OS",13,10,0
welcome_en db "Welcome to Mini-OS",13,10,0

