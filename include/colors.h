/**
 * @file colors.h
 * @brief Archivo de definición de colores para terminales con soporte para ANSI y Windows.
 *
 * Este archivo contiene definiciones y macros para manipular los colores de texto y fondo
 * en terminales compatibles con ANSI y en sistemas Windows, así como diversas funciones
 * para trabajar con la terminal, como mover el cursor, cambiar colores y manipular textos
 * con estilos.
 *
 * @license Apache License, Version 2.0 con Modificación.
 * Copyright 2023 Desmon (David)
 *
 * Se concede permiso a cualquier persona que obtenga una copia de este software para tratar
 * el software sin restricciones bajo los términos de la licencia Apache 2.0 con modificaciones.
 */


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
#ifndef __COLORS_H__
#define __COLORS_H__ "Desmon.hak.anon"
#define __version 2.1

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def ConsoleColor
 * @brief Codigo de colores estandar
 * @brief enumeracion de colores basicos
 */
typedef enum ConsoleColor
{
    COLOR_BLACK=0,
    COLOR_RED    ,
    COLOR_GREEN  ,
    COLOR_YELLOW ,
    COLOR_BLUE   ,
    COLOR_MAGENTA,
    COLOR_CYAN   ,
    COLOR_WHITE  ,

#ifdef _WIN32
    COLOR_LIGHTBLACK  ,
#else
    COLOR_LIGHTBLACK=0,
#endif

    COLOR_LIGHTRED    ,
    COLOR_LIGHTGREEN  ,
    COLOR_LIGHTYELLOW ,
    COLOR_LIGHTBLUE   ,
    COLOR_LIGHTMAGENTA,
    COLOR_LIGHTCYAN   ,
    COLOR_LIGHTWHITE  ,
} ConsoleColor;


/**
 * @typedef RGB_C
 * @brief Estructura para representar colores en formato RGB.
 *
 * La estructura principal consta de 3 valores R (red) G (green) B (blue)
 * La segunda solo es un alias para poder usar {.red=..., .green=...} y {.r=...}
 * siendo ambas la misma expresión
 */
typedef union RGB_C
{
    struct
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
} RGB_C;


/*
 *  ▒█  ▒█ ▀█▀ ▒█▄ ▒█   ▒█▀▀█ ▒█    █▀▀▄ ▀▀█▀▀ ▒█▀▀▀ ▒█▀▀▀█ ▒█▀▀▄ ▒█▀▄▀█
 *  ▒█▒█▒█ ▒█  ▒█▒█▒█   ▒█▄▄█ ▒█   ▒█▄▄█  ▒█   ▒█▀▀  ▒█  ▒█ ▒█▄▄▀ ▒█▒█▒█
 *  ▒▀▄▀▄▀ ▄█▄ ▒█  ▀█   ▒█    ▒█▄▄█▒█ ▒█  ▒█   ▒█    ▒█▄▄▄█ ▒█ ▒█ ▒█  ▒█
 *  ====================================================================
 */
#ifdef _WIN32

#include <Windows.h>

/**
 * @defgroup Macros definidas para cada version de windows
 *
 * @see https://learn.microsoft.com/es-es/windows/win32/winprog/using-the-windows-headers?redirectedfrom=MSDN#setting_winver_or__win32_winnt
 * @{
 */

#define HIGH_INTENSTY              90
#define REGULAR_COLORS_LETTER      30
#define HIGH_INTENSTY_BACKGROUNG  100
#define REGULAR_COLORS_BACKGROUND  40

/** @} */

/**
 * @def FOREGROUND_BLACK
 * @brief Define el color de primer plano como negro.
 */
#ifndef FOREGROUND_BLACK
#   define FOREGROUND_BLACK 0
#endif


/**
 * @def FOREGROUND_WHITE
 * @brief Define el color de primer plano como blanco, combinando rojo, verde y azul.
 */
#ifndef FOREGROUND_WHITE
#   define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
//#define FOREGROUND_WHITE  0xf
#endif


/**
 * @def FOREGROUND_MASK
 * @brief Define la máscara de color de primer plano, combinando rojo, verde y azul.
 */
#ifndef FOREGROUND_MASK
#   define FOREGROUND_MASK (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
#endif


