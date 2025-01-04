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
#define __version 2.0

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

/**
 * @defgroup color_definitions Definiciones de colores
 * @{
 */

/**
 * @enum ANSIColors
 * @brief Colores ANSI estándar para terminales.
 *
 * Esta enumeración define los colores estándar en ANSI que se pueden usar para cambiar
 * el color del texto en terminales compatibles con ANSI.
 */
typedef enum ANSIColors {
    ANSI_BLACK = 0,      /**< Color negro */
    ANSI_RED = 1,        /**< Color rojo */
    ANSI_GREEN = 2,      /**< Color verde */
    ANSI_YELLOW = 3,     /**< Color amarillo */
    ANSI_BLUE = 4,       /**< Color azul */
    ANSI_MAGENTA = 5,    /**< Color magenta */
    ANSI_CYAN = 6,       /**< Color cian */
    ANSI_WHITE = 7,      /**< Color blanco */
} ANSIColors;

// macros que se definen para cada version windows:
// https://learn.microsoft.com/es-es/windows/win32/winprog/using-the-windows-headers?redirectedfrom=MSDN#setting_winver_or__win32_winnt

#define REGULAR_COLORS_LETTER 30
#define HIGH_INTENSTY  90
#define REGULAR_COLORS_BACKGROUND 40
#define HIGH_INTENSTY_BACKGROUNG 100

/**
 * @brief Macro para establecer el color de primer plano (texto) en terminales ANSI.
 * 
 * @param color El color a aplicar (en formato ANSI).
 */
#define ANSI_COLOR_FOREGROUNG(color) "\033["   color "m"


/**
 * @brief Macro para establecer el color de fondo en terminales ANSI.
 * 
 * @param color El color de fondo a aplicar (en formato ANSI).
 */
#define ANSI_COLOR_BACKGROUNG(color) "\033[0;" color "m"

/**
 * @brief Macro para hacer el texto en negrita en terminales ANSI.
 * 
 * @param color El color a aplicar (en formato ANSI).
 */
#define ANSI_COLOR_BOLD(color)       "\033[1;" color "m"

/**
 * @brief Macro para subrayar el texto en terminales ANSI.
 * 
 * @param color El color a aplicar (en formato ANSI).
 */
#define ANSI_COLOR_UNDERLINE(color)  "\033[4;" color "m"

/**
 * @brief Función para establecer el color de primer plano en la terminal utilizando ANSI.
 * 
 * @param color Color a aplicar.
 */
void ANSI_fore_color(ANSIColors color);

/**
 * @brief Función para establecer el color de fondo en la terminal utilizando ANSI.
 * 
 * @param color Color a aplicar.
 */
void ANSI_back_color(ANSIColors color);


/**
 * @union sizes_num
 * @brief Unión para manejar diferentes tamaños de datos.
 *
 * Esta unión se usa para representar números de diferentes tamaños (64 bits, 32 bits, etc.)
 * en una variable, permitiendo convertir entre diferentes representaciones de enteros.
 */
typedef union sizes_num {
    uint64_t i64;  /**< Entero de 64 bits */
    uint32_t i32;  /**< Entero de 32 bits */
    uint16_t i16;  /**< Entero de 16 bits */
    uint8_t   i8;  /**< Entero de  8 bits */
} sizes_num;

#ifdef _WIN32
#include <Windows.h>


/**
 * @enum ConsoleColor
 * @brief Colores para consola en sistemas Windows.
 *
 * Esta enumeración define los colores disponibles en las consolas de Windows. Los valores
 * se corresponden con códigos de colores que se pueden usar con las funciones de consola
 * específicas de Windows.
 */

/** 
 * @def FOREGROUND_BLACK
 * @brief Define el color de primer plano como negro.
 */
#ifndef FOREGROUND_BLACK
#define FOREGROUND_BLACK 0
#endif


/** 
 * @def FOREGROUND_WHITE
 * @brief Define el color de primer plano como blanco, combinando rojo, verde y azul.
 */
#ifndef FOREGROUND_WHITE
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
//#define FOREGROUND_WHITE  0xf
#endif

/** 
 * @def FOREGROUND_MASK
 * @brief Define la máscara de color de primer plano, combinando rojo, verde y azul.
 */
#ifndef FOREGROUND_MASK
#define FOREGROUND_MASK (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
#endif

/** 
 * @def FOREGROUND_RESET
 * @brief Restablece el color de primer plano a su valor predeterminado (combinando rojo, verde y azul).
 */
#ifndef FOREGROUND_RESET
#define FOREGROUND_RESET FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#endif

