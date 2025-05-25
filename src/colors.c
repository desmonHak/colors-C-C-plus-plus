/*
 *	Licencia Apache, Versión 2.0 con Modificación
 *	
 *	Copyright 2023 Desmon (David)
 *	
 *	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 *	este software y archivos de documentación asociados (el "Software"), para tratar el 
 *	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 *	modificación, fusión, publicación, distribución, sublicencia y/o venta de copias del 
 *	Software, y para permitir a las personas a quienes se les proporcione el Software 
 *	hacer lo mismo, sujeto a las siguientes condiciones:
 *	
 *	El anterior aviso de copyright y este aviso de permiso se incluirán en todas las 
 *	copias o partes sustanciales del Software.
 *	
 *	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O 
 *	IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD 
 *	PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN. EN NINGÚN CASO LOS TITULARES DEL 
 *	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN 
 *	RECLAMO, DAÑO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE 
 *	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRO TIPO
 *	DE ACCIONES EN EL SOFTWARE.
 *	
 *	Además, cualquier modificación realizada por terceros se considerará propiedad del 
 *	titular original de los derechos de autor. Los titulares de derechos de autor 
 *	originales no se responsabilizan de las modificaciones realizadas por terceros.
 *	
 *	Queda explícitamente establecido que no es obligatorio especificar ni notificar los 
 *	cambios realizados entre versiones, ni revelar porciones específicas de código 
 *	modificado.
 */

#ifndef __COLORS_C__
#define __COLORS_C__

#include "colors.h"

/* ACTIVATE ANSI COLORS IN WINDOWS */

#ifdef _MSC_VER
/* Con MSVC se tiene que activar manualmente */
void _ACTIVATE_COLORS_ANSI_WIN__(void)
#else
void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__(void)
#endif
{
    #ifdef _WIN32
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD  mode   = 0;

        if ( GetConsoleMode(handle, &mode) ) {
            if ( !(mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) ) {
                mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(handle, mode);
            }
        }
    #endif
}

#ifdef _MSC_VER
void _RESET_COLOR__(void)
#else
void __attribute__((destructor)) _RESET_COLOR__(void)
#endif
{
    resetColorTerminal();
    exit(0);
}

uint32_t jenkins_hash(
    uint32_t value,
    uint32_t n1, uint32_t n2, uint32_t n3,
    uint32_t n4, uint32_t n5, uint32_t n6 )
{
    value = (value + 0x7ed55d16) + (value << n1);
    value = (value ^ 0xc761c23c) ^ (value >> n2);
    value = (value + 0x165667b1) + (value << n3);
    value = (value + 0xd3a2646c) ^ (value << n4);
    value = (value + 0xfd7046c5) + (value << n5);
    value = (value ^ 0xb55a4f09) ^ (value >> n6);
    return value % 256;
}


void print_binary(sizes_num num, uint8_t size_word) {
    switch (size_word) {
    case 8: {

        uint8_t mask = (uint8_t)1 << 7;
        for (uint8_t i = 0; i < 8; i++, num.i8 <<= 1)
            putchar(num.i8 & mask ? '1' : '0');

    } break;

    case 16: {

        uint16_t mask = (uint16_t)1 << 15;
        for (uint8_t i = 0; i < 16; i++, num.i16 <<= 1)
            putchar(num.i16 & mask ? '1' : '0');

    } break;

    case 32: {

        uint32_t mask = (uint32_t)1 << 31;
        for (uint8_t i = 0; i < 32; i++, num.i32 <<= 1)
            putchar(num.i32 & mask ? '1' : '0');

    } break;

    case 64: {

        uint64_t mask = (uint64_t)1 << 63;
        for (uint8_t i = 0; i < 64; i++, num.i64 <<= 1)
            putchar(num.i64 & mask ? '1' : '0');

    } break;

    default:
        puts("print_binary: size_word desconocido");
        break;
    }
}