/**
 * @def FOREGROUND_RESET
 * @brief Restablece el color de primer plano a su valor predeterminado (combinando rojo, verde y azul).
 */
#ifndef FOREGROUND_RESET
#   define FOREGROUND_RESET (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#endif


/**
 * @def FOREGROUND_YELLOW
 * @brief Define el color de primer plano como amarillo (rojo + verde).
 */
#ifndef FOREGROUND_YELLOW
#   define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#endif


/**
 * @def FOREGROUND_MAGENTA
 * @brief Define el color de primer plano como magenta (rojo + azul).
 */
#ifndef FOREGROUND_MAGENTA
#   define FOREGROUND_MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
#endif


/**
 * @def FOREGROUND_CYAN
 * @brief Define el color de primer plano como cian (verde + azul).
 */
#ifndef FOREGROUND_CYAN
#   define FOREGROUND_CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE)
#endif


/**
 * @def BACKGROUND_BLACK
 * @brief Define el color de fondo como negro.
 */
#ifndef BACKGROUND_BLACK
#   define BACKGROUND_BLACK 0
#endif


/**
 * @def BACKGROUND_WHITE
 * @brief Define el color de fondo como blanco (0xf0).
 */
#ifndef BACKGROUND_WHITE
#   define BACKGROUND_WHITE 0xf0
#endif


/**
 * @def BACKGROUND_YELLOW
 * @brief Define el color de fondo como amarillo (rojo + verde).
 */
#ifndef BACKGROUND_YELLOW
#   define BACKGROUND_YELLOW (BACKGROUND_RED | BACKGROUND_GREEN)
#endif


/**
 * @def BACKGROUND_MAGENTA
 * @brief Define el color de fondo como magenta (rojo + azul).
 */
#ifndef BACKGROUND_MAGENTA
#   define BACKGROUND_MAGENTA (BACKGROUND_RED | BACKGROUND_BLUE)
#endif


/**
 * @def BACKGROUND_CYAN
 * @brief Define el color de fondo como cian (verde + azul).
 */
#ifndef BACKGROUND_CYAN
#   define BACKGROUND_CYAN (BACKGROUND_GREEN | BACKGROUND_BLUE)
#endif


/**
 * @defgroup Alias para establecer un color al texto o al fondo de este
 * Los que inician con SET_BG es para el background (el fondo del texto)
 * Los que inician con SET_FG es para el foreground (el texto)
 * @{
 */
#define SET_BACKGROUND_COLOR_GREEN       setConsoleBackgroundColor(BACKGROUND_GREEN  )
#define SET_BACKGROUND_COLOR_YELLOW      setConsoleBackgroundColor(BACKGROUND_YELLOW )
#define SET_BACKGROUND_COLOR_BLUE        setConsoleBackgroundColor(BACKGROUND_BLUE   )
#define SET_BACKGROUND_COLOR_RED         setConsoleBackgroundColor(BACKGROUND_RED    )
#define SET_BACKGROUND_COLOR_BLACK       setConsoleBackgroundColor(BACKGROUND_BLACK  )
#define SET_BACKGROUND_COLOR_MAGENTA     setConsoleBackgroundColor(BACKGROUND_MAGENTA)
#define SET_BACKGROUND_COLOR_CYAN        setConsoleBackgroundColor(BACKGROUND_CYAN   )
#define SET_BACKGROUND_COLOR_WHITE       setConsoleBackgroundColor(BACKGROUND_WHITE  )

#define SET_LETTER_GREEN            setConsoleForegroundColor(FOREGROUND_GREEN  )
#define SET_LETTER_YELLOW           setConsoleForegroundColor(FOREGROUND_YELLOW )
#define SET_LETTER_BLUE             setConsoleForegroundColor(FOREGROUND_BLUE   )
#define SET_LETTER_RED              setConsoleForegroundColor(FOREGROUND_RED    )
#define SET_LETTER_BLACK            setConsoleForegroundColor(FOREGROUND_BLACK  )
#define SET_LETTER_MAGENTA          setConsoleForegroundColor(FOREGROUND_MAGENTA)
#define SET_LETTER_CYAN             setConsoleForegroundColor(FOREGROUND_CYAN   )
#define SET_LETTER_WHITE            setConsoleForegroundColor(FOREGROUND_WHITE  )