/** 
 * @def FOREGROUND_YELLOW
 * @brief Define el color de primer plano como amarillo (rojo + verde).
 */
#ifndef FOREGROUND_YELLOW
#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN 
#endif

/** 
 * @def FOREGROUND_MAGENTA
 * @brief Define el color de primer plano como magenta (rojo + azul).
 */
#ifndef FOREGROUND_MAGENTA
#define FOREGROUND_MAGENTA FOREGROUND_RED | FOREGROUND_BLUE 
#endif

/** 
 * @def FOREGROUND_CYAN
 * @brief Define el color de primer plano como cian (verde + azul).
 */
#ifndef FOREGROUND_CYAN
#define FOREGROUND_CYAN FOREGROUND_GREEN | FOREGROUND_BLUE 
#endif

/** 
 * @def BACKGROUND_BLACK
 * @brief Define el color de fondo como negro.
 */
#ifndef BACKGROUND_BLACK
#define BACKGROUND_BLACK 0
#endif

/** 
 * @def BACKGROUND_WHITE
 * @brief Define el color de fondo como blanco (0xf0).
 */
#ifndef BACKGROUND_WHITE
#define BACKGROUND_WHITE 0xf0
#endif

/** 
 * @def BACKGROUND_YELLOW
 * @brief Define el color de fondo como amarillo (rojo + verde).
 */
#ifndef BACKGROUND_YELLOW
#define BACKGROUND_YELLOW BACKGROUND_RED | BACKGROUND_GREEN
#endif

/** 
 * @def BACKGROUND_MAGENTA
 * @brief Define el color de fondo como magenta (rojo + azul).
 */
#ifndef BACKGROUND_MAGENTA
#define BACKGROUND_MAGENTA BACKGROUND_RED | BACKGROUND_BLUE
#endif

/** 
 * @def BACKGROUND_CYAN
 * @brief Define el color de fondo como cian (verde + azul).
 */
#ifndef BACKGROUND_CYAN
#define BACKGROUND_CYAN BACKGROUND_GREEN | BACKGROUND_BLUE
#endif

//void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__();
#else
typedef enum ConsoleColor
{
    C_BLACK = ANSI_BLACK,
    C_RED = ANSI_RED,
    C_GREEN = ANSI_GREEN,
    C_YELLOW = ANSI_YELLOW,
    C_BLUE = ANSI_BLUE,
    C_MAGENTA = ANSI_MAGENTA,    
    C_CYAN = ANSI_CYAN,
    C_WHITE = ANSI_WHITE,
    
    C_LIGHTBLACK = ANSI_BLACK,
    C_LIGHTRED = ANSI_RED,
    C_LIGHTGREEN = ANSI_GREEN,
    C_LIGHTYELLOW = ANSI_YELLOW,
    C_LIGHTBLUE = ANSI_BLUE,
    C_LIGHTMAGENTA = ANSI_MAGENTA,
    C_LIGHTCYAN = ANSI_CYAN,
    C_LIGHTWHITE = ANSI_WHITE
} ConsoleColor;
#endif

/** 
 * @def BACKGROUND_COLOR_BLACK_ANSI
 * @brief Define la secuencia ANSI para establecer el color de fondo como negro.
 */
#define BACKGROUND_COLOR_BLACK_ANSI   "\033[0;40m"

/** 
 * @def BACKGROUND_COLOR_RED_ANSI
 * @brief Define la secuencia ANSI para establecer el color de fondo como rojo.
 */
#define BACKGROUND_COLOR_RED_ANSI     "\033[0;41m"

/** 
 * @def BACKGROUND_COLOR_GREEN_ANSI
 * @brief Define la secuencia ANSI para establecer el color de fondo como verde.
 */
#define BACKGROUND_COLOR_GREEN_ANSI   "\033[0;42m"

/** 
 * @def BACKGROUND_COLOR_YELLOW_ANSI
 * @brief Define la secuencia ANSI para establecer el color de fondo como amarillo.
 */
#define BACKGROUND_COLOR_YELLOW_ANSI  "\033[0;43m"

/** 
 * @def BACKGROUND_COLOR_BLUE_ANSI
 * @brief Define la secuencia ANSI para establecer el color de fondo como azul.
 */
#define BACKGROUND_COLOR_BLUE_ANSI    "\033[0;44m"

/** 
 * @def BACKGROUND_COLOR_MAGENTA_ANSI
 * @brief Define la secuencia ANSI para establecer el color de fondo como magenta.
 */
#define BACKGROUND_COLOR_MAGENTA_ANSI "\033[0;45m"

/** 
 * @def BACKGROUND_COLOR_CYAN_ANSI
 * @brief Define la secuencia ANSI para establecer el color de fondo como cian.
 */
