#ifndef __COLORS_H__
#define __COLORS_H__ "Desmon.hak.anon"
#define __version 2.0

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef enum ANSIColors
{
    ANSI_BLACK = 0,
    ANSI_RED = 1,
    ANSI_GREEN = 2,
    ANSI_YELLOW = 3,
    ANSI_BLUE = 4,
    ANSI_MAGENTA = 5,    
    ANSI_CYAN = 6,
    ANSI_WHITE = 7,
} ANSIColors;

#define REGULAR_COLORS_LETTER 30
#define HIGH_INTENSTY  90
#define REGULAR_COLORS_BACKGROUND 40
#define HIGH_INTENSTY_BACKGROUNG 100
#define ANSI_COLOR_FOREGROUNG(color) "\033["   color "m"
#define ANSI_COLOR_BACKGROUNG(color) "\033[0;" color "m"
#define ANSI_COLOR_BOLD(color)       "\033[1;" color "m"
#define ANSI_COLOR_UNDERLINE(color)  "\033[4;" color "m"
void ANSI_fore_color(ANSIColors color);
void ANSI_back_color(ANSIColors color);

typedef union sizes_num {
    unsigned long long i64;
    unsigned int i32;
    unsigned short int i16;
    unsigned char i8;
} sizes_num;

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

#ifndef FOREGROUND_BLACK
#define FOREGROUND_BLACK 0
#endif
#ifndef FOREGROUND_WHITE
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
//#define FOREGROUND_WHITE  0xf
#endif
#ifndef FOREGROUND_MASK
#define FOREGROUND_MASK (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
#endif
#ifndef FOREGROUND_RESET
#define FOREGROUND_RESET FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#endif
#ifndef FOREGROUND_YELLOW
#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN 
#endif
#ifndef FOREGROUND_MAGENTA
#define FOREGROUND_MAGENTA FOREGROUND_RED | FOREGROUND_BLUE 
#endif
#ifndef FOREGROUND_CYAN
#define FOREGROUND_CYAN FOREGROUND_GREEN | FOREGROUND_BLUE 
#endif

#ifndef BACKGROUND_BLACK
#define BACKGROUND_BLACK 0
#endif
#ifndef BACKGROUND_WHITE
#define BACKGROUND_WHITE 0xf0
#endif
#ifndef BACKGROUND_YELLOW
#define BACKGROUND_YELLOW BACKGROUND_RED | BACKGROUND_GREEN
#endif
#ifndef BACKGROUND_MAGENTA
#define BACKGROUND_MAGENTA BACKGROUND_RED | BACKGROUND_BLUE
#endif
#ifndef BACKGROUND_CYAN
#define BACKGROUND_CYAN BACKGROUND_GREEN | BACKGROUND_BLUE
#endif

void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__();
#else
typedef enum ConsoleColor
{
    C_BLACK = ANSI_BLACK,
    C_RED = ANSI_RED,
    C_GREEN = ANSI_GREEN,
    C_YELLOW = ANSI_YELLOW,
    C_BLUE = ANSI_BLUE,
    C_MAGENTA = ANSI_MAGENTA,    
    C_CYAN = ANSI_CYAN,
    C_WHITE = ANSI_WHITE,
    
    C_LIGHTBLACK = ANSI_BLACK,
    C_LIGHTRED = ANSI_RED,
    C_LIGHTGREEN = ANSI_GREEN,
    C_LIGHTYELLOW = ANSI_YELLOW,
    C_LIGHTBLUE = ANSI_BLUE,
    C_LIGHTMAGENTA = ANSI_MAGENTA,
    C_LIGHTCYAN = ANSI_CYAN,
    C_LIGHTWHITE = ANSI_WHITE
} ConsoleColor;
#endif

#define BACKGROUND_COLOR_BLACK_ANSI   "\033[0;40m"
#define BACKGROUND_COLOR_RED_ANSI     "\033[0;41m"
#define BACKGROUND_COLOR_GREEN_ANSI   "\033[0;42m"
#define BACKGROUND_COLOR_YELLOW_ANSI  "\033[0;43m"
#define BACKGROUND_COLOR_BLUE_ANSI    "\033[0;44m"
#define BACKGROUND_COLOR_MAGENTA_ANSI "\033[0;45m"

#define BACKGROUND_COLOR_CYAN_ANSI    "\033[0;46m"
#define BACKGROUND_COLOR_WHITE_ANSI   "\033[0;47m"
#define BACKGROUND_COLOR_RESET_ANSI   "\033[0m"

