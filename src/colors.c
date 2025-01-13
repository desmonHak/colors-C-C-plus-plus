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
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  mode   = 0;

    if ( GetConsoleMode(handle, &mode) ) {
        if ( !(mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) ) {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(handle, mode);
        }
    }
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
void printf_color(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf_color(format, args);
    va_end(args);
}
void vprintf_color(const char* format, va_list args)
{
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

    size_t length_formated = (vsnprintf(NULL, 0, format, args) + 1) * sizeof(char);
    char  *buffer_formated = (char*)malloc(length_formated);

    if (length_formated < 5)
    {
        for (uint8_t i =0 ; i < (uint8_t)length_formated; i++) {
            putchar(buffer_formated[i]);
        }

        free(buffer_formated);
        return;
    }

    vsprintf(buffer_formated, format, args);

    const char *p = buffer_formated;
    uint8_t possible_color_code = 0;

    char    color_code[30] = {0};
    uint8_t color_code_idx =  0 ;

    while ( *p != '\0' )
    {
        if (*p == '#' && *(p+1) == '{') {
            color_code_idx = 0;

            p += 2;
            for (uint8_t idx = 0; idx < 30 && *p ; idx++, p++) {
                color_code[color_code_idx] = *p;
                color_code_idx++;

                if ( *p == '}' ) {
                    possible_color_code = 1;
                    break;
                }
            }

            color_code[color_code_idx-1] = '\0';
        } else {
            putchar(*p);
        }

        if ( possible_color_code ) {
            possible_color_code = 0;

            if (strncmp(color_code, "reset", 8) == 0) {
                resetConsoleForeground();

            } else if (strncmp(color_code, "FG:red", 6) == 0){
                SET_FG_RED;

            } else if (strncmp(color_code, "FG:lred", 8) == 0){
                SET_FG_LIGHTRED;

            } else if (strncmp(color_code, "FG:lblack", 8) == 0){
                SET_FG_LIGHTBLACK;

            } else if (strncmp(color_code, "FG:lgreen", 8) == 0){
                SET_FG_LIGHTGREEN;

            } else if (strncmp(color_code, "FG:lyellow", 8) == 0){
                SET_FG_LIGHTYELLOW;

            } else if (strncmp(color_code, "FG:lblue", 8) == 0){
                SET_FG_LIGHTBLUE;

            } else if (strncmp(color_code, "FG:lpurple", 8) == 0){
                SET_FG_LIGHTMAGENTA;

            } else if (strncmp(color_code, "FG:lcyan", 8) == 0){
                SET_FG_LIGHTCYAN;

            } else if (strncmp(color_code, "FG:lwhite", 8) == 0){
                SET_FG_LIGHTWHITE;

            } else if (strncmp(color_code, "FG:green", 8) == 0){
                SET_FG_GREEN;

            } else if (strncmp(color_code, "FG:blue", 7) == 0){
                SET_FG_BLUE;

            } else if (strncmp(color_code, "FG:black", 8) == 0){
                SET_FG_BLACK;

            } else if (strncmp(color_code, "FG:yellow", 9) == 0){
                SET_FG_YELLOW;

            } else if (strncmp(color_code, "FG:purple", 9) == 0){
                SET_FG_MAGENTA;

            } else if (strncmp(color_code, "FG:cyan", 7) == 0){
                SET_FG_CYAN;

            } else if (strncmp(color_code, "FG:white", 8) == 0){
                SET_FG_WHITE;

            } else if (strncmp(color_code, "BG:black", 8) == 0){
                SET_BG_COLOR_BLACK;

            } else if (strncmp(color_code, "BG:red", 6) == 0){
                SET_BG_COLOR_RED;

            } else if (strncmp(color_code, "BG:green", 8) == 0){
                SET_BG_COLOR_GREEN;

            } else if (strncmp(color_code, "BG:yellow", 9) == 0){
                SET_BG_COLOR_YELLOW;

            } else if (strncmp(color_code, "BG:purple", 9) == 0){
                SET_BG_COLOR_MAGENTA;

            } else if (strncmp(color_code, "BG:cyan", 7) == 0){
                SET_BG_COLOR_CYAN;

            } else if (strncmp(color_code, "BG:white", 8) == 0){
                SET_BG_COLOR_WHITE;

            } else if (strncmp(color_code, "BG:blue", 7) == 0) {
                SET_BG_COLOR_BLUE;

            } else if (strncmp(color_code, "FG:", 3) == 0) {

                uint8_t red, green, blue;
                if (sscanf(color_code, "FG:%hhu;%hhu;%hhu", &red, &green, &blue) == 3)
                    foreground_color_custom(red, green, blue);

            } else if (strncmp(color_code, "BG:", 3) == 0) {

                uint8_t red, green, blue;
                if (sscanf(color_code, "BG:%hhu;%hhu;%hhu", &red, &green, &blue) == 3)
                    background_color_custom(red, green, blue);

            } else if (strncmp(color_code, "i64:", 4) == 0) {

                sizes_num num;
                if (sscanf(color_code, "i64:%" PRIu64, &num.i64))
                    print_binary(num, 64);

            } else if (strncmp(color_code, "i32:", 4) == 0) {

                sizes_num num;
                if (sscanf(color_code, "i32:%" SCNu32, &num.i32))
                    print_binary(num, 32);

            } else if (strncmp(color_code, "i16:", 4) == 0) {

                sizes_num num;
                if (sscanf(color_code, "i16:%hu", &num.i16))
                    print_binary(num, 16);

            } else if (strncmp(color_code, "i8:", 3) == 0) {

                sizes_num num;
                if (sscanf(color_code, "i8:%hhu", &num.i8))
                    print_binary(num, 8);
                else
                    print_binary((sizes_num) { .i8 = 0 }, 8);

            } else {
                printf("%s: identificador invalido\n", color_code);
            }
        }

        p++;
    }

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
        /*  uint32_t temp = array[i];
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
    buffer_Position_memory = NULL;
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
                random_color = jenkins_hash(string_text_for_printing[i], Avalue1, Avalue2, Avalue3, 2, 3, 4);
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