#define BACKGROUND_COLOR_CYAN_ANSI    "\033[0;46m"

/** 
 * @def BACKGROUND_COLOR_WHITE_ANSI
 * @brief Define la secuencia ANSI para establecer el color de fondo como blanco.
 */
#define BACKGROUND_COLOR_WHITE_ANSI   "\033[0;47m"

/** 
 * @def BACKGROUND_COLOR_RESET_ANSI
 * @brief Restablece el color de fondo a su valor predeterminado.
 */
#define BACKGROUND_COLOR_RESET_ANSI   "\033[0m"


#ifdef _WIN32
#   define BACKGROUND_COLOR_GREEN       setConsoleBackgroundColor(BACKGROUND_GREEN  )
#   define BACKGROUND_COLOR_YELLOW      setConsoleBackgroundColor(BACKGROUND_YELLOW )
#   define BACKGROUND_COLOR_BLUE        setConsoleBackgroundColor(BACKGROUND_BLUE   )
#   define BACKGROUND_COLOR_RED         setConsoleBackgroundColor(BACKGROUND_RED    )
#   define BACKGROUND_COLOR_BLACK       setConsoleBackgroundColor(BACKGROUND_BLACK  )
#   define BACKGROUND_COLOR_MAGENTA     setConsoleBackgroundColor(BACKGROUND_MAGENTA)
#   define BACKGROUND_COLOR_CYAN        setConsoleBackgroundColor(BACKGROUND_CYAN   )
#   define BACKGROUND_COLOR_WHITE       setConsoleBackgroundColor(BACKGROUND_WHITE  )
#else
#   define BACKGROUND_COLOR_GREEN       setConsoleBackgroundColor(C_GREEN  )
#   define BACKGROUND_COLOR_YELLOW      setConsoleBackgroundColor(C_YELLOW )
#   define BACKGROUND_COLOR_BLUE        setConsoleBackgroundColor(C_BLUE   )
#   define BACKGROUND_COLOR_RED         setConsoleBackgroundColor(C_RED    )
#   define BACKGROUND_COLOR_BLACK       setConsoleBackgroundColor(C_BLACK  )
#   define BACKGROUND_COLOR_MAGENTA     setConsoleBackgroundColor(C_MAGENTA)
#   define BACKGROUND_COLOR_CYAN        setConsoleBackgroundColor(C_CYAN   )
#   define BACKGROUND_COLOR_WHITE       setConsoleBackgroundColor(C_WHITE  )
#endif


/** 
 * @def BACKGROUND_COLOR_RESET
 * @brief Restablece el color de fondo al predeterminado.
 */
#define BACKGROUND_COLOR_RESET       resetColorTerminal()


/** 
 * @def LETTER_BLACK_ANSI
 * @brief Define la secuencia ANSI para el color de letra negro.
 */
#define LETTER_BLACK_ANSI   "\033[30m"

/** 
 * @def LETTER_RED_ANSI
 * @brief Define la secuencia ANSI para el color de letra rojo.
 */
#define LETTER_RED_ANSI     "\033[31m"

/** 
 * @def LETTER_GREEN_ANSI
 * @brief Define la secuencia ANSI para el color de letra verde.
 */
#define LETTER_GREEN_ANSI   "\033[32m"

/** 
 * @def LETTER_YELLOW_ANSI
 * @brief Define la secuencia ANSI para el color de letra amarillo.
 */
#define LETTER_YELLOW_ANSI  "\033[33m"

/** 
 * @def LETTER_BLUE_ANSI
 * @brief Define la secuencia ANSI para el color de letra azul.
 */
#define LETTER_BLUE_ANSI    "\033[34m"

/** 
 * @def LETTER_MAGENTA_ANSI
 * @brief Define la secuencia ANSI para el color de letra magenta.
 */
#define LETTER_MAGENTA_ANSI "\033[35m"

/** 
 * @def LETTER_CYAN_ANSI
 * @brief Define la secuencia ANSI para el color de letra cian.
 */
#define LETTER_CYAN_ANSI    "\033[36m"

/** 
 * @def LETTER_WHITE_ANSI
 * @brief Define la secuencia ANSI para el color de letra blanca.
 */
#define LETTER_WHITE_ANSI   "\033[37m"

/** 
 * @def LETTER_RESET_ANSI
 * @brief Restablece el color de letra al predeterminado.
 */
#define LETTER_RESET_ANSI   "\033[38m"


/**
 * @def LETTER_LIGHTBLACK_EX_ANSI
 * @brief Color gris claro para la letra (ANSI).
 */