// Función que imprime el texto alineado dentro de un ancho dado
void print_aligned(const char *text, size_t width, TextAlign align) {
    size_t len = strlen(text);
    if (len >= width) {
        // Si el texto es igual o más largo que el ancho, imprimir tal cual (o truncar si quieres)
        printf("%.*s", (int)width, text);
        return;
    }

    size_t padding_left = 0;
    size_t padding_right = 0;

    switch (align) {
        case ALIGN_LEFT:
            padding_right = width - len;
            break;

        case ALIGN_CENTER:
            padding_left = (width - len) / 2;
            padding_right = width - len - padding_left;
            break;

        case ALIGN_RIGHT:
            padding_left = width - len;
            break;
    }

    for (size_t i = 0; i < padding_left; i++) putchar(' ');
    printf("%s", text);
    for (size_t i = 0; i < padding_right; i++) putchar(' ');
}

void printf_color(const char *format, ...)
{
    va_list args = {0};
    va_start(args, format);
    vprintf_color(format, args);
    va_end(args);
}
void vprintf_color(const char* format, va_list args) {
#if defined(MUTEX_NAME) && defined(_WIN32)
    /* agregando mutex para multiproceso y multihilo en windows */
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
    if ( hMutex == NULL ) {
        /* El mutex no existe, crear uno nuevo */
        hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
        if (hMutex == NULL) {
            printf("CreateMutex failed (%d).\n", GetLastError());
            return;
        }
    }

    /* Esperar a que el mutex esté disponible */
    WaitForSingleObject(hMutex, INFINITE);

    printf("\rpid: ");

    SET_FG_LIGHTGREEN;
    printf("%06d", GetCurrentProcessId());
    resetConsoleForeground();
    printf(") ");
#endif

    va_list args_copy = {0};
    va_copy(args_copy, args);

    size_t length_formated = (vsnprintf(NULL, 0, format, args_copy) + 1) * sizeof(char);
    char  *buffer_formated = (char*)calloc(length_formated, sizeof(char));

    va_end(args_copy);

    vsprintf(buffer_formated, format, args);

    if (length_formated < 5)
    {
        for (uint8_t i = 0 ; i < (uint8_t)length_formated; i++) {
            putchar(buffer_formated[i]);
        }

        free(buffer_formated);
        return;
    }

    const char *c = buffer_formated;

    char color_code[30] = {0};

    do {
        uint8_t possible_color_code = 0;
        uint8_t color_code_idx      = 0;

        if (*c == '#' && *(c+1) && *(c+1) == '{') {

            c += 2;
            for (uint8_t i = 0; i < 29 && *c ; c++) {  // ← 29 para reservar lugar a '\0'
                if (*c == ' ')
                    continue;

                if (*c == '}') {
                    color_code[color_code_idx++] = *c;
                    color_code[color_code_idx] = '\0';
                    possible_color_code = 1;
                    break;
                }

                color_code[color_code_idx++] = *c;
            }
            color_code[color_code_idx] = '\0';


        } else {
            putchar(*c);
        }
    #define SIZEOF_STRING(str) (sizeof(str) - 1)
        if ( possible_color_code ) {
            uint8_t invalid_code = 0;
            uint8_t red, green, blue;
            sizes_num num;

            if (strncmp(color_code, "reset}", SIZEOF_STRING("reset}")) == 0) {
                CONSOLE_COLOR_RESET;

            }

            else if (color_code[0] == 'F') {
                if (strncmp(color_code, "FG:red}", SIZEOF_STRING("FG:red}")) == 0){
                    SET_FG_RED;

                } else if (strncmp(color_code, "FG:lred}", SIZEOF_STRING("FG:lred}")) == 0){
                    SET_FG_LIGHTRED;

                } else if (strncmp(color_code, "FG:lblack}", SIZEOF_STRING("FG:lblack}")) == 0){
                    SET_FG_LIGHTBLACK;

                } else if (strncmp(color_code, "FG:lgreen}", SIZEOF_STRING("FG:lgreen}")) == 0){
                    SET_FG_LIGHTGREEN;

                } else if (strncmp(color_code, "FG:lyellow}", SIZEOF_STRING("FG:lyellow}")) == 0){
                    SET_FG_LIGHTYELLOW;

                } else if (strncmp(color_code, "FG:lblue}", SIZEOF_STRING("FG:lblue}")) == 0){
                    SET_FG_LIGHTBLUE;

                } else if (strncmp(color_code, "FG:lpurple}", SIZEOF_STRING("FG:lpurple}")) == 0){
                    SET_FG_LIGHTMAGENTA;

                } else if (strncmp(color_code, "FG:lcyan}", SIZEOF_STRING("FG:lcyan}")) == 0){
                    SET_FG_LIGHTCYAN;

                } else if (strncmp(color_code, "FG:lwhite}", SIZEOF_STRING("FG:lwhite}")) == 0){
                    SET_FG_LIGHTWHITE;

                } else if (strncmp(color_code, "FG:green}", SIZEOF_STRING("FG:green}")) == 0){
                    SET_FG_GREEN;

                } else if (strncmp(color_code, "FG:blue}", SIZEOF_STRING("FG:blue}")) == 0){
                    SET_FG_BLUE;

                } else if (strncmp(color_code, "FG:black}", SIZEOF_STRING("FG:black}")) == 0){
                    SET_FG_BLACK;

                } else if (strncmp(color_code, "FG:yellow}", SIZEOF_STRING("FG:yellow}")) == 0){
                    SET_FG_YELLOW;

                } else if (strncmp(color_code, "FG:purple}", SIZEOF_STRING("FG:purple}")) == 0){
                    SET_FG_MAGENTA;

                } else if (strncmp(color_code, "FG:cyan}", SIZEOF_STRING("FG:cyan}")) == 0){
                    SET_FG_CYAN;

                } else if (strncmp(color_code, "FG:white}", SIZEOF_STRING("FG:white}")) == 0){
                    SET_FG_WHITE;

                } else if (strncmp(color_code, "FG:", 3) == 0) {
                    const char *p = color_code + 3;
                    char *endptr;

                    red   = (uint8_t)strtoul(p, &endptr, 10);
                    if (*endptr != ';') { invalid_code = 1; }
                    else {
                        p = endptr + 1;
                        green = (uint8_t)strtoul(p, &endptr, 10);
                        if (*endptr != ';') { invalid_code = 1; }
                        else {
                            p = endptr + 1;
                            blue = (uint8_t)strtoul(p, &endptr, 10);
                            if (*endptr != '}') { invalid_code = 1; }
                            else {
                                foreground_color_custom(red, green, blue);
                            }
                        }
                    }
                }
                else invalid_code = 1;
            }

            else if (color_code[0] == 'B') {
                if (strncmp(color_code, "BG:black}", SIZEOF_STRING("BG:black}")) == 0){
                    SET_BG_COLOR_BLACK;

                } else if (strncmp(color_code, "BG:red}", SIZEOF_STRING("BG:red}")) == 0){
                    SET_BG_COLOR_RED;

                } else if (strncmp(color_code, "BG:green}", SIZEOF_STRING("BG:green}")) == 0){
                    SET_BG_COLOR_GREEN;

                } else if (strncmp(color_code, "BG:yellow}", SIZEOF_STRING("BG:yellow}")) == 0){
                    SET_BG_COLOR_YELLOW;

                } else if (strncmp(color_code, "BG:purple}", SIZEOF_STRING("BG:purple}")) == 0){
                    SET_BG_COLOR_MAGENTA;

                } else if (strncmp(color_code, "BG:cyan}", SIZEOF_STRING("BG:cyan}")) == 0){
                    SET_BG_COLOR_CYAN;

                } else if (strncmp(color_code, "BG:white}", SIZEOF_STRING("BG:white}")) == 0){
                    SET_BG_COLOR_WHITE;

                } else if (strncmp(color_code, "BG:blue}", SIZEOF_STRING("BG:blue}")) == 0) {
                    SET_BG_COLOR_BLUE;

                } else if (strncmp(color_code, "BG:", SIZEOF_STRING("BG:")) == 0) {
                    const char *p = color_code + 3;
                    char *endptr;

                    red   = (uint8_t)strtoul(p, &endptr, 10);
                    if (*endptr != ';') { invalid_code = 1; }
                    else {
                        p = endptr + 1;
                        green = (uint8_t)strtoul(p, &endptr, 10);
                        if (*endptr != ';') { invalid_code = 1; }
                        else {
                            p = endptr + 1;
                            blue = (uint8_t)strtoul(p, &endptr, 10);
                            if (*endptr != '}') { invalid_code = 1; }
                            else {
                                background_color_custom(red, green, blue);
                            }
                        }
                    }
                } else invalid_code = 1;
            }

            else if (color_code[0] == 'i') {
                const char *p = color_code + 1;  // saltar 'i'
                char *endptr = NULL;

                if (strncmp(p, "64:", SIZEOF_STRING("64:")) == 0) {
                    num.i64 = strtoull(p + 3, &endptr, 10);
                    if (endptr && *endptr == '}')
                        print_binary(num, 64);
                    else
                        invalid_code = 1;

                } else if (strncmp(p, "32:", SIZEOF_STRING("32:")) == 0) {
                    num.i32 = strtoul(p + 3, &endptr, 10);
                    if (endptr && *endptr == '}')
                        print_binary(num, 32);
                    else
                        invalid_code = 1;

                } else if (strncmp(p, "16:", SIZEOF_STRING("16:")) == 0) {
                    const unsigned long val = strtoul(p + 3, &endptr, 10);
                    if (endptr && *endptr == '}' && val <= 0xFFFF) {
                        num.i16 = (uint16_t)val;
                        print_binary(num, 16);
                    } else {
                        invalid_code = 1;
                    }

                } else if (strncmp(p, "8:", SIZEOF_STRING("8:")) == 0) {
                    const unsigned long val = strtoul(p + 2, &endptr, 10);
                    if (endptr && *endptr == '}' && val <= 0xFF) {
                        num.i8 = (uint8_t)val;
                        print_binary(num, 8);
                    } else {
                        invalid_code = 1;
                    }

                } else {
                    invalid_code = 1;
                }
            } else if (color_code[0] == 'S'){
                if (strncmp(color_code, "ST:bold}", SIZEOF_STRING("ST:bold}")) == 0) {
                    printf(STYLE_BOLDED);

                } else if (strncmp(color_code, "ST:darkened}", SIZEOF_STRING("ST:darkened}")) == 0) {
                    printf(STYLE_DARKENED);

                } else if (strncmp(color_code, "ST:italics}", SIZEOF_STRING("ST:italics}")) == 0) {
                    printf(STYLE_ITALICS);

                } else if (strncmp(color_code, "ST:underline}", SIZEOF_STRING("ST:underline}")) == 0) {
                    printf(STYLE_UNDERLINED);

                } else if (strncmp(color_code, "ST:blink}", SIZEOF_STRING("ST:blink}")) == 0) {
                    printf(STYLE_BLIKING);

                } else if (strncmp(color_code, "ST:invert}", SIZEOF_STRING("ST:invert}")) == 0) {
                    printf(STYLE_INVERTED);

                } else invalid_code = 1;
            } else if (strncmp(color_code, "ALIGN:", 6) == 0) {
                const char *p = color_code + 6;
                char *endptr = NULL;
                unsigned long width = strtoul(p, &endptr, 10);
                if (endptr == NULL || *endptr != ':') {
                    invalid_code = 1;
                } else {
                    p = endptr + 1;
                    char align_char = *p++;
                    TextAlign align = ALIGN_LEFT;
                    if (align_char == 'L' || align_char == 'l') align = ALIGN_LEFT;
                    else if (align_char == 'C' || align_char == 'c') align = ALIGN_CENTER;
                    else if (align_char == 'R' || align_char == 'r') align = ALIGN_RIGHT;
                    else invalid_code = 1;

                    if (!invalid_code) {
                        // El texto está justo después del marcador de alineado (en c)
                        // Si el texto comienza con '}', sáltarlo
                        const char *text_start = c;
                        if (*text_start == '}') text_start++;

                        // Buscar el siguiente salto de línea o marcador especial
                        const char *text_end1 = strchr(text_start, '\n');
                        const char *text_end2 = strstr(text_start, "#{");
                        const char *text_end = NULL;
                        if (text_end1 && text_end2)
                            text_end = (text_end1 < text_end2) ? text_end1 : text_end2;
                        else if (text_end1)
                            text_end = text_end1;
                        else if (text_end2)
                            text_end = text_end2;
                        else
                            text_end = text_start + strlen(text_start);

                        size_t text_len = text_end - text_start;
                        char *text = (char*)calloc(text_len + 1, sizeof(char));
                        strncpy(text, text_start, text_len);
                        text[text_len] = '\0';

                        print_aligned(text, width, align);
                        free(text);

                        // Avanzar c hasta el final del texto alineado
                        c = text_end - 1; // -1 porque el bucle principal hará c++
                    }
                }
            }



            if (invalid_code) {
                if (color_code_idx > 0) {
                    color_code[color_code_idx - 1] = '\0';  // ← solo si hay algo antes
                } else {
                    strcpy(color_code, "desconocido");
                }
                printf("\n%s: identificador invalido\n", color_code);
            }

            if (possible_color_code && color_code[color_code_idx - 1] != '}') {
                invalid_code = 1;
            }


        }

        c++;
    } while ( *c != '\0' );

    fflush(stdout);
    free(buffer_formated);

#if defined(MUTEX_NAME) && defined(_WIN32)
    // Liberar el mutex
    ReleaseMutex(hMutex);

    // Cerrar el handle del mutex
    CloseHandle(hMutex);
#endif
}



