/*
 *	Licencia Apache, Version 2.0 con Modificacion
 *	
 *	Copyright 2023 Desmon (David)
 *	
 *	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 *	este software y archivos de documentacion asociados (el "Software"), para tratar el 
 *	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 *	modificacion, fusion, publicacion, distribucion, sublicencia y/o venta de copias del 
 *	Software, y para permitir a las personas a quienes se les proporcione el Software 
 *	hacer lo mismo, sujeto a las siguientes condiciones:
 *	
 *	El anterior aviso de copyright y este aviso de permiso se incluiran en todas las 
 *	copias o partes sustanciales del Software.
 *	
 *	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTiA DE NINGÚN TIPO, EXPRESA O 
 *	IMPLiCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTiAS DE COMERCIABILIDAD, IDONEIDAD 
 *	PARA UN PROPoSITO PARTICULAR Y NO INFRACCIoN. EN NINGÚN CASO LOS TITULARES DEL 
 *	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERaN RESPONSABLES DE NINGÚN 
 *	RECLAMO, DAnO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIoN DE CONTRATO, AGRAVIO O DE 
 *	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIoN CON EL SOFTWARE O EL USO U OTRO TIPO
 *	DE ACCIONES EN EL SOFTWARE.
 *	
 *	Ademas, cualquier modificacion realizada por terceros se considerara propiedad del 
 *	titular original de los derechos de autor. Los titulares de derechos de autor 
 *	originales no se responsabilizan de las modificaciones realizadas por terceros.
 *	
 *	Queda explicitamente establecido que no es obligatorio especificar ni notificar los 
 *	cambios realizados entre versiones, ni revelar porciones especificas de codigo 
 *	modificado.
 */
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
    // si mayor que 255 entonces error
    if (x > 0xff)
    {
        puts("El numero debe estar en el rango de 0 a 255.\n");
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

//void __attribute__((destructor)) _RESET_COLOR__()
#ifdef _MSC_VER
void _RESET_COLOR__()
#else
void static __attribute__((destructor)) _RESET_COLOR__()
#endif
{
    // setConsoleColor(C_WHITE, C_BLACK);
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    resetColorTerminal();
    exit(0);
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
//void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__()
#ifdef _MSC_VER
void _ACTIVATE_COLORS_ANSI_WIN__()
#else
void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__()
#endif
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
    #if defined(MUTEX_NAME) && defined(_WIN32)
    // agregando mutex para multiproceso y multihilo en windows
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
    if (hMutex == NULL) {
        // El mutex no existe, crear uno nuevo
        hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
        if (hMutex == NULL) {
            printf("CreateMutex failed (%d).\n", GetLastError());
            return;
        }
    }

    // Esperar a que el mutex esté disponible
    WaitForSingleObject(hMutex, INFINITE);

    printf("\rpid: ");
    LETTER_LIGHTGREEN_EX;
    printf("%06d", GetCurrentProcessId());
    resetConsoleForegroundColor();
    printf(") ");
    #endif
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

                    if (sscanf(color_code, "i64:%"PRIu64, &num.i64))
                    {
                        print_sizes_num(num, 64);
                    }
                }
                else if (strncmp(color_code, "i32:", 4) == 0)
                {
                    sizes_num num;
                    if (sscanf(color_code, "i32:%"SCNu32, &num.i32))
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
                /* esta parte de aqui no era optima, por cada salto de linea, se reseteaba el color.
                    time   seconds   seconds    calls  Ts/call  Ts/call  name    
                    0.00      0.00     0.00       21     0.00     0.00  resetColorTerminal
                    0.00      0.00     0.00       10     0.00     0.00  printf_color
                    0.00      0.00     0.00       10     0.00     0.00  setConsoleForegroundColor
                    0.00      0.00     0.00       10     0.00     0.00  vprintf_color
                    0.00      0.00     0.00        1     0.00     0.00  clear_display
                    0.00      0.00     0.00        1     0.00     0.00  debug_set_level
                    0.00      0.00     0.00        1     0.00     0.00  resize_terminal
                    0.00      0.00     0.00        1     0.00     0.00  set_title
                    en un codigo simple donde se llama 10 veces a printf_color, se llama 10 veces a resetColorTerminal,
                    1 por finalizacion de la funcion mas 10 veces adicionales, por añadirse un \n, lo que añadio una llamada
                    adicional a resetColorTerminal, por cada llamada a printf_color, lo que duplica la cantidad de llamadas
                    a resetColorTerminal, por printf_color. 
                    Eliminado esta seccion se reduce las llamadas inecesarias a la mitad.
                 */
                //if (*p == '\n')
                //{
                //    resetColorTerminal();
                //}
                putchar(*p);
                fflush(stdout);
            }
        }

        p++;
    }

    // Restablecer colores
    resetColorTerminal();
    free(formatted_buffer);
    #if defined(MUTEX_NAME) && defined(_WIN32)
    // Liberar el mutex
    ReleaseMutex(hMutex);

    // Cerrar el handle del mutex
    CloseHandle(hMutex);
    #endif
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

