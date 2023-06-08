#ifndef __COLORS_C__
#define __COLORS_C__ "Desmon.hak.anon"
#include "colors.h"

// genera un valor entre 0 y 255
unsigned int jenkins_hash(
    unsigned int value,
    unsigned int n1, unsigned int n2, unsigned int n3,
    unsigned int n4, unsigned int n5, unsigned int n6)
{
    value = (value + 0x7ed55d16) + (value << n1);
    value = (value ^ 0xc761c23c) ^ (value >> n2);
    value = (value + 0x165667b1) + (value << n3);
    value = (value + 0xd3a2646c) ^ (value << n4);
    value = (value + 0xfd7046c5) + (value << n5);
    value = (value ^ 0xb55a4f09) ^ (value >> n6);
    return value % 256;
}
// combina los valores de un array
void shuffle_array(int array[], int size)
{
    srand(time(NULL));

    for (int i = size - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
// genera tres valores aparit de 1 usando 6 desplazamientos
void generate_three_values(
    unsigned int x,
    unsigned int *value1,
    unsigned int *value2,
    unsigned int *value3,
    unsigned int n1, unsigned int n2, unsigned int n3,
    unsigned int n4, unsigned int n5, unsigned int n6)
{
    if (x < 0 || x > 255)
    {
        printf("El numero debe estar en el rango de 0 a 255.\n");
        return;
    }

    // Aplicar la función de dispersión hash a los valores iniciales
    *value1 = jenkins_hash(x, n1, n2, n3, n4, n5, n6);
    *value2 = jenkins_hash(*value1, n1, n2, n3, n4, n5, n6);
    *value3 = jenkins_hash(*value2, n1, n2, n3, n4, n5, n6);
}

void resetColorTerminal()
{
#ifdef _WIN32

    /*setConsoleBackgroundColor(BACKGROUND_BLACK);
    setConsoleForegroundColor(FOREGROUND_WHITE);*/
    // setConsoleColor(FOREGROUND_MASK, 0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_MASK);
    /*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    WORD originalAttrs = csbi.wAttributes;
    WORD foregroundAttrs = originalAttrs & 0x0F; // Máscara para obtener solo los bits del color del texto
    WORD backgroundAttrs = originalAttrs & 0xF0; // Máscara para obtener solo los bits del color de fondo

    WORD resetAttrs = foregroundAttrs | (backgroundAttrs << 4); // Combinar los atributos de texto y fondo

    SetConsoleTextAttribute(hConsole, resetAttrs);*/
#else
    printf(BACKGROUND_COLOR_RESET_ANSI);
#endif
}

void __attribute__((destructor)) _RESET_COLOR__()
{
    // setConsoleColor(C_WHITE, C_BLACK);
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    resetColorTerminal();
}

#ifdef _WIN32
void resetConsoleForegroundColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD attributes = consoleInfo.wAttributes;
    attributes &= 0xFFF0; // Eliminar el color de la letra actual
    attributes |= FOREGROUND_WHITE;
    SetConsoleTextAttribute(hConsole, attributes);
}

void setConsoleForegroundColor(WORD foregroundColor)
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD attributes = consoleInfo.wAttributes;
    attributes &= 0xFFF0; // Eliminar el color de la letra actual
    attributes |= foregroundColor;
    SetConsoleTextAttribute(hConsole, attributes);
}
#else
void resetConsoleForegroundColor()
{
    resetColorTerminal();
}
void setConsoleForegroundColor(ConsoleColor foregroundColor)
{
    printf("\033[%dm", 30 + foregroundColor);
}
#endif

#ifdef _WIN32
void resetConsoleBackgroundColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD originalAttrs = csbi.wAttributes;
    WORD backgroundAttrs = originalAttrs & 0xF0;
    SetConsoleTextAttribute(hConsole, backgroundAttrs);
}
void setConsoleBackgroundColor(WORD backgroundColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    WORD attributes = consoleInfo.wAttributes;
    attributes &= 0x000F; // Limpiar los bits de color de fondo existentes
    attributes |= backgroundColor;

    SetConsoleTextAttribute(hConsole, attributes);
}
#else
void resetConsoleBackgroundColor()
{
    resetColorTerminal();
}
void setConsoleBackgroundColor(ConsoleColor backgroundColor)
{
    printf("\033[0;%dm", 40 + backgroundColor);
}
#endif

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