#ifdef _WIN32
void setConsoleForegroundColor(WORD foregroundColor)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO console_info;

    GetConsoleScreenBufferInfo(handle, &console_info);
    WORD attributes = console_info.wAttributes;
    attributes &= 0xFFF0;
    attributes |= foregroundColor;

    SetConsoleTextAttribute(handle, attributes);
}

void resetConsoleForeground(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD attributes = consoleInfo.wAttributes;
    attributes &= 0xFFF0; // Eliminar el color de la letra actual
    attributes |= FOREGROUND_WHITE;
    SetConsoleTextAttribute(hConsole, attributes);
}


void resetConsoleBackground(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD originalAttrs = csbi.wAttributes;
    WORD backgroundAttrs = originalAttrs & 0xF0;
    SetConsoleTextAttribute(hConsole, backgroundAttrs);
}

void resetColorTerminal(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_MASK);
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

void resetConsoleForeground(void) {
    resetColorTerminal();
}


void resetConsoleBackground(void) {
    resetColorTerminal();
}


void setConsoleForegroundColor( ConsoleColor foregroundColor ) {
    printf("\033[38;5;%dm", foregroundColor);
}

void resetColorTerminal(void) {
    printf("\033[0;0m");
}


void setConsoleBackgroundColor(ConsoleColor backgroundColor) {
    printf("\033[48;5;%dm", backgroundColor);
}