#define SET_LETTER_LIGHTBLACK    setConsoleForegroundColor(FOREGROUND_BLACK   | FOREGROUND_INTENSITY)
#define SET_LETTER_LIGHTRED      setConsoleForegroundColor(FOREGROUND_RED     | FOREGROUND_INTENSITY)
#define SET_LETTER_LIGHTGREEN    setConsoleForegroundColor(FOREGROUND_GREEN   | FOREGROUND_INTENSITY)
#define SET_LETTER_LIGHTYELLOW   setConsoleForegroundColor(FOREGROUND_YELLOW  | FOREGROUND_INTENSITY)
#define SET_LETTER_LIGHTBLUE     setConsoleForegroundColor(FOREGROUND_BLUE    | FOREGROUND_INTENSITY)
#define SET_LETTER_LIGHTMAGENTA  setConsoleForegroundColor(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)
#define SET_LETTER_LIGHTCYAN     setConsoleForegroundColor(FOREGROUND_CYAN    | FOREGROUND_INTENSITY)
#define SET_LETTER_LIGHTWHITE    setConsoleForegroundColor(FOREGROUND_WHITE   | FOREGROUND_INTENSITY)
/* @} */

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


/* PROTOTIPOS */

void setConsoleForegroundColor( WORD foregroundColor );
void setConsoleBackgroundColor( WORD backgroundColor );

#else
/*
 *  ▒█▀▀▀█ ▀▀█▀▀ ▒█ ▒█ ▒█▀▀▀ ▒█▀▀▄   ▒█▀▀█ ▒█    █▀▀▄ ▀▀█▀▀ ▒█▀▀▀ ▒█▀▀▀█ ▒█▀▀▄ ▒█▀▄▀█
 *  ▒█  ▒█  ▒█   ▒█▀▀█ ▒█▀▀▀ ▒█▄▄▀   ▒█▄▄█ ▒█   ▒█▄▄█  ▒█   ▒█▀▀  ▒█  ▒█ ▒█▄▄▀ ▒█▒█▒█
 *  ▒█▄▄▄█  ▒█   ▒█ ▒█ ▒█▄▄▄ ▒█ ▒█   ▒█    ▒█▄▄█▒█ ▒█  ▒█   ▒█    ▒█▄▄▄█ ▒█ ▒█ ▒█  ▒█
 *  ====================================================================
 */

/**
 * @defgroup Alias para establecer un color al texto o al fondo de este
 * Los que inician con SET_BG es para el background (el fondo del texto)
 * Los que inician con SET_FG es para el foreground (el texto)
 * @{
 */
#define SET_BG_COLOR_GREEN       setConsoleBackgroundColor( COLOR_GREEN   )
#define SET_BG_COLOR_YELLOW      setConsoleBackgroundColor( COLOR_YELLOW  )
#define SET_BG_COLOR_BLUE        setConsoleBackgroundColor( COLOR_BLUE    )
#define SET_BG_COLOR_RED         setConsoleBackgroundColor( COLOR_RED     )
#define SET_BG_COLOR_BLACK       setConsoleBackgroundColor( COLOR_BLACK   )
#define SET_BG_COLOR_MAGENTA     setConsoleBackgroundColor( COLOR_MAGENTA )
#define SET_BG_COLOR_CYAN        setConsoleBackgroundColor( COLOR_CYAN    )
#define SET_BG_COLOR_WHITE       setConsoleBackgroundColor( COLOR_WHITE   )

#define SET_FG_GREEN             setConsoleForegroundColor( COLOR_GREEN   )
#define SET_FG_YELLOW            setConsoleForegroundColor( COLOR_YELLOW  )
#define SET_FG_BLUE              setConsoleForegroundColor( COLOR_BLUE    )
#define SET_FG_RED               setConsoleForegroundColor( COLOR_RED     )
#define SET_FG_BLACK             setConsoleForegroundColor( COLOR_BLACK   )
#define SET_FG_MAGENTA           setConsoleForegroundColor( COLOR_MAGENTA )
#define SET_FG_CYAN              setConsoleForegroundColor( COLOR_CYAN    )
#define SET_FG_WHITE             setConsoleForegroundColor( COLOR_WHITE   )

