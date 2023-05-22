#ifndef __COLORS_C__
#define __COLORS_C__ "Desmon.hak.anon"

#include "colors.h"

#ifdef _WIN32
void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__()
{
    // Habilitar el soporte de colores ANSI en la consola de Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode))
    {
        if (!(dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING))
        {
            // Habilitar los colores ANSI en la consola de Windows
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
}

#endif

#endif