#ifdef _WIN32
void setConsoleColor(WORD foreground, WORD background)
{
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hConsole, (int)foreground | ((int)background << 4));
    setConsoleForegroundColor(foreground);
    setConsoleBackgroundColor(background);
}
#else
void setConsoleColor(ConsoleColor foreground, ConsoleColor background)
{
    setConsoleForegroundColor(foreground);
    setConsoleBackgroundColor(background);
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
    va_list args_copy;
    va_copy(args_copy, args);
    size_t size = (vsnprintf(NULL, 0, format, args_copy) + 1) * sizeof(char);
    va_end(args_copy);
    char *formatted_buffer = (char *)malloc(size);
    vsprintf(formatted_buffer, format, args);

    const char *p = formatted_buffer;
    bool in_color_code = false;
    char color_code[30];
    int color_code_index = 0;

    while (*p != '\0')
    {
        if (in_color_code)
        {
            if (*p == '}')
            {
                color_code[color_code_index] = '\0';

                // Token de color encontrado, procesarlo aquí
                if (strncmp(color_code, "FG:red", 6) == 0)
                {
                    // Cambiar a color rojo
                    LETTER_RED;
                }
                else if (strncmp(color_code, "FG:reset", 8) == 0)
                {
                    // Restablecer color de primer plano
                    resetConsoleForegroundColor();
                }
                else if (strncmp(color_code, "BG:reset", 8) == 0)
                {
                    // Restablecer color de fondo
                    resetConsoleBackgroundColor();
                }

                else if (strncmp(color_code, "FG:lred", 8) == 0)
                {
                    LETTER_LIGHTRED_EX;
                }
                else if (strncmp(color_code, "FG:lblack", 8) == 0)
                {
                    LETTER_LIGHTBLACK_EX;
                }
                else if (strncmp(color_code, "FG:lgreen", 8) == 0)
                {
                    LETTER_LIGHTGREEN_EX;
                }
                else if (strncmp(color_code, "FG:lyellow", 8) == 0)
                {
                    LETTER_LIGHTYELLOW_EX;
                }
                else if (strncmp(color_code, "FG:lblue", 8) == 0)
                {
                    LETTER_LIGHTBLUE_EX;
                }
                else if (strncmp(color_code, "FG:lpurple", 8) == 0)
                {
                    LETTER_LIGHTMAGENTA_EX;
                }
                else if (strncmp(color_code, "FG:lcyan", 8) == 0)
                {
                    LETTER_LIGHTCYAN_EX;
                }
                else if (strncmp(color_code, "FG:lwhite", 8) == 0)
                {
                    LETTER_LIGHTWHITE_EX;
                }

                else if (strncmp(color_code, "FG:green", 8) == 0)
                {
                    // Cambiar a color verde
                    LETTER_GREEN;
                }
                else if (strncmp(color_code, "FG:blue", 7) == 0)
                {
                    // Cambiar a color azul
                    LETTER_BLUE;
                }
                else if (strncmp(color_code, "FG:black", 8) == 0)
                {
                    // Cambiar a color negro
                    LETTER_BLACK;
                }
                else if (strncmp(color_code, "FG:yellow", 9) == 0)
                {
                    // Cambiar a color amarillo
                    LETTER_YELLOW;
                }
                else if (strncmp(color_code, "FG:purple", 9) == 0)
                {
                    // Cambiar a color magenta
                    LETTER_MAGENTA;
                }
                else if (strncmp(color_code, "FG:cyan", 7) == 0)
                {
                    // Cambiar a color cian
                    LETTER_CYAN;
                }
                else if (strncmp(color_code, "FG:white", 8) == 0)
                {
                    // Cambiar a color blanco
                    LETTER_WHITE;
                }
                else if (strncmp(color_code, "BG:black", 8) == 0)
                {
                    // Cambiar a fondo negro
                    BACKGROUND_COLOR_BLACK;
                }
                else if (strncmp(color_code, "BG:red", 6) == 0)
                {
                    // Cambiar a fondo rojo
                    BACKGROUND_COLOR_RED;
                }
                else if (strncmp(color_code, "BG:green", 8) == 0)
                {
                    // Cambiar a fondo verde
                    BACKGROUND_COLOR_GREEN;
                }
                else if (strncmp(color_code, "BG:yellow", 9) == 0)
                {
                    // Cambiar a fondo amarillo
                    BACKGROUND_COLOR_YELLOW;
                }
                else if (strncmp(color_code, "BG:purple", 9) == 0)
                {
                    // Cambiar a fondo magenta
                    BACKGROUND_COLOR_MAGENTA;
                }
                else if (strncmp(color_code, "BG:cyan", 7) == 0)
                {
                    // Cambiar a fondo cian
                    BACKGROUND_COLOR_CYAN;
                }
                else if (strncmp(color_code, "BG:white", 8) == 0)
                {
                    // Cambiar a fondo blanco
                    BACKGROUND_COLOR_WHITE;
                }
                else if (strncmp(color_code, "BG:blue", 7) == 0)
                {
                    // Cambiar a fondo azul
                    BACKGROUND_COLOR_BLUE;
                }
                else if (strncmp(color_code, "FG:", 3) == 0)
                {
                    // Comprobar si es un color personalizado FG:r;g;b
                    unsigned char red, green, blue;
                    if (sscanf(color_code, "FG:%hhu;%hhu;%hhu", &red, &green, &blue) == 3)
                    {
                        // Cambiar a color personalizado
                        foreground_color_custom_(red, green, blue);
                    }
                }
                else if (strncmp(color_code, "BG:", 3) == 0)
                {
                    // Comprobar si es un color personalizado FG:r;g;b
                    unsigned char red, green, blue;
                    if (sscanf(color_code, "BG:%hhu;%hhu;%hhu", &red, &green, &blue) == 3)
                    {
                        // Cambiar a color personalizado
                        background_color_custom_(red, green, blue);
                    }
                }
                else if (strncmp(color_code, "i64:", 4) == 0)
                {
                    sizes_num num;

                    if (sscanf(color_code, "i64:%llu", &num.i64))
                    {
                        print_sizes_num(num, 64);
                    }
                }
                else if (strncmp(color_code, "i32:", 4) == 0)
                {
                    sizes_num num;
                    if (sscanf(color_code, "i32:%u", &num.i32))
                    {
                        print_sizes_num(num, 32);
                    }
                }
                else if (strncmp(color_code, "i16:", 4) == 0)
                {
                    sizes_num num;
                    if (sscanf(color_code, "i16:%hu", &num.i16))
                    {
                        print_sizes_num(num, 16);
                    }
                }
                else if (strncmp(color_code, "i8:", 3) == 0)
                {
                    sizes_num num;

                    if (sscanf(color_code, "i8:%hhu", &num.i8))
                    {
                        print_sizes_num(num, 8);
                        printf("-%d-\n", num.i8);
                    }
                    else
                    {
                        print_sizes_num((sizes_num){.i8 = 0}, 8);
                    }
                    // printf("%d\n", num.i8);
                }
                else
                {
                    printf("%s: identificador invalido", color_code);
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
                    putchar('#');
                    putchar(*p);
                    fflush(stdout);
                }
            }
            else
            {
                if (*p == '\n')
                {
                    resetColorTerminal();
                }
                putchar(*p);
                fflush(stdout);
            }
        }

        p++;
    }

    // Restablecer colores
    resetColorTerminal();
    free(formatted_buffer);
}