#define LETTER_LIGHTBLACK_EX_ANSI "\033[90m"

/**
 * @def LETTER_LIGHTRED_EX_ANSI
 * @brief Color rojo claro para la letra (ANSI).
 */
#define LETTER_LIGHTRED_EX_ANSI "\033[91m"

/**
 * @def LETTER_LIGHTGREEN_EX_ANSI
 * @brief Color verde claro para la letra (ANSI).
 */
#define LETTER_LIGHTGREEN_EX_ANSI "\033[92m"

/**
 * @def LETTER_LIGHTYELLOW_EX_ANSI
 * @brief Color amarillo claro para la letra (ANSI).
 */
#define LETTER_LIGHTYELLOW_EX_ANSI "\033[93m"

/**
 * @def LETTER_LIGHTBLUE_EX_ANSI
 * @brief Color azul claro para la letra (ANSI).
 */
#define LETTER_LIGHTBLUE_EX_ANSI "\033[94m"

/**
 * @def LETTER_LIGHTMAGENTA_EX_ANSI
 * @brief Color magenta claro para la letra (ANSI).
 */
#define LETTER_LIGHTMAGENTA_EX_ANSI "\033[95m"

/**
 * @def LETTER_LIGHTCYAN_EX_ANSI
 * @brief Color cian claro para la letra (ANSI).
 */
#define LETTER_LIGHTCYAN_EX_ANSI "\033[96m"

/**
 * @def LETTER_LIGHTWHITE_EX_ANSI
 * @brief Color blanco claro para la letra (ANSI).
 */
#define LETTER_LIGHTWHITE_EX_ANSI "\033[97m"


#ifdef _WIN32
#define LETTER_GREEN            setConsoleForegroundColor(FOREGROUND_GREEN)
#define LETTER_YELLOW           setConsoleForegroundColor(FOREGROUND_YELLOW)
#define LETTER_BLUE             setConsoleForegroundColor(FOREGROUND_BLUE)
#define LETTER_RED              setConsoleForegroundColor(FOREGROUND_RED)
#define LETTER_BLACK            setConsoleForegroundColor(FOREGROUND_BLACK)
#define LETTER_MAGENTA          setConsoleForegroundColor(FOREGROUND_MAGENTA)
#define LETTER_CYAN             setConsoleForegroundColor(FOREGROUND_CYAN)
#define LETTER_WHITE            setConsoleForegroundColor(FOREGROUND_WHITE)
#define LETTER_LIGHTBLACK_EX    setConsoleForegroundColor(FOREGROUND_BLACK   | FOREGROUND_INTENSITY)
#define LETTER_LIGHTRED_EX      setConsoleForegroundColor(FOREGROUND_RED     | FOREGROUND_INTENSITY)
#define LETTER_LIGHTGREEN_EX    setConsoleForegroundColor(FOREGROUND_GREEN   | FOREGROUND_INTENSITY)
#define LETTER_LIGHTYELLOW_EX   setConsoleForegroundColor(FOREGROUND_YELLOW  | FOREGROUND_INTENSITY)
#define LETTER_LIGHTBLUE_EX     setConsoleForegroundColor(FOREGROUND_BLUE    | FOREGROUND_INTENSITY)
#define LETTER_LIGHTMAGENTA_EX  setConsoleForegroundColor(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)
#define LETTER_LIGHTCYAN_EX     setConsoleForegroundColor(FOREGROUND_CYAN    | FOREGROUND_INTENSITY)
#define LETTER_LIGHTWHITE_EX    setConsoleForegroundColor(FOREGROUND_WHITE   | FOREGROUND_INTENSITY)
#else
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#define LETTER_GREEN             setConsoleForegroundColor(C_GREEN)
#define LETTER_YELLOW            setConsoleForegroundColor(C_YELLOW)
#define LETTER_BLUE              setConsoleForegroundColor(C_BLUE)
#define LETTER_RED               setConsoleForegroundColor(C_RED)
#define LETTER_BLACK             setConsoleForegroundColor(C_BLACK)
#define LETTER_MAGENTA           setConsoleForegroundColor(C_MAGENTA)
#define LETTER_CYAN              setConsoleForegroundColor(C_CYAN)
#define LETTER_WHITE             setConsoleForegroundColor(C_WHITE)
#define LETTER_LIGHTBLACK_EX     setConsoleForegroundColor(C_LIGHTBLACK)
#define LETTER_LIGHTRED_EX       setConsoleForegroundColor(C_LIGHTRED)
#define LETTER_LIGHTGREEN_EX     setConsoleForegroundColor(C_LIGHTGREEN)
#define LETTER_LIGHTYELLOW_EX    setConsoleForegroundColor(C_LIGHTYELLOW)
#define LETTER_LIGHTBLUE_EX      setConsoleForegroundColor(C_LIGHTBLUE)
#define LETTER_LIGHTMAGENTA_EX   setConsoleForegroundColor(C_LIGHTMAGENTA)
#define LETTER_LIGHTCYAN_EX      setConsoleForegroundColor(C_LIGHTCYAN)
#define LETTER_LIGHTWHITE_EX     setConsoleForegroundColor(C_LIGHTWHITE)
#endif 
#define LETTER_RESET       resetColorTerminal()


