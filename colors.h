#ifndef __COLORS_H__
#define __COLORS_H__ "Desmon.hak.anon"
#define __version 2.0

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#ifdef _WIN32
#include <Windows.h>
typedef enum ConsoleColor
{
    C_BLACK,
    C_BLUE,
    C_GREEN,
    C_CYAN,
    C_RED,
    C_MAGENTA,
    C_YELLOW,
    C_WHITE,
    C_LIGHTBLACK,
    C_LIGHTCYAN,
    C_LIGHTRED,
    C_LIGHTMAGENTA,
    C_LIGHTYELLOW,
    C_LIGHTWHITE
} ConsoleColor;

void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__();
#else
typedef enum ConsoleColor
{
    C_BLACK = 0,
    C_BLUE = 4,
    C_GREEN = 2,
    C_CYAN = 6,
    C_RED = 1,
    C_MAGENTA = 5,
    C_YELLOW = 3,
    C_WHITE = 7,
    C_LIGHTBLACK = 0,
    C_LIGHTCYAN = 6,
    C_LIGHTRED = 1,
    C_LIGHTMAGENTA = 5,
    C_LIGHTYELLOW = 3,
    C_LIGHTWHITE = 7
} ConsoleColor;
#endif

#define BACKGROUND_COLOR_BLACK "\033[0;40m"
#define BACKGROUND_COLOR_RED "\033[0;41m"
#define BACKGROUND_COLOR_GREEN "\033[0;42m"
#define BACKGROUND_COLOR_YELLOW "\033[0;43m"
#define BACKGROUND_COLOR_BLUE "\033[0;44m"
#define BACKGROUND_COLOR_MAGENTA "\033[0;45m"
#define BACKGROUND_COLOR_CYAN "\033[0;46m"
#define BACKGROUND_COLOR_WHITE "\033[0;47m"
#define BACKGROUND_COLOR_RESET "\033[0m"

// letra negro oscuro
#define LETTER_BLACK "\033[30m"

// letra rojo ocuro
#define LETTER_RED "\033[31m"

// letra verde ocuro
#define LETTER_GREEN "\033[32m"

// letra amarillo oscuro
#define LETTER_YELLOW "\033[33m"

// letra azul oscuro
#define LETTER_BLUE "\033[34m"

// letra magenta oscuro
#define LETTER_MAGENTA "\033[35m"

// letra cyan ocuro:
#define LETTER_CYAN "\033[36m"

// letra blanco oscuro(gris claro)
#define LETTER_WHITE "\033[37m"

// resetear el color de la letra a la por defecto
#define LETTER_RESET "\033[38m"

// versiones claras de los colores de letra:

// fondo negro:
#define LETTER_LIGHTBLACK_EX "\033[90m" // o gris
#define LETTER_LIGHTRED_EX "\033[91m"
#define LETTER_LIGHTGREEN_EX "\033[92m"
#define LETTER_LIGHTYELLOW_EX "\033[93m"
#define LETTER_LIGHTBLUE_EX "\033[94m"
#define LETTER_LIGHTMAGENTA_EX "\033[95m"
#define LETTER_LIGHTCYAN_EX "\033[96m"
#define LETTER_LIGHTWHITE_EX "\033[97m"

// stylos:
#define STYLE_BOLDED "\033[1m"     // : Negrita
#define STYLE_DARKENED "\033[2m"   // : Oscurecido
#define STYLE_ITALICS "\033[3m"    // : Cursiva
#define STYLE_UNDERLINED "\033[4m" // : Subrayado
#define STYLE_BLIKING "\033[5m"    // : Parpadeo
#define STYLE_INVERTED "\033[7m"   // : Inversión de colores (texto y fondo)

// Mover el cursor hacia arriba:
#define UP(data, number) "\033[" number "A" data

// Mover el cursor hacia abajo:
#define DOWN(data, number) "\033[" number "B" data

// Mover el cursor hacia la derecha:
#define FORWARD(data, number) "\033[" number "C" data

