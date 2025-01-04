#ifndef __COLORS_C__
#define __COLORS_C__

#include "colors.h"

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

    if (length_formated < 3)
    {
        puts(buffer_formated);
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

            } else if (strncmp(color_code, "BG:blue", 7) == 0)
                SET_BG_COLOR_BLUE;
            else if (strncmp(color_code, "FG:", 3) == 0) {
                // Comprobar si es un color personalizado FG:r;g;b
                uint8_t red, green, blue;
                if (sscanf(color_code, "FG:%hhu;%hhu;%hhu", &red, &green, &blue) == 3)
                    // Cambiar a color personalizado
                    foreground_color_custom(red, green, blue);
            }
/*
            else if (strncmp(color_code, "BG:", 3) == 0) {
                // Comprobar si es un color personalizado FG:r;g;b
                uint8_t red, green, blue;
                if (sscanf(color_code, "BG:%hhu;%hhu;%hhu", &red, &green, &blue) == 3) {
                    // Cambiar a color personalizado
                    background_color_custom_(red, green, blue);
                }
            } else if (strncmp(color_code, "i64:", 4) == 0) {
                sizes_num num;

                if (sscanf(color_code, "i64:%" PRIu64, &num.i64)) {
                    print_sizes_num(num, 64);
                }
            } else if (strncmp(color_code, "i32:", 4) == 0) {
                sizes_num num;
                if (sscanf(color_code, "i32:%" SCNu32, &num.i32)) {
                    print_sizes_num(num, 32);
                }
            } else if (strncmp(color_code, "i16:", 4) == 0) {
                sizes_num num;
                if (sscanf(color_code, "i16:%hu", &num.i16)) {
                    print_sizes_num(num, 16);
                }
            } else if (strncmp(color_code, "i8:", 3) == 0) {
                sizes_num num;

                if (sscanf(color_code, "i8:%hhu", &num.i8)) {
                    print_sizes_num(num, 8);
                    printf("-%d-\n", num.i8);
                } else {
                    print_sizes_num((sizes_num) { .i8 = 0 }, 8);
                } */
                // printf("%d\n", num.i8);
            else {
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

void resetConsoleForeground(void)
{
    resetColorTerminal();
}


void resetConsoleBackground(void)
{
    resetColorTerminal();
}


void setConsoleForegroundColor( ConsoleColor foregroundColor )
{
    printf("\033[%dm", 30 + foregroundColor);
}

void resetColorTerminal(void)
{
    printf("\033[0;0m");
}


void setConsoleBackgroundColor(ConsoleColor backgroundColor)
{
    printf("\033[0;%dm", 40 + backgroundColor);
}

#endif

static void foreground_color_custom(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    printf(FOREGROUND_COLOR_CUSTOM_RGB("%d", "%d", "%d"), red, green, blue);
}

#endif // END __COLORS_C__