#endif


void generate_three_values(
    uint32_t seed,
    uint32_t *value1,
    uint32_t *value2,
    uint32_t *value3,
    uint32_t n1, uint32_t n2, uint32_t n3,
    uint32_t n4, uint32_t n5, uint32_t n6)
{
    /* si mayor que 255 entonces error */
    if (seed > 0xff) {
        puts("El numero debe estar en el rango de 0 a 255.\n");
        return;
    }

    /* Aplicar la función de dispersión hash a los valores iniciales */
    *value1 = jenkins_hash(    seed, n1, n2, n3, n4, n5, n6 );
    *value2 = jenkins_hash( *value1, n1, n2, n3, n4, n5, n6 );
    *value3 = jenkins_hash( *value2, n1, n2, n3, n4, n5, n6 );
}


void shuffle_array(int32_t array[], int32_t size)
{
    srand(time(NULL));

    for (int32_t i = size - 1; i > 0; --i)
    {
        int32_t j = rand() % (i + 1);
        /* uint32_t temp = array[i];
           array[i] = array[j];
           array[j] = temp; */

        array[i] ^= array[j];
        array[j] ^= array[i];
        array[i] ^= array[j];
    }
}


void clear_display(void)
{
    printf(CLEAR_DISPLAY);
}

void resize_terminal( uint32_t rows, uint32_t cols ) {
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

    /* printf_color("\033[8;%d;%dt", rows, cols); */
    #endif
}