// Mover el cursor hacia la izquierda
#define BACK(data, number) "\033[" number "D" data

// Mover el cursor a una posición específica
#define POS(data, number1, number2) "\033[" number1 ";" number2 "H" data

// cambiar titulo de la terminal:
#define SET_TITLE(title) "\033]2;" title "\007"

// limpiar pantalla:
#define CLEAR_DISPLAY "\033[3J\033[H\033[2J"

// limpiar una linea:
#define CLEAR_LINE "\033[K"

// esconder cursor
#define HIDDEN_SLIDER "\033[?25l"

//  mostrar cursor
#define SHOW_SLIDER "\033[?25h"

// cambiar el modo del cursor
#define SET_MODE_SLIDER "\033[?12l"

// cambiar el tamaño del cursor
#define SET_SIZE_SLIDER(size) "\033[?" size "c"

#define POINTGREEN(data) LETTER_LIGHTGREEN_EX "[" LETTER_BLUE "*" LETTER_LIGHTGREEN_EX "]" LETTER_LIGHTWHITE_EX data LETTER_RESET
#define POINTRED(data) LETTER_LIGHTYELLOW_EX "[" LETTER_BLUE "*" LETTER_LIGHTYELLOW_EX "]" LETTER_LIGHTMAGENTA_EX data LETTER_RESET

// definir el color de fondo de forma personalizada
#define BACKGROUND_COLOR_CUSTOM(red, green, blue) "\x1b[48;2;" red ";" green ";" blue "m"

// definir el color de letra de forma personalizada
#define FOREGROUND_COLOR_CUSTOM(red, green, blue) "\x1b[38;2;" red ";" green ";" blue "m"

// definir colore de fondo y de letra
#define BACK_FORE_COLOR_CUSTOM(redB, greenB, blueB, redF, greenF, blueF) BACKGROUND_COLOR_CUSTOM(redB, greenB, blueB) FOREGROUND_COLOR_CUSTOM(redF, greenF, blueF)

#define RGB_CREATE(red, green, blue) (RGB_C) {.r = red, .g = green, .b = blue}
typedef union RGB_C
{
    struct
    {
        unsigned char red, green, blue;
    };
    struct
    {
        unsigned char r, g, b;
    };
} RGB_C;

#define foreground_color_custom(...) _Generic((__VA_ARGS__), \
    RGB_C: foreground_color_custom_RGB,                      \
    default: foreground_color_custom_)(__VA_ARGS__)

#define background_color_custom(...) _Generic((__VA_ARGS__), \
    RGB_C: background_color_custom_RGB,                      \
    default: background_color_custom_)(__VA_ARGS__)

#define back_fore_color_custom(...) _Generic((__VA_ARGS__), \
    RGB_C: back_fore_color_custom_RGB,                \
    default: back_fore_color_custom_)(__VA_ARGS__)

void __attribute__((destructor)) _RESET_COLOR__();

void clear_line();
void clear_display();
void set_title(char *title);
void setConsoleColor(ConsoleColor foreground, ConsoleColor background);
void resetColorTerminal();
void pos(unsigned char x, unsigned char y, char *data);
void back(char *data, unsigned char number);
void forward(char *data, unsigned char number);
void down(char *data, unsigned char number);
void up(char *data, unsigned char number);
static inline void foreground_color_custom_RGB(RGB_C color);
static void foreground_color_custom_(unsigned char red, unsigned char green, unsigned char blue);
static inline void background_color_custom_RGB(RGB_C color);
static void background_color_custom_(unsigned char red, unsigned char green, unsigned char blue);
static inline void back_fore_color_custom_RGB(RGB_C colorBackGround, RGB_C colorForeGround);
static void back_fore_color_custom_(unsigned char redB, unsigned char greenB,
                                       unsigned char blueB, unsigned char redF,
                                       unsigned char greenF, unsigned char blueF);
void printf_color(const char *format, ...);
void vprintf_color(const char *format, va_list args);

#include "colors.c"
#endif