/**
 * @def STYLE_BOLDED
 * @brief Aplica estilo de texto en negrita.
 */
#define STYLE_BOLDED "\033[1m"

/**
 * @def STYLE_DARKENED
 * @brief Aplica estilo de texto oscurecido.
 */
#define STYLE_DARKENED "\033[2m"

/**
 * @def STYLE_ITALICS
 * @brief Aplica estilo de texto en cursiva.
 */
#define STYLE_ITALICS "\033[3m"

/**
 * @def STYLE_UNDERLINED
 * @brief Aplica estilo de texto subrayado.
 */
#define STYLE_UNDERLINED "\033[4m"

/**
 * @def STYLE_BLIKING
 * @brief Aplica estilo de texto parpadeante.
 */
#define STYLE_BLIKING "\033[5m"

/**
 * @def STYLE_INVERTED
 * @brief Invierte los colores de fondo y texto.
 */
#define STYLE_INVERTED "\033[7m"

/**
 * @def UP
 * @brief Mueve el cursor hacia arriba.
 * @param data Contenido que será renderizado.
 * @param number Número de líneas a mover hacia arriba.
 */
#define UP(data, number) "\033[" number "A" data

/**
 * @def DOWN
 * @brief Mueve el cursor hacia abajo.
 * @param data Contenido que será renderizado.
 * @param number Número de líneas a mover hacia abajo.
 */
#define DOWN(data, number) "\033[" number "B" data

/**
 * @def FORWARD
 * @brief Mueve el cursor hacia la derecha.
 * @param data Contenido que será renderizado.
 * @param number Número de espacios a mover hacia la derecha.
 */
#define FORWARD(data, number) "\033[" number "C" data

/**
 * @def BACK
 * @brief Mueve el cursor hacia la izquierda.
 * @param data Contenido que será renderizado.
 * @param number Número de espacios a mover hacia la izquierda.
 */
#define BACK(data, number) "\033[" number "D" data

/**
 * @def POS
 * @brief Mueve el cursor a una posición específica.
 * @param data Contenido que será renderizado.
 * @param number1 Línea a la que mover el cursor.
 * @param number2 Columna a la que mover el cursor.
 */

#define POS(data, number1, number2) "\033[" number1 ";" number2 "H" data

/**
 * @def SET_TITLE
 * @brief Cambia el título de la ventana de la terminal.
 * @param title Nuevo título para la ventana.
 */
#define SET_TITLE(title) "\033]2;" title "\007"

/**
 * @def CLEAR_DISPLAY
 * @brief Limpia completamente la pantalla de la terminal.
 */
#define CLEAR_DISPLAY "\033[3J\033[H\033[2J"

/**
 * @def CLEAR_LINE
 * @brief Limpia la línea actual del cursor.
 */
#define CLEAR_LINE "\033[K"

/**
 * @def HIDDEN_SLIDER
 * @brief Esconde el cursor en la terminal.
 */
#define HIDDEN_SLIDER "\033[?25l"

/**
 * @def SHOW_SLIDER
 * @brief Muestra el cursor en la terminal.
 */
#define SHOW_SLIDER "\033[?25h"

/**
 * @def SET_MODE_SLIDER
 * @brief Cambia el modo del cursor.
 */
#define SET_MODE_SLIDER "\033[?12l"

/**
 * @def SET_SIZE_SLIDER
 * @brief Cambia el tamaño del cursor.
 * @param size Tamaño deseado para el cursor.
 */
#define SET_SIZE_SLIDER(size) "\033[?" size "c"

/**
 * @def POINTGREEN
 * @brief Formato predefinido para mensajes con texto en verde, con un símbolo indicador en azul.
 * @param data Contenido del mensaje.
 */
#define POINTGREEN(data) "#{FG:green}[#{FG:blue}*#{FG:green}]#{FG:white}" data "#{FG:reset}"

/**
 * @def POINTRED
 * @brief Formato predefinido para mensajes con texto en púrpura, con un símbolo indicador en azul.
 * @param data Contenido del mensaje.
 */