void clear_line()
{
    printf(CLEAR_LINE);
}
void clear_display()
{
    printf(CLEAR_DISPLAY);
}
void set_title(const char *title)
{
    printf(SET_TITLE("%s"), title);
}
void pos(const unsigned char x, const unsigned char y, const char *data)
{
    printf(POS("%s", "%d", "%d"), x, y, data);
}
void back(const char *data, const unsigned char number)
{
    printf(BACK("%s", "%d"), number, data);
}
void forward(const char *data, const unsigned char number)
{
    printf(FORWARD("%s", "%d"), number, data);
}
void down(const char *data, const unsigned char number)
{
    printf(DOWN("%s", "%d"), number, data);
}
void up(const char *data, const unsigned char number)
{
    printf(UP("%s", "%d"), number, data);
}
static inline void foreground_color_custom_RGB(RGB_C color)
{
    foreground_color_custom_(color.r, color.g, color.b);
}
static void foreground_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    printf(FOREGROUND_COLOR_CUSTOM_RGB("%d", "%d", "%d"), red, green, blue);
}
static inline void background_color_custom_RGB(RGB_C color)
{
    background_color_custom_(color.red, color.green, color.blue);
}
static void background_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    printf(BACKGROUND_COLOR_CUSTOM_RGB("%d", "%d", "%d"), red, green, blue);
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
    foreground_color_custom_(redF, greenF, blueF);
    background_color_custom_(redB, greenB, blueB);
}

void ANSI_fore_color(ANSIColors color)
{
    printf(ANSI_COLOR_FOREGROUNG("%d"), color);
}
void ANSI_back_color(ANSIColors color)
{
    printf(ANSI_COLOR_BACKGROUNG("%d"), color);
}

void print_sizes_num(sizes_num byte, size_t size_word)
{
    switch (size_word)
    {
    case 8:
        for (int i = 7; i >= 0; i--)
        {
            unsigned char mask = 1U << i;
            unsigned char bit = byte.i8 & mask ? '1' : '0';
            putchar(bit);
        }
        break;
    case 16:
        for (int i = 15; i >= 0; i--)
        {
            unsigned short mask = 1U << i;
            unsigned char bit = byte.i16 & mask ? '1' : '0';
            putchar(bit);
        }
        break;
    case 32:
        for (int i = 31; i >= 0; i--)
        {
            unsigned long mask = 1UL << i;
            unsigned char bit = byte.i32 & mask ? '1' : '0';
            putchar(bit);
        }
        break;
    case 64:
        for (int i = 63; i >= 0; i--)
        {
            unsigned long long mask = 1ULL << i;
            unsigned char bit = byte.i64 & mask ? '1' : '0';
            putchar(bit);
        }
        break;
    default:
        puts("print_sizes_num: size_word desconocido");
        break;
    }
}

void print_bin(const void *data, size_t size)
{
    const unsigned char *bytePtr = (const unsigned char *)data;

    for (size_t byte = 0; byte < size; byte++)
    {
        for (size_t i = 8; i > 0; i--)
        {
            unsigned char mask = 1U << (i - 1);
            unsigned char bit = bytePtr[byte] & mask ? '1' : '0';
            putchar(bit);
        }
    }
}

#endif