#ifdef _WIN32
#define BACKGROUND_COLOR_GREEN       setConsoleBackgroundColor(BACKGROUND_GREEN)
#define BACKGROUND_COLOR_YELLOW      setConsoleBackgroundColor(BACKGROUND_YELLOW)
#define BACKGROUND_COLOR_BLUE        setConsoleBackgroundColor(BACKGROUND_BLUE)
#define BACKGROUND_COLOR_RED         setConsoleBackgroundColor(BACKGROUND_RED)
#define BACKGROUND_COLOR_BLACK       setConsoleBackgroundColor(BACKGROUND_BLACK)
#define BACKGROUND_COLOR_MAGENTA     setConsoleBackgroundColor(BACKGROUND_MAGENTA)
#define BACKGROUND_COLOR_CYAN        setConsoleBackgroundColor(BACKGROUND_CYAN)
#define BACKGROUND_COLOR_WHITE       setConsoleBackgroundColor(BACKGROUND_WHITE)
#else
#define BACKGROUND_COLOR_GREEN       setConsoleBackgroundColor(C_GREEN)
#define BACKGROUND_COLOR_YELLOW      setConsoleBackgroundColor(C_YELLOW)
#define BACKGROUND_COLOR_BLUE        setConsoleBackgroundColor(C_BLUE)
#define BACKGROUND_COLOR_RED         setConsoleBackgroundColor(C_RED)
#define BACKGROUND_COLOR_BLACK       setConsoleBackgroundColor(C_BLACK)
#define BACKGROUND_COLOR_MAGENTA     setConsoleBackgroundColor(C_MAGENTA)
#define BACKGROUND_COLOR_CYAN        setConsoleBackgroundColor(C_CYAN)
#define BACKGROUND_COLOR_WHITE       setConsoleBackgroundColor(C_WHITE)
#endif 
#define BACKGROUND_COLOR_RESET       resetColorTerminal()




// letra negro oscuro
#define LETTER_BLACK_ANSI   "\033[30m"

// letra rojo ocuro
#define LETTER_RED_ANSI     "\033[31m"

// letra verde ocuro
#define LETTER_GREEN_ANSI   "\033[32m"

// letra amarillo oscuro
#define LETTER_YELLOW_ANSI  "\033[33m"

// letra azul oscuro
#define LETTER_BLUE_ANSI    "\033[34m"

// letra magenta oscuro
#define LETTER_MAGENTA_ANSI "\033[35m"

// letra cyan ocuro:
#define LETTER_CYAN_ANSI    "\033[36m"

// letra blanco oscuro(gris claro)
#define LETTER_WHITE_ANSI   "\033[37m"

// resetear el color de la letra a la por defecto
#define LETTER_RESET_ANSI   "\033[38m"

// versiones claras de los colores de letra:

// fondo negro:
#define LETTER_LIGHTBLACK_EX_ANSI "\033[90m" // o gris
#define LETTER_LIGHTRED_EX_ANSI "\033[91m"
#define LETTER_LIGHTGREEN_EX_ANSI "\033[92m"
#define LETTER_LIGHTYELLOW_EX_ANSI "\033[93m"
#define LETTER_LIGHTBLUE_EX_ANSI "\033[94m"
#define LETTER_LIGHTMAGENTA_EX_ANSI "\033[95m"
#define LETTER_LIGHTCYAN_EX_ANSI "\033[96m"
#define LETTER_LIGHTWHITE_EX_ANSI "\033[97m"