#define SET_FG_LIGHTBLACK        setConsoleForegroundColor(COLOR_LIGHTBLACK  )
#define SET_FG_LIGHTRED          setConsoleForegroundColor(COLOR_LIGHTRED    )
#define SET_FG_LIGHTGREEN        setConsoleForegroundColor(COLOR_LIGHTGREEN  )
#define SET_FG_LIGHTYELLOW       setConsoleForegroundColor(COLOR_LIGHTYELLOW )
#define SET_FG_LIGHTBLUE         setConsoleForegroundColor(COLOR_LIGHTBLUE   )
#define SET_FG_LIGHTMAGENTA      setConsoleForegroundColor(COLOR_LIGHTMAGENTA)
#define SET_FG_LIGHTCYAN         setConsoleForegroundColor(COLOR_LIGHTCYAN   )
#define SET_FG_LIGHTWHITE        setConsoleForegroundColor(COLOR_LIGHTWHITE  )
/* @} */

void setConsoleForegroundColor( ConsoleColor foregroundColor );
void setConsoleBackgroundColor( ConsoleColor backgroundColor );

#endif

/*
 *
 *  ▒█▀▀█ ▒█▀▀▀ ▒█▄ ▒█ ▒█▀▀▀ ▒█▀▀▄ █▀▀▄ ▒█      ▒█▀▀▄ ▒█▀▀▀█ ▒█▀▀▄ ▒█▀▀▀
 *  ▒█ ▄▄ ▒█▀▀▀ ▒█▒█▒█ ▒█▀▀▀ ▒█▄▄▀▒█▄▄█ ▒█      ▒█    ▒█  ▒█ ▒█ ▒█ ▒█▀▀▀
 *  ▒█▄▄▀ ▒█▄▄▄ ▒█  ▀█ ▒█▄▄▄ ▒█ ▒█▒█ ▒█ ▒█▄▄█   ▒█▄▄▀ ▒█▄▄▄█ ▒█▄▄█ ▒█▄▄▄
 *  ====================================================================
 */

#define BACKGROUND_COLOR_RESET resetColorTerminal()
#define LETTER_RESET           resetColorTerminal()

/**
 * @def FOREGROUND_COLOR_CUSTOM_RGB
 * @brief Define un color de letra personalizado utilizando valores RGB.
 * @param red Componente de rojo (0-255).
 * @param green Componente de verde (0-255).
 * @param blue Componente de azul (0-255).
 */
#define FOREGROUND_COLOR_CUSTOM_RGB(red, green, blue) "\033[48;2;" red ";" green ";" blue "m"

/**
 * @union sizes_num
 * @brief Unión para manejar diferentes tamaños de datos.
 *
 * Esta unión se usa para representar números de diferentes tamaños (64 bits, 32 bits, etc.)
 * en una variable, permitiendo convertir entre diferentes representaciones de enteros.
 */
typedef union sizes_num {
    uint8_t   i8;
    uint16_t i16;
    uint32_t i32;
    uint64_t i64;
} sizes_num;

/**
 * @brief Función que calcula un hash de Jenkins para un conjunto de valores.
 *
 * @param value El valor base.
 * @param n1 a n6 Los valores adicionales para el hash.
 *
 * @return El valor de hash resultante.
 * @see https://en.wikipedia.org/wiki/Jenkins_hash_function
 */
uint32_t jenkins_hash(
        uint32_t value,
        uint32_t n1, uint32_t n2, uint32_t n3,
        uint32_t n4, uint32_t n5, uint32_t n6
    );

/**
 * @brief Restablece los colores de la terminal a los valores predeterminados.
 */
void resetColorTerminal(void);

/**
 * @brief Función similar a printf_color, pero acepta una lista de argumentos variable.
 *
 * @param format El formato del texto con los colores.
 * @param args La lista de argumentos.
 */
void vprintf_color(const char *format, va_list args);

static void foreground_color_custom(
    const uint8_t red  ,
    const uint8_t green,
    const uint8_t blue);

/**
 * @defgroup Funciones para restablecer el color del texto y del fondo a los predeterminados por el terminal
 * @{
 */
void resetColorTerminal    (void);
void resetConsoleForeground(void);
void resetConsoleBackground(void);

/* @} */


