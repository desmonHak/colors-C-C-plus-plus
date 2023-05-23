#include "colors.h"

void resetColorTerminal()
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    printf(LETTER_RESET);
#endif
}

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

void __attribute__((destructor)) _RESET_COLOR__()
{
    // setConsoleColor(C_WHITE, C_BLACK);
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    resetColorTerminal();
}

void setConsoleColor(ConsoleColor foreground, ConsoleColor background)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, foreground | (background << 4));
}
#else
void setConsoleColor(ConsoleColor foreground, ConsoleColor background)
{
    printf("\033[%dm\033[0;%dm", 30 + foreground, 40 + background);
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
    char buffer[256] = "";

    while (*p != '\0')
    {
        if (in_color_code)
        {
            if (*p == '}')
            {
                color_code[color_code_index] = '\0';
                if (strcmp(color_code, "FG:red") == 0)
                {
                    printf(LETTER_RED); // Set foreground text color to red
                }
                else if (strcmp(color_code, "FG:reset") == 0 || strcmp(color_code, "BG:reset") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, LETTER_RESET);
                }
                else if (strcmp(color_code, "FG:green") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, LETTER_GREEN); // Set foreground text color to green
                }
                else if (strcmp(color_code, "FG:blue") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, LETTER_BLUE); // Set foreground text color to blue
                }
                else if (strcmp(color_code, "FG:black") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, LETTER_BLACK); // Set foreground text color to black
                }
                else if (strcmp(color_code, "FG:yellow") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, LETTER_YELLOW); // Set foreground text color to yellow
                }
                else if (strcmp(color_code, "FG:purple") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, LETTER_MAGENTA); // Set foreground text color to purple
                }
                else if (strcmp(color_code, "FG:cyan") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, LETTER_CYAN); // Set foreground text color to cyan
                }
                else if (strcmp(color_code, "FG:white") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, LETTER_WHITE); // Set foreground text color to white
                }
                else if (strcmp(color_code, "BG:black") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, BACKGROUND_COLOR_BLACK); // Set background color to black
                }
                else if (strcmp(color_code, "BG:red") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, BACKGROUND_COLOR_RED); // Set background color to red
                }
                else if (strcmp(color_code, "BG:green") == 0)
                {
                    printf(BACKGROUND_COLOR_GREEN); // Set background color to green
                }
                else if (strcmp(color_code, "BG:yellow") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, BACKGROUND_COLOR_YELLOW); // Set background color to yellow
                }
                else if (strcmp(color_code, "BG:purple") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, BACKGROUND_COLOR_MAGENTA); // Set background color to purple
                }
                else if (strcmp(color_code, "BG:cyan") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, BACKGROUND_COLOR_CYAN); // Set background color to cyan
                }
                else if (strcmp(color_code, "BG:white") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, BACKGROUND_COLOR_WHITE); // Set background color to white
                }
                else if (strcmp(color_code, "BG:blue") == 0)
                {
                    sprintf(buffer, "%s%s", buffer, BACKGROUND_COLOR_BLUE); // Set background color to blue
                }

                in_color_code = false;
                color_code_index = 0;
            }
            else
            {
                color_code[color_code_index] = *p;
                color_code_index++;
            }
        }
        else
        {
            if (*p == '#')
            {
                p++;
                if (*p == '{')
                {
                    in_color_code = true;
                    color_code_index = 0;
                }
                else
                {
                    sprintf(buffer, "%s#%c", buffer, *p);
                }
            }
            else
            {
                sprintf(buffer, "%s%c", buffer, *p);
            }
        }

        p++;
    }

    char formatted_buffer[256];
    vsprintf(formatted_buffer, buffer, args);
    printf("%s" LETTER_RESET, formatted_buffer);
    // setConsoleColor(C_WHITE, C_BLACK);
    resetColorTerminal();
}

void clear_line()
{
    printf(CLEAR_LINE);
}
void clear_display()
{
    printf(CLEAR_DISPLAY);
}
void set_title(char *title)
{
    printf(SET_TITLE("%d"), title);
}
void pos(unsigned char x, unsigned char y, char *data)
{
    printf(POS("%d", "%d", "%s"), x, y, data);
}
void back(char *data, unsigned char number)
{
    printf(BACK("%s", "%d"), data, number);
}
void forward(char *data, unsigned char number)
{
    printf(FORWARD("%s", "%d"), data, number);
}
void down(char *data, unsigned char number)
{
    printf(DOWN("%s", "%d"), data, number);
}
void up(char *data, unsigned char number)
{
    printf(UP("%s", "%d"), data, number);
}
static inline void foreground_color_custom_RGB(RGB_C color)
{
    foreground_color_custom_(color.r, color.g, color.b);
}
static void foreground_color_custom_(unsigned char red, unsigned char green, unsigned char blue)
{
    printf(FOREGROUND_COLOR_CUSTOM("%d", "%d", "%d"), red, green, blue);
}
static inline void background_color_custom_RGB(RGB_C color)
{
    background_color_custom_(color.red, color.green, color.blue);
}
static void background_color_custom_(unsigned char red, unsigned char green, unsigned char blue)
{
    printf(BACKGROUND_COLOR_CUSTOM("%d", "%d", "%d"), red, green, blue);
}
static inline void back_fore_color_custom_RGB(RGB_C colorBackGround, RGB_C colorForeGround)
{
    back_fore_color_custom_(
        colorBackGround.r,
        colorBackGround.g,
        colorBackGround.b,
        colorForeGround.r,
        colorForeGround.g,
        colorForeGround.b);
}
static void back_fore_color_custom_(unsigned char redB, unsigned char greenB,
                                       unsigned char blueB, unsigned char redF,
                                       unsigned char greenF, unsigned char blueF)
{
    printf(BACK_FORE_COLOR_CUSTOM("%d", "%d", "%d", "%d", "%d", "%d"), redB, greenB, blueB, redF, greenF, blueF);
}