#ifdef _WIN32
#define LETTER_GREEN            setConsoleForegroundColor(FOREGROUND_GREEN)
#define LETTER_YELLOW           setConsoleForegroundColor(FOREGROUND_YELLOW)
#define LETTER_BLUE             setConsoleForegroundColor(FOREGROUND_BLUE)
#define LETTER_RED              setConsoleForegroundColor(FOREGROUND_RED)
#define LETTER_BLACK            setConsoleForegroundColor(FOREGROUND_BLACK)
#define LETTER_MAGENTA          setConsoleForegroundColor(FOREGROUND_MAGENTA)
#define LETTER_CYAN             setConsoleForegroundColor(FOREGROUND_CYAN)
#define LETTER_WHITE            setConsoleForegroundColor(FOREGROUND_WHITE)
#define LETTER_LIGHTBLACK_EX    setConsoleForegroundColor(FOREGROUND_BLACK   | FOREGROUND_INTENSITY)
#define LETTER_LIGHTRED_EX      setConsoleForegroundColor(FOREGROUND_RED     | FOREGROUND_INTENSITY)
#define LETTER_LIGHTGREEN_EX    setConsoleForegroundColor(FOREGROUND_GREEN   | FOREGROUND_INTENSITY)
#define LETTER_LIGHTYELLOW_EX   setConsoleForegroundColor(FOREGROUND_YELLOW  | FOREGROUND_INTENSITY)
#define LETTER_LIGHTBLUE_EX     setConsoleForegroundColor(FOREGROUND_BLUE    | FOREGROUND_INTENSITY)
#define LETTER_LIGHTMAGENTA_EX  setConsoleForegroundColor(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)
#define LETTER_LIGHTCYAN_EX     setConsoleForegroundColor(FOREGROUND_CYAN    | FOREGROUND_INTENSITY)
#define LETTER_LIGHTWHITE_EX    setConsoleForegroundColor(FOREGROUND_WHITE   | FOREGROUND_INTENSITY)
#else
#define LETTER_GREEN             setConsoleForegroundColor(C_GREEN)
#define LETTER_YELLOW            setConsoleForegroundColor(C_YELLOW)
#define LETTER_BLUE              setConsoleForegroundColor(C_BLUE)
#define LETTER_RED               setConsoleForegroundColor(C_RED)
#define LETTER_BLACK             setConsoleForegroundColor(C_BLACK)
#define LETTER_MAGENTA           setConsoleForegroundColor(C_MAGENTA)
#define LETTER_CYAN              setConsoleForegroundColor(C_CYAN)
#define LETTER_WHITE             setConsoleForegroundColor(C_WHITE)
#define LETTER_LIGHTBLACK_EX     setConsoleForegroundColor(C_LIGHTBLACK)
#define LETTER_LIGHTRED_EX       setConsoleForegroundColor(C_LIGHTRED)
#define LETTER_LIGHTGREEN_EX     setConsoleForegroundColor(C_LIGHTGREEN)
#define LETTER_LIGHTYELLOW_EX    setConsoleForegroundColor(C_LIGHTYELLOW)
#define LETTER_LIGHTBLUE_EX      setConsoleForegroundColor(C_LIGHTBLUE)
#define LETTER_LIGHTMAGENTA_EX   setConsoleForegroundColor(C_LIGHTMAGENTA)
#define LETTER_LIGHTCYAN_EX      setConsoleForegroundColor(C_LIGHTCYAN)
#define LETTER_LIGHTWHITE_EX     setConsoleForegroundColor(C_LIGHTWHITE)
#endif 
#define LETTER_RESET       resetColorTerminal()

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

#define POINTGREEN(data) "#{FG:green}[#{FG:blue}*#{FG:green}]#{FG:white}" data "#{FG:reset}"
#define POINTRED(data)   "#{FG:yellow}[#{FG:blue}*#{FG:yellow}]#{FG:purple}" data "#{FG:reset}"

// definir el color de fondo de forma personalizada
#define BACKGROUND_COLOR_CUSTOM(color) "\033[48;5;"color"m"

// definir el color de fondo de forma personalizada
#define BACKGROUND_COLOR_CUSTOM_RGB(red, green, blue) "\033[38;2;"red";"green";"blue"m"

// definir el color de letra de forma personalizada
#define FOREGROUND_COLOR_CUSTOM(color) "\033[38;5;"color"m"

#define FOREGROUND_COLOR_CUSTOM_RGB(red, green, blue) "\033[48;2;"red";"green";"blue"m"

// definir colore de fondo y de letra
#define BACK_FORE_COLOR_CUSTOM(Acolor, Bcolor) BACKGROUND_COLOR_CUSTOM(Acolor) FOREGROUND_COLOR_CUSTOM(Bcolor)

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
void set_title(const char *title);
#ifdef _WIN32
void setConsoleForegroundColor(WORD foregroundColor);
void setConsoleBackgroundColor(WORD backgroundColor);
void setConsoleColor(WORD foreground, WORD background);
#else
void setConsoleForegroundColor(ConsoleColor foregroundColor);
void setConsoleBackgroundColor(ConsoleColor backgroundColor);
void setConsoleColor(ConsoleColor foreground, ConsoleColor background);
#endif
void resetColorTerminal();
void pos(const unsigned char x, const unsigned char y, const char *data);
void back(const char *data, const unsigned char number);
void forward(const char *data, const unsigned char number);
void down(const char *data, const unsigned char number);
void up(const char *data, const unsigned char number);
static inline void foreground_color_custom_RGB(RGB_C color);
static void foreground_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue);
static inline void background_color_custom_RGB(RGB_C color);
static void background_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue);
static inline void back_fore_color_custom_RGB(RGB_C colorBackGround, RGB_C colorForeGround);
static void back_fore_color_custom_(unsigned char redB, unsigned char greenB,
                                       unsigned char blueB, unsigned char redF,
                                       unsigned char greenF, unsigned char blueF);
unsigned int jenkins_hash(
    unsigned int value,
    unsigned int n1, unsigned int n2, unsigned int n3,
    unsigned int n4, unsigned int n5, unsigned int n6);
void shuffle_array(int array[], int size);
void generate_three_values(
    unsigned int x,
    unsigned int *value1,
    unsigned int *value2,
    unsigned int *value3,
    unsigned int n1, unsigned int n2, unsigned int n3,
    unsigned int n4, unsigned int n5, unsigned int n6);
void printf_color(const char *format, ...);
void vprintf_color(const char *format, va_list args);
void print_sizes_num(sizes_num byte, size_t size_word);

#include "colors.c"
#endif