/**
 * @brief Cambia el color de fondo utilizando valores RGB proporcionados como enteros.
 *
 * Esta función cambia el color de fondo en la terminal a un color especificado por los valores RGB
 * proporcionados como parámetros individuales.
 *
 * @param red   Componente rojo  del color (0-255).
 * @param green Componente verde del color (0-255).
 * @param blue  Componente azul  del color (0-255).
 */
static void background_color_custom(const uint8_t red, const uint8_t green, const uint8_t blue);


/**
 * @brief Restablece el color al por defecto tanto del texto como del fondo de este mismo
 *
 * La funcion se activa automaticamente al finalizar el programa
 * Si se usa MSVC entonces se tiene que activar al final manualmente
*/
#ifdef _MSC_VER
void static _RESET_COLOR__(void)
#else
void static __attribute__((destructor)) _RESET_COLOR__(void)
#endif
{
    resetColorTerminal();
    exit(0);
}


/**
 * @brief Imprimite el numero en binario
 *
 * @param byte El valor a imprimir.
 * @param size_word El tamaño de los datos.
 */
void print_binary(sizes_num byte, uint8_t size_word);


/**
 * @brief Función que imprime un mensaje de texto con colores en formato de texto.
 *
 * @param format El formato del texto con los colores.
 */
void printf_color(const char *format, ...);


/**
 * @brief Macro para definir el color del texto en terminales ANSI
 *
 * @param color El color de texto a aplicar (en formato ANSI), color entre 0 y 255.
 *
 * @code
 *     printf("%sTexto en rojo\n", ANSI_COLOR_FG("1"));
 * @endcode
 *
 * @see https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#256-colors
 */
#define ANSI_COLOR_FG( color ) "\033[38;5;" color "m"


/**
 * @brief Macro para establecer el de fondo en terminales ANSI
 *
 * @param color El color de fondo a aplicar (en formato ANSI), color entre 0 y 255.
 *
 * @code
 *     printf("%sTexto con fondo azul\n", ANSI_COLOR_BG("4"));
 * @endcode
 *
 * @see https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#256-colors
 */
#define ANSI_COLOR_BG( color ) "\033[48;5;" color "m"


/**
 * @brief Macro para establecer el color brillante en terminales ANSI
 *
 * @param color El color brillante de texto a aplicar (en formato ANSI), color entre 0 y 255.
 *
 * @code
 *     printf("%sTexto rojo bold\n", ANSI_COLOR_BOLD("1"));
 * @endcode
 *
 * @see https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#colors--graphics-mode
 */
#define ANSI_COLOR_BOLD(color) "\033[1m\033[38;5;" color "m"

/**
 * @brief Macro para establecer el color del texto subrayado en terminales ANSI
 *
 * @param color El color de texto a aplicar (en formato ANSI), color entre 0 y 255.
 *
 * @code
 *     printf("%sTexto verde subrayado\n", ANSI_COLOR_UNDERLINE("10"));
 * @endcode
 *
 * @see https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#colors--graphics-mode
 */
#define ANSI_COLOR_UNDERLINE(color)  "\033[4m\033[38;5;" color "m"


/**
 * @brief Macro para restablecer el estilo, color y texto de en terminales ANSI
 *
 * @code
 *     printf("%sTexto rojo %stexto normal\n", ANSI_COLOR_FG("1"), ANSI_RESET_MODES);
 * @endcode
 *
 * @see https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#colors--graphics-mode
 */
#define ANSI_RESET_MODES "\033[0;0m"


/**
 * @def BG_COLOR_RESET
 * @brief Restablece el color de fondo al predeterminado.
 */
#define BG_COLOR_RESET       resetColorTerminal()


/**
 * @def FG_BLACK_ANSI
 * @brief Define la secuencia ANSI para el color de letra negro.
 */
#define FG_BLACK_ANSI   "\033[30m"


/**
 * @def FG_RED_ANSI
 * @brief Define la secuencia ANSI para el color de letra rojo.
 */
#define FG_RED_ANSI     "\033[31m"


/**
 * @def FG_GREEN_ANSI
 * @brief Define la secuencia ANSI para el color de letra verde.
 */
#define FG_GREEN_ANSI   "\033[32m"


/**
 * @def FG_YELLOW_ANSI
 * @brief Define la secuencia ANSI para el color de letra amarillo.
 */
#define FG_YELLOW_ANSI  "\033[33m"