#define POINTRED(data)   "#{FG:yellow}[#{FG:blue}*#{FG:yellow}]#{FG:purple}" data "#{FG:reset}"

#ifndef __DISABLE_COLORS_FORE_BACK_GROUND__ 

/**
 * @def BACKGROUND_COLOR_CUSTOM
 * @brief Define un color de fondo personalizado utilizando códigos ANSI.
 * @param color Código del color en formato ANSI (0-255).
 */
#define BACKGROUND_COLOR_CUSTOM(color) "\033[48;5;" color "m"

/**
 * @def BACKGROUND_COLOR_CUSTOM_RGB
 * @brief Define un color de fondo personalizado utilizando valores RGB.
 * @param red Componente de rojo (0-255).
 * @param green Componente de verde (0-255).
 * @param blue Componente de azul (0-255).
 */
#define BACKGROUND_COLOR_CUSTOM_RGB(red, green, blue) "\033[38;2;" red ";" green ";" blue "m"

/**
 * @def FOREGROUND_COLOR_CUSTOM
 * @brief Define un color de letra personalizado utilizando códigos ANSI.
 * @param color Código del color en formato ANSI (0-255).
 */
#define FOREGROUND_COLOR_CUSTOM(color) "\033[38;5;" color "m"

#else  // no comptible para win7
#warning BACKGROUND_COLOR_CUSTOM, BACKGROUND_COLOR_CUSTOM_RGB y FOREGROUND_COLOR_CUSTOM no son compatibles en Windows 7
#define BACKGROUND_COLOR_CUSTOM(color) color 
#define BACKGROUND_COLOR_CUSTOM_RGB(red, green, blue) red green blue
#define FOREGROUND_COLOR_CUSTOM(color) color
#endif

/**
 * @def FOREGROUND_COLOR_CUSTOM_RGB
 * @brief Define un color de letra personalizado utilizando valores RGB.
 * @param red Componente de rojo (0-255).
 * @param green Componente de verde (0-255).
 * @param blue Componente de azul (0-255).
 */
#define FOREGROUND_COLOR_CUSTOM_RGB(red, green, blue) "\033[48;2;" red ";" green ";" blue "m"

/**
 * @def BACK_FORE_COLOR_CUSTOM
 * @brief Define simultáneamente el color de fondo y el de letra.
 * @param Acolor Código del color de fondo en formato ANSI.
 * @param Bcolor Código del color de letra en formato ANSI.
 */
#define BACK_FORE_COLOR_CUSTOM(Acolor, Bcolor) BACKGROUND_COLOR_CUSTOM(Acolor) FOREGROUND_COLOR_CUSTOM(Bcolor)

/**
 * @def RGB_CREATE
 * @brief Crea una estructura RGB_C con valores específicos de rojo, verde y azul.
 * @param red Valor del componente rojo (0-255).
 * @param green Valor del componente verde (0-255).
 * @param blue Valor del componente azul (0-255).
 */
#define RGB_CREATE(red, green, blue) (RGB_C) {.r = red, .g = green, .b = blue}

/**
 * @typedef RGB_C
 * @brief Estructura para representar colores en formato RGB.
 */
typedef union RGB_C
{
    struct
    {
        unsigned char red;  /**< Valor de rojo. */
        unsigned char green;/**< Valor de verde. */
        unsigned char blue; /**< Valor de azul. */
    };
    struct
    {
        unsigned char r; /**< Alias para rojo. */
        unsigned char g; /**< Alias para verde. */
        unsigned char b; /**< Alias para azul. */
    };
} RGB_C;

/**
 * @def foreground_color_custom
 * @brief Define un color de letra utilizando argumentos genéricos (puede ser RGB_C o código ANSI).
 * @param ... Valores que determinan el color (pueden ser RGB_C o un código ANSI).
 */
#define foreground_color_custom(...) _Generic((__VA_ARGS__), \
    RGB_C: foreground_color_custom_RGB,                      \
    default: foreground_color_custom_)(__VA_ARGS__)


/**
 * @def background_color_custom
 * @brief Define un color de fondo utilizando argumentos genéricos (puede ser RGB_C o código ANSI).
 * @param ... Valores que determinan el color (pueden ser RGB_C o un código ANSI).
 */
#define background_color_custom(...) _Generic((__VA_ARGS__), \
    RGB_C: background_color_custom_RGB,                      \
    default: background_color_custom_)(__VA_ARGS__)

/**
 * @def back_fore_color_custom
 * @brief Define simultáneamente el color de fondo y el de letra utilizando argumentos genéricos.
 * @param ... Valores que determinan los colores (pueden ser RGB_C o códigos ANSI).
 */
