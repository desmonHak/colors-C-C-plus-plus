#ifndef __COLORS_H__
#define __COLORS_H__ "Desmon.hak.anon"
#define __version 2.0

#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__();
#endif

#define BACKGROUND_COLOR_BLACK        "\033[0;40m"
#define BACKGROUND_COLOR_RED          "\033[0;41m"
#define BACKGROUND_COLOR_GREEN        "\033[0;42m"
#define BACKGROUND_COLOR_YELLOW       "\033[0;43m"
#define BACKGROUND_COLOR_BLUE         "\033[0;44m"
#define BACKGROUND_COLOR_PURPLE       "\033[0;45m"
#define BACKGROUND_COLOR_CYAN         "\033[0;46m"
#define BACKGROUND_COLOR_WHITE        "\033[0;47m"
#define BACKGROUND_COLOR_RESET        "\033[0m"

#define LETTER_BLACK            "\033[30m"
#define LETTER_RED              "\033[31m"
#define LETTER_GREEN            "\033[32m"
#define LETTER_YELLOW           "\033[33m"
#define LETTER_BLUE             "\033[34m"
#define LETTER_MAGENTA          "\033[35m"
#define LETTER_CYAN             "\033[36m"
#define LETTER_WHITE            "\033[37m"
#define LETTER_RESET            "\033[37m\033[38m"
#define LETTER_LIGHTBLACK_EX    "\033[90m"
#define LETTER_LIGHTRED_EX      "\033[91m"
#define LETTER_LIGHTGREEN_EX    "\033[92m"
#define LETTER_LIGHTYELLOW_EX   "\033[93m"
#define LETTER_LIGHTBLUE_EX     "\033[94m"
#define LETTER_LIGHTMAGENTA_EX  "\033[95m"
#define LETTER_LIGHTCYAN_EX     "\033[96m"
#define LETTER_LIGHTWHITE_EX    "\033[97m"


#define UP(data, number)                printf("\033[%dA%s", number, data);
#define DOWN(data, number)              printf("\033[%dB%s", number, data);
#define FORWARD(data, number)           printf("\033[%dC%s", number, data);
#define BACK(data, number)              printf("\033[%dD%s", number, data);
#define POS(data, number1, number2)     printf("\033[%d;%dH%s", number1, number2, data);
#define SET_TITLE(title)                printf("\033]2;%s\007" title);
#define CLEAR()                         printf("\033[3J\033[H\033[2J");
#define POINTGREEN(data)                LETTER_LIGHTGREEN_EX "[" LETTER_BLUE "*"  LETTER_LIGHTGREEN_EX "]" LETTER_LIGHTWHITE_EX data LETTER_RESET
#define POINTRED(data)                  LETTER_LIGHTYELLOW_EX "[" LETTER_BLUE "*"  LETTER_LIGHTYELLOW_EX "]" LETTER_LIGHTMAGENTA_EX data LETTER_RESET

#include "colors.c"
#endif