#include <inttypes.h> // para PRIuPTR y similares
#include <stdint.h>


char *get_addr_to_encoder_x86_(uint64_t addr) {
        size_t size;

        size = (snprintf(nullptr, 0, F_PTRNULL, (size_t)addr) + 1) * sizeof(char);
        char * buffer_Position_memory = (char *)malloc(size);
        if (buffer_Position_memory == NULL) return nullptr;
        sprintf(buffer_Position_memory, F_PTRNULL, (size_t)addr);
        return buffer_Position_memory;
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
    char my_string_default[] = " ";
    if ((string_text_for_printing == NULL) || (size_string_text_for_printing == 0)) return; // error
    if (string_init == NULL) string_init = my_string_default; // no se ingreso un valor de incio que usar para imprimir cada fila



    size_t size = 0;
    char *buffer_Position_memory = get_addr_to_encoder_x86_(0);
    uint32_t level_space = strlen(buffer_Position_memory);


    printf_color("\n %s ", string_init);
    for (uint32_t i = 0; i < level_space; i++) putchar(' ');
    #ifndef __DISABLE_COLORS_FORE_BACK_GROUND__
        unsigned int random_color = jenkins_hash(string_text_for_printing[0], level_space, 0, 1, 2, 3, 4);
        // imprimir primera fila. (empezamos desde 0x23 para tener unos colores agradables)
        for (uint16_t r = 0x23; r < 0x33; r++) printf_color("|"FOREGROUND_COLOR_CUSTOM("%d")"%02x#{reset}", r >> 2, ((uint8_t)(r-0x33)) - 0xf0 );
        printf_color("|\n %s"FOREGROUND_COLOR_CUSTOM("%d")"%s #{reset}", string_init, ((((uint8_t)random_color >> 2)) & 0b1110111) | 0b00001001, buffer_Position_memory);
    #else
        for (uint16_t r = 0x23; r < 0x33; r++) printf_color("|%02x#{reset}", r >> 2);
        printf_color("|\n %s%s #{reset}", string_init, buffer_Position_memory);
    #endif
    free(buffer_Position_memory);
    buffer_Position_memory = nullptr;
    for (uint32_t i = 0; i < size_string_text_for_printing; i++)
    {
        #ifndef __DISABLE_COLORS_FORE_BACK_GROUND__
            // imprimir el resto de filas
            unsigned int values[] = {
                (unsigned int)size_string_text_for_printing,
                size, level_space,  0xa0, 0xe1, string_text_for_printing[i]
            };
            // generar 3 valores apartir de una semilla de entrada y 6 valores(pueden ser constantes o variables)
            unsigned int seed = (unsigned int) (string_text_for_printing[i]);
            unsigned int n1 = jenkins_hash(seed, values[0], values[1], values[2], values[3], values[4], values[5]);
            unsigned int n2 = jenkins_hash(n1, values[0], values[1], values[2], values[3], values[4], values[5]);
            unsigned int n3 = jenkins_hash(n2, values[0], values[1], values[2], values[3], values[4], values[5]);
            // mediante la operacion ((((uint8_t)valor >> 2)) & 0b1110111) | 0b00001001
            // de puede obtener colores claros

                printf_color("|"FOREGROUND_COLOR_CUSTOM("%d")"%.2X#{reset}",
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
                random_color = jenkins_hash(string_text_for_printing[i], n1, n2, n3, 2, 3, 4);
                printf_color("|\n %s"FOREGROUND_COLOR_CUSTOM("%d")"%s #{reset}", string_init, ((((uint8_t)random_color >> 2)) & 0b1111111) | 0b00001001, buffer_Position_memory, i+1);
            #else
                printf_color("|\n %s%s #{reset}", string_init, buffer_Position_memory, i+1);
            #endif
            free(buffer_Position_memory);
            buffer_Position_memory = NULL;
        }
    }
    printf("|\n");
}

#endif /* END __COLORS_C__ */