/**
 * @def FG_BLUE_ANSI
 * @brief Define la secuencia ANSI para el color de letra azul.
 */
#define FG_BLUE_ANSI    "\033[34m"


/**
 * @def FG_MAGENTA_ANSI
 * @brief Define la secuencia ANSI para el color de letra magenta.
 */
#define FG_MAGENTA_ANSI "\033[35m"


/**
 * @def FG_CYAN_ANSI
 * @brief Define la secuencia ANSI para el color de letra cian.
 */
#define FG_CYAN_ANSI    "\033[36m"


/**
 * @def FG_WHITE_ANSI
 * @brief Define la secuencia ANSI para el color de letra blanca.
 */
#define FG_WHITE_ANSI   "\033[37m"


/**
 * @def FG_RESET_ANSI
 * @brief Restablece el color de letra al predeterminado.
 */
#define FG_RESET_ANSI   "\033[0;0m"


/**
 * @def FG_LIGHTBLACK_ANSI
 * @brief Color gris claro para la letra (ANSI).
 */
#define FG_LIGHTBLACK_ANSI "\033[90m"


/**
 * @def FG_LIGHTRED_ANSI
 * @brief Color rojo claro para la letra (ANSI).
 */
#define FG_LIGHTRED_ANSI "\033[91m"


/**
 * @def FG_LIGHTGREEN_ANSI
 * @brief Color verde claro para la letra (ANSI).
 */
#define FG_LIGHTGREEN_ANSI "\033[92m"


/**
 * @def FG_LIGHTYELLOW_ANSI
 * @brief Color amarillo claro para la letra (ANSI).
 */
#define FG_LIGHTYELLOW_ANSI "\033[93m"


/**
 * @def FG_LIGHTBLUE_ANSI
 * @brief Color azul claro para la letra (ANSI).
 */
#define FG_LIGHTBLUE_ANSI "\033[94m"


/**
 * @def FG_LIGHTMAGENTA_ANSI
 * @brief Color magenta claro para la letra (ANSI).
 */
#define FG_LIGHTMAGENTA_ANSI "\033[95m"


/**
 * @def FG_LIGHTCYAN_ANSI
 * @brief Color cian claro para la letra (ANSI).
 */
#define FG_LIGHTCYAN_ANSI "\033[96m"


/**
 * @def FG_LIGHTWHITE_ANSI
 * @brief Color blanco claro para la letra (ANSI).
 */
#define FG_LIGHTWHITE_ANSI "\033[97m"


/**
 * @def BACKGROUND_COLOR_CUSTOM_RGB
 * @brief Define un color de fondo personalizado utilizando valores RGB.
 * @param red Componente de rojo (0-255).
 * @param green Componente de verde (0-255).
 * @param blue Componente de azul (0-255).
 */
#define BACKGROUND_COLOR_CUSTOM_RGB(red, green, blue) "\033[38;2;" red ";" green ";" blue "m"


/**
 * @def foreground_color_custom
 * @brief Define un color de letra utilizando argumentos genéricos (puede ser RGB_C o código ANSI).
 * @param ... Valores que determinan el color (pueden ser RGB_C o un código ANSI).
 */
#define foreground_color_custom_(...) _Generic((__VA_ARGS__), \
    RGB_C: foreground_color_custom_RGB,                      \
    default: foreground_color_custom_)(__VA_ARGS__)


/**
 * @def background_color_custom
 * @brief Define un color de fondo utilizando argumentos genéricos (puede ser RGB_C o código ANSI).
 * @param ... Valores que determinan el color (pueden ser RGB_C o un código ANSI).
 */
#define background_color_custom_(...) _Generic((__VA_ARGS__), \
    RGB_C: background_color_custom_RGB,                      \
    default: background_color_custom_)(__VA_ARGS__)


/**
 * @def back_fore_color_custom
 * @brief Define simultáneamente el color de fondo y el de letra utilizando argumentos genéricos.
 * @param ... Valores que determinan los colores (pueden ser RGB_C o códigos ANSI).
 */
#define back_fore_color_custom_(...) _Generic((__VA_ARGS__), \
    RGB_C: back_fore_color_custom_RGB,                \
    default: back_fore_color_custom_)(__VA_ARGS__)


#include "colors.c"

#endif