#define back_fore_color_custom(...) _Generic((__VA_ARGS__), \
    RGB_C: back_fore_color_custom_RGB,                \
    default: back_fore_color_custom_)(__VA_ARGS__)

#ifdef _MSC_VER

/**
 * 
 * @brief Función que se llama al iniciar el programa para activar los colores ANSI en Windows.
 */
void _ACTIVATE_COLORS_ANSI_WIN__();

/**
 * @brief Función que se llama al salir del programa para restablecer los colores ANSI en Windows.
 */
void _RESET_COLOR__();

#else

/**
 * @brief Función que se llama al iniciar el programa para activar los colores ANSI en Windows.
 */
void __attribute__((constructor)) _ACTIVATE_COLORS_ANSI_WIN__();

/**
 * @brief Función que se llama al salir del programa para restablecer los colores ANSI en Windows.
 */
void static __attribute__((destructor)) _RESET_COLOR__();
#endif

void resize_terminal(int rows, int cols);
void clear_line();
void clear_display();

/**
 * @brief Función para cambiar el título de la terminal.
 * 
 * @param title El título que se desea establecer.
 */
void set_title(const char *title);

#ifdef _WIN32

/**
 * @brief Establece el color de primer plano en la consola para Windows.
 * 
 * @param foregroundColor El color de primer plano.
 */
void setConsoleForegroundColor(WORD foregroundColor);


/**
 * @brief Establece el color de fondo en la consola para Windows.
 * 
 * @param backgroundColor El color de fondo.
 */
void setConsoleBackgroundColor(WORD backgroundColor);

/**
 * @brief Establece ambos colores de primer plano y fondo en la consola de Windows.
 * 
 * @param foreground El color de primer plano.
 * @param background El color de fondo.
 */
void setConsoleColor(WORD foreground, WORD background);
#else

/**
 * @brief Establece el color de primer plano en la consola para Windows.
 * 
 * @param foregroundColor El color de primer plano.
 */
void setConsoleForegroundColor(ConsoleColor foregroundColor);


/**
 * @brief Establece el color de fondo en la consola para Windows.
 * 
 * @param backgroundColor El color de fondo.
 */
void setConsoleBackgroundColor(ConsoleColor backgroundColor);

/**
 * @brief Establece ambos colores de primer plano y fondo en la consola de Windows.
 * 
 * @param foreground El color de primer plano.
 * @param background El color de fondo.
 */
void setConsoleColor(ConsoleColor foreground, ConsoleColor background);
#endif

/**
 * @brief Restablece los colores de la terminal a los valores predeterminados.
 */
void resetColorTerminal();

/**
 * @brief Mueve el cursor a una posición específica en la terminal.
 * 
 * @param x Coordenada X de la posición.
 * @param y Coordenada Y de la posición.
 * @param data El texto a mostrar en esa posición.
 */
void pos(const unsigned char x, const unsigned char y, const char *data);

/**
 * @brief Mueve el cursor hacia atrás en la terminal.
 * 
 * @param data El texto a mostrar al mover el cursor.
 * @param number Número de posiciones a mover.
 */
void back(const char *data, const unsigned char number);

/**
 * @brief Mueve el cursor hacia adelante en la terminal.
 * 
 * @param data El texto a mostrar al mover el cursor.
 * @param number Número de posiciones a mover.
 */
void forward(const char *data, const unsigned char number);

/**
 * @brief Mueve el cursor hacia abajo en la terminal.
 * 
 * @param data El texto a mostrar al mover el cursor.
 * @param number Número de posiciones a mover.
 */
void down(const char *data, const unsigned char number);

/**
 * @brief Mueve el cursor hacia arriba en la terminal.
 * 
 * @param data El texto a mostrar al mover el cursor.
 * @param number Número de posiciones a mover.
 */
void up(const char *data, const unsigned char number);

/**
 * @brief Cambia el color de primer plano utilizando valores RGB.
 * 
 * Esta función cambia el color del texto en la terminal a un color especificado por los valores RGB.
 * 
 * @param color Estructura RGB_C que contiene los valores de color (rojo, verde, azul).
 */
static void foreground_color_custom_RGB(RGB_C color);

/**
 * @brief Cambia el color de primer plano utilizando valores RGB proporcionados como enteros.
 * 
 * Esta función cambia el color del texto en la terminal a un color especificado por los valores RGB
 * proporcionados como parámetros individuales.
 * 
 * @param red Componente rojo del color (0-255).
 * @param green Componente verde del color (0-255).
 * @param blue Componente azul del color (0-255).
 */
static void foreground_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue);

