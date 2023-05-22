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

void printf_color(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf_color(format, args);
    va_end(args);
}

void vprintf_color(const char *format, va_list args)
{
    const char *p = format;
    bool in_color_code = false;
    char color_code[20];
    int color_code_index = 0;

    va_list args_copy;
    va_copy(args_copy, args);

    while (*p != '\0')
    {
        if (in_color_code)
        {
            if (*p == '{')
            {
                color_code_index = 0;
            }
            else if (*p == '}')
            {
                color_code[color_code_index] = '\0';

                if (strcmp(color_code, "FG:red") == 0)
                {
                    printf(LETTER_RED); // Set foreground text color to red
                }
                else if (strcmp(color_code, "FG:reset") == 0 || strcmp(color_code, "BG:reset") == 0)
                {
                    printf(LETTER_RESET);
                }
                else if (strcmp(color_code, "FG:green") == 0)
                {
                    printf(LETTER_GREEN); // Set foreground text color to green
                }
                else if (strcmp(color_code, "FG:blue") == 0)
                {
                    printf(LETTER_BLUE); // Set foreground text color to blue
                }
                else if (strcmp(color_code, "FG:black") == 0)
                {
                    printf(LETTER_BLACK); // Set foreground text color to black
                }
                else if (strcmp(color_code, "FG:yellow") == 0)
                {
                    printf(LETTER_YELLOW); // Set foreground text color to yellow
                }
                else if (strcmp(color_code, "FG:purple") == 0)
                {
                    printf(LETTER_MAGENTA); // Set foreground text color to purple
                }
                else if (strcmp(color_code, "FG:cyan") == 0)
                {
                    printf(LETTER_CYAN); // Set foreground text color to cyan
                }
                else if (strcmp(color_code, "FG:white") == 0)
                {
                    printf(LETTER_WHITE); // Set foreground text color to white
                }
                else if (strcmp(color_code, "BG:black") == 0)
                {
                    printf(BACKGROUND_COLOR_BLACK); // Set background color to black
                }
                else if (strcmp(color_code, "BG:red") == 0)
                {
                    printf(BACKGROUND_COLOR_RED); // Set background color to red
                }
                else if (strcmp(color_code, "BG:green") == 0)
                {
                    printf(BACKGROUND_COLOR_GREEN); // Set background color to green
                }
                else if (strcmp(color_code, "BG:yellow") == 0)
                {
                    printf(BACKGROUND_COLOR_YELLOW); // Set background color to yellow
                }
                else if (strcmp(color_code, "BG:purple") == 0)
                {
                    printf(BACKGROUND_COLOR_MAGENTA); // Set background color to purple
                }
                else if (strcmp(color_code, "BG:cyan") == 0)
                {
                    printf(BACKGROUND_COLOR_CYAN); // Set background color to cyan
                }
                else if (strcmp(color_code, "BG:white") == 0)
                {
                    printf(BACKGROUND_COLOR_WHITE); // Set background color to white
                }
                else if (strcmp(color_code, "BG:blue") == 0)
                {
                    printf(BACKGROUND_COLOR_BLUE); // Set background color to blue
                }

                in_color_code = false;
            }
            else
            {
                color_code[color_code_index] = *p;
                color_code_index++;
            }
        }
        else
        {
            if (*p == '%')
            {
                p++;
                if (*p == '{')
                {
                    in_color_code = true;
                    color_code_index = 0;
                }
                else if (*p == '%')
                {
                    putchar('%');
                }
                else
                {
                    char format_specifier[10];
                    int format_specifier_index = 0;
                    format_specifier[format_specifier_index] = *p;
                    format_specifier_index++;
                    format_specifier[format_specifier_index] = '\0';
                    p++;

                    while (*p != '\0')
                    {
                        format_specifier[format_specifier_index] = *p;
                        format_specifier_index++;
                        format_specifier[format_specifier_index] = '\0';

                        if (strchr("diufFeEgGxXoscpaAn", *p) != NULL)
                        {
                            break;
                        }

                        p++;
                    }

                    if (*p != '\0')
                    {
                        char buffer[256];
                        vsnprintf(buffer, sizeof(buffer), format_specifier, args_copy);
                        printf("%s", buffer);
                    }
                }
            }
            else
            {
                putchar(*p);
            }
        }

        p++;
    }

    // Reset text and background color
    printf("\033[0m");

    va_end(args_copy);
}