#ifndef __DISABLE_COLORS_FORE_BACK_GROUND__ 
static void foreground_color_custom_RGB(RGB_C color)
{
    foreground_color_custom_(color.r, color.g, color.b);
}
static void foreground_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    printf(FOREGROUND_COLOR_CUSTOM_RGB("%d", "%d", "%d"), red, green, blue);
}
static void background_color_custom_RGB(RGB_C color)
{
    background_color_custom_(color.red, color.green, color.blue);
}
static void background_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    printf(BACKGROUND_COLOR_CUSTOM_RGB("%d", "%d", "%d"), red, green, blue);
}
#else
static void background_color_custom_RGB(RGB_C color)
{
    return; // no comptible para win7
}
static void background_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    return; // no comptible para win7
}
static void foreground_color_custom_RGB(RGB_C color)
{
    return; // no comptible para win7
}
static void foreground_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    return; // no comptible para win7
}
#endif
static void back_fore_color_custom_RGB(RGB_C colorBackGround, RGB_C colorForeGround)
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



char *get_addr_to_encoder_x86_(uint64_t addr) {
    /*
     *  
     * get_addr_to_encoder_x86(uint64_t addr, encoder_x86 encoder_val):
     * Esta funcion devuelve un string con la direccion de memoria formateada en 16, 32 o 64bits
     * 
     * Se espera recibir addr el cual es la direccion de memoria a formatear,
     * se espera recibir encoder_val, el cual indica si formatear la direcion a 16, 32 o 64bits.
     *      Posibles valores para encoder_x86 encoder_val:
     *          - ENCODER_IN_16bits = 0 : para 16bits
     *          - ENCODER_IN_32bits = 1 : para 32bits
     *          - ENCODER_IN_64bits = 2 : para 64bits
     * 
     * En caso de que malloc devuelva error, la funcion devuelve NULL
     *  
     */
    size_t size;

    size = (snprintf(NULL, 0, "%p", (size_t)addr) + 1) * sizeof(char);
    char * buffer_Position_memory = (char *)malloc(size);
    if (buffer_Position_memory == NULL) return NULL;
    sprintf(buffer_Position_memory, "%p", (size_t)addr);
    return buffer_Position_memory;
}

void resize_terminal(int rows, int cols) {
    #ifdef _WIN32
        // Obtener el identificador de la consola estándar
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
        // Crear una estructura de tamaño de búfer
        COORD newSize;
        newSize.X = cols;  // Número de columnas
        newSize.Y = rows;  // Número de filas
        
        // Establecer el tamaño del búfer
        SetConsoleScreenBufferSize(hConsole, newSize);
        
        // Cambiar el tamaño de la ventana
        SMALL_RECT rect;
        rect.Left = 0;
        rect.Top = 0;
        rect.Right = cols - 1;
        rect.Bottom = rows - 1;

        SetConsoleWindowInfo(hConsole, TRUE, &rect);
    #else



        struct winsize w;
        w.ws_row = rows;
        w.ws_col = cols;
        ioctl(STDOUT_FILENO, TIOCSWINSZ, &w);
    //*/
    //printf_color("\033[8;%d;%dt", rows, cols);
    #endif
}