/**
 * @brief Cambia el color de fondo utilizando valores RGB.
 * 
 * Esta función cambia el color de fondo en la terminal a un color especificado por los valores RGB.
 * 
 * @param color Estructura RGB_C que contiene los valores de color (rojo, verde, azul).
 */
static void background_color_custom_RGB(RGB_C color);

/**
 * @brief Cambia el color de fondo utilizando valores RGB proporcionados como enteros.
 * 
 * Esta función cambia el color de fondo en la terminal a un color especificado por los valores RGB
 * proporcionados como parámetros individuales.
 * 
 * @param red Componente rojo del color (0-255).
 * @param green Componente verde del color (0-255).
 * @param blue Componente azul del color (0-255).
 */
static void background_color_custom_(const unsigned char red, const unsigned char green, const unsigned char blue);

/**
 * @brief Cambia los colores de fondo y primer plano utilizando valores RGB para ambos.
 * 
 * Esta función cambia tanto el color de fondo como el color del texto en la terminal, utilizando
 * los valores RGB para el fondo y para el primer plano.
 * 
 * @param colorBackGround Estructura RGB_C que contiene los valores de color para el fondo.
 * @param colorForeGround Estructura RGB_C que contiene los valores de color para el texto (primer plano).
 */
static void back_fore_color_custom_RGB(RGB_C colorBackGround, RGB_C colorForeGround);

/**
 * @brief Cambia los colores de fondo y primer plano utilizando valores RGB proporcionados como enteros.
 * 
 * Esta función cambia tanto el color de fondo como el color del texto en la terminal, utilizando
 * los valores RGB proporcionados como parámetros individuales para el fondo y el primer plano.
 * 
 * @param redB Componente rojo del color de fondo (0-255).
 * @param greenB Componente verde del color de fondo (0-255).
 * @param blueB Componente azul del color de fondo (0-255).
 * @param redF Componente rojo del color del texto (0-255).
 * @param greenF Componente verde del color del texto (0-255).
 * @param blueF Componente azul del color del texto (0-255).
 */
static void back_fore_color_custom_(unsigned char redB, unsigned char greenB,
                                        unsigned char blueB, unsigned char redF,
                                        unsigned char greenF, unsigned char blueF);

/**
 * @brief Función que calcula un hash de Jenkins para un conjunto de valores.
 * 
 * @param value El valor base.
 * @param n1 a n6 Los valores adicionales para el hash.
 * 
 * @return El valor de hash resultante.
 */
unsigned int jenkins_hash(
    unsigned int value,
    unsigned int n1, unsigned int n2, unsigned int n3,
    unsigned int n4, unsigned int n5, unsigned int n6);

/**
 * @brief Función que mezcla un array de enteros.
 * 
 * @param array El array a mezclar.
 * @param size El tamaño del array.
 */
void shuffle_array(int array[], int size);

/**
 * @brief Función que genera tres valores a partir de una semilla.
 * 
 * @param x La semilla.
 * @param value1, value2, value3 Los valores generados.
 * @param n1 a n6 Los valores adicionales para la generación.
 */
void generate_three_values(
    unsigned int x,
    unsigned int *value1,
    unsigned int *value2,
    unsigned int *value3,
    unsigned int n1, unsigned int n2, unsigned int n3,
    unsigned int n4, unsigned int n5, unsigned int n6);

/**
 * @brief Función que imprime un mensaje de texto con colores en formato de texto.
 * 
 * @param format El formato del texto con los colores.
 */
void printf_color(const char *format, ...);

/**
 * @brief Función similar a printf_color, pero acepta una lista de argumentos variable.
 * 
 * @param format El formato del texto con los colores.
 * @param args La lista de argumentos.
 */
void vprintf_color(const char *format, va_list args);

/**
 * @brief Función que imprime tamaños de variables de diferentes tipos de datos.
 * 
 * @param byte El valor a imprimir.
 * @param size_word El tamaño de los datos.
 */
void print_sizes_num(sizes_num byte, size_t size_word);

/**
 * @brief Función que imprime una tabla de valores en formato hexadecimal.
 * 
 * @param string_init El valor inicial.
 * @param string_text_for_printing El texto a imprimir.
 * @param size_string_text_for_printing El tamaño del texto.
 */
void print_table_hex(char *string_init, char *string_text_for_printing, size_t size_string_text_for_printing);

/**
 * @brief Función que obtiene la dirección de memoria para un codificador x86.
 * 
 * @param addr La dirección a obtener.
 * 
 * @return La dirección formateada como string.
 */
char *get_addr_to_encoder_x86_(uint64_t addr);

/** @} */

#include "colors.c"
#endif