void print_table_hex(char *string_init, char *string_text_for_printing, size_t size_string_text_for_printing) {
    /*
     *  
     * print_table_hex(char *string_init, char *string_text_for_printing, size_t size_string_text_for_printing):
     * Esta funcion imprime un "string_text_for_printing" en forma de tabla hexadecimal de tamaño de X * 0xf(16 en decimal).
     * Donde X es size_string_text_for_printing / 16. 
     * 
     * Se espera recibir un string_init, el cual es un string que se imprimira al inicio de cada fila.
     * Se espera recibir un string_text_for_printing el cual sea la cadena o secuencia de bytes a imprimir en formao hexadecimal
     * Se espera recibir un size_string_text_for_printing el cual sea el tamaño del string  o secuencia de bytes a imprimir.
     * 
     * En caso de que string_init no sea un puntero valido o NULL se usara una cadena vacia por defecto.
     * En caso de que string_text_for_printing no sea un puntero valido o NULL, la funcion no imprimira nada.
     * En caso de que size_string_text_for_printing sea 0 no se imprimira nada.
     *  
     */
    char my_string_default[] = "";
    if ((string_text_for_printing == NULL) || (size_string_text_for_printing == 0)) return; // error
    if (string_init == NULL) string_init = my_string_default; // no se ingreso un valor de incio que usar para imprimir cada fila

    size_t size = 0;
    char *buffer_Position_memory = get_addr_to_encoder_x86_(0);
    uint32_t level_space = strlen(buffer_Position_memory);

    
    printf_color("\n%s ", string_init);
    for (uint32_t i = 0; i < level_space; i++) putchar(' ');
    #ifndef __DISABLE_COLORS_FORE_BACK_GROUND__ 
        unsigned int random_color = jenkins_hash(string_text_for_printing[0], level_space, 0, 1, 2, 3, 4);
        // imprimir primera fila. (empezamos desde 0x23 para tener unos colores agradables)
        for (uint16_t r = 0x23; r < 0x33; r++) printf_color("|"FOREGROUND_COLOR_CUSTOM("%d")"%02x#{FG:reset}", r >> 2, ((uint8_t)(r-0x33)) - 0xf0 ); 
        printf_color("|\n%s"FOREGROUND_COLOR_CUSTOM("%d")"%s #{FG:reset}", string_init, ((((uint8_t)random_color >> 2)) & 0b1110111) | 0b00001001, buffer_Position_memory);
    #else
        for (uint16_t r = 0x23; r < 0x33; r++) printf_color("|%02x#{FG:reset}", r >> 2); 
        printf_color("|\n%s%s #{FG:reset}", string_init, buffer_Position_memory);
    #endif
    free(buffer_Position_memory);
    for (uint32_t i = 0; i < size_string_text_for_printing; i++)
    {
        #ifndef __DISABLE_COLORS_FORE_BACK_GROUND__
            // imprimir el resto de filas
            unsigned int Avalue1, Avalue2, Avalue3, seed, values[] = {
                (unsigned int)size_string_text_for_printing, 
                size, level_space,  0xa0, 0xe1, string_text_for_printing[i]
            };
            // generar 3 valores apartir de una semilla de entrada y 6 valores(pueden ser constantes o variables)
            seed = (unsigned int)(string_text_for_printing[i]);
            Avalue1 = jenkins_hash(seed,    values[0], values[1], values[2], values[3], values[4], values[5]);
            Avalue2 = jenkins_hash(Avalue1, values[0], values[1], values[2], values[3], values[4], values[5]);
            Avalue3 = jenkins_hash(Avalue2, values[0], values[1], values[2], values[3], values[4], values[5]);
            // mediante la operacion ((((uint8_t)valor >> 2)) & 0b1110111) | 0b00001001
            // de puede obtener colores claros
            
                printf_color("|"FOREGROUND_COLOR_CUSTOM("%d")"%.2X#{BG:reset}", 
                    ((((uint8_t)string_text_for_printing[i] >> 2)) & 0b1110111) | 0b00001001, 
                    (uint8_t)string_text_for_printing[i]);
        #else
            printf_color("|%.2X", 
                (uint8_t)string_text_for_printing[i]);
        #endif
        // imrpimir en X * 16
        if ((i+1) % ((256*4)/8 / 8) == 0){
            // imprimir la siguiente filas, despues de imprimir 16 bytes
            buffer_Position_memory = get_addr_to_encoder_x86_(i+1);
            #ifndef __DISABLE_COLORS_FORE_BACK_GROUND__ 
                random_color = jenkins_hash(string_text_for_printing[i], Avalue1, Avalue2, Avalue3, 2, 3, 4);
                printf_color("|\n%s"FOREGROUND_COLOR_CUSTOM("%d")"%s #{FG:reset}", string_init, ((((uint8_t)random_color >> 2)) & 0b1111111) | 0b00001001, buffer_Position_memory, i+1);
            #else
                printf_color("|\n%s%s #{FG:reset}", string_init, buffer_Position_memory, i+1);
            #endif
            free(buffer_Position_memory);
        }
    }
    printf("|\n");
}


#endif
