# COLORS

Una librería para Windows y Linux que permite manipular colores con C/C++.

---

Todo lo necesario esta en el directorio `include`, la cabecera inicial (`<colors.h>`) incluye por defecto el modulo `<stdio.h>` y `<Windows.h>` para poder manipular los colores de una forma mas sencilla.

La cabecera `<colors.h>` permite activar la caracteriztica para usar secuencias de escape ANSI en Windows y lo hace automaticamente. Pero si usas MSVC tienes que activarlo manualmente llamando a `_ACTIVATE_COLORS_ANSI_WIN__()`.

> [!IMPORTANT]
> Así como `_ACTIVATE_COLORS_ANSI_WIN__()` se activa solo (a menos que use MSVC donde se tiene que activar manualmente), ocurre lo mismo con `resetColorTerminal()`, esta se llama automaticamente al finalizar el programa (a menos que use MSVC);

---

## USOS

Puedes usar tanto `printf` o `printf_color` (que proporciona `<colors.h>`). La diferencia es que con `printf_color` puedes usar la sintaxis de interpolado `#{}` para poder utilizar los colores.

```C
#include "colors.h"

int main(void)
{
    printf(
        "%sHola %smundo%s!%s\n",
        FG_GREEN_ANSI,
        FG_RED_ANSI,
        ANSI_COLOR_BG("6"),
        FG_RESET_ANSI
    );

    printf_color("#{FG:green}Hola #{FG:red}mundo#{BG:cyan}!");

    return 0;
}

```

Tambien puedes usar uso de macros globales para cambiar el color de la letra y el fondo de esta misma.


```C
#include "colors.h"

int main(){
    SET_FG_CYAN;
    puts("Texto en Cyan");

    ANSI_RESET_MODES;
    puts("Texto normal");

    printf_color("#{BG:green}#{FG:red}letra en rojo con fondo verde: %d, %c, {BG:reset}\n", 1, 'c');

    printf_color("#{BG:blue}#{FG:green}letra en verde con fondo azul: %d, %f#{BG:reset}\n", 2, 1.2f);

    return 0;
}
```

Tambien puedes usar algunasde las macros para representar información. Tales como `POINTGREEN()` o `POINTRED()`.

```C
#include "colors.h"

int main(){
    printf(POINTGREEN(" hola mundo\n") );
    /* => [*] hola mundo */

    printf_color(POINTRED("hola mundo\n")   );
    /* => [*]hola mundo */
}
```

---

## COLORES DISPONIBLES

```C
/* colores para las letras: */
"FG:red"
"FG:green"
"FG:blue"
"FG:black"
"FG:yellow"
"FG:purple"
"FG:cyan"
"FG:white"

/* colores para el fondo: */
"BG:black"
"BG:red"
"BG:green"
"BG:yellow"
"BG:purple"
"BG:cyan"
"BG:white"
"BG:blue"

/* restablece los colores tanto al color de texto como el fondo de este */
"reset"
```

## EJEMPLOS

----

![imagen](https://raw.githubusercontent.com/desmonHak/colors-C-C-plus-plus/main/imagen.png) 

![imagen1](https://raw.githubusercontent.com/desmonHak/colors-C-C-plus-plus/main/imagen1.png) 


----

## COLORES PARA LETRAS

```C
/* letra negro oscuro */
#define LETTER_BLACK           ...

/* letra rojo ocuro */
#define LETTER_RED             ...

/* letra verde ocuro */
#define LETTER_GREEN           ...

/* letra amarillo oscuro */
#define LETTER_YELLOW          ...

/* letra azul oscuro */
#define LETTER_BLUE            ...

/* letra magenta oscuro */
#define LETTER_MAGENTA         ...

/* letra cyan ocuro: */
#define LETTER_CYAN            ...

/* letra blanco oscuro */
#define LETTER_WHITE           ...

/* resetear el color de la letra a la por defecto */
#define LETTER_RESET           ...

/* versiones claras de los colores de letra: */
#define LETTER_LIGHTBLACK_EX   ...
#define LETTER_LIGHTRED_EX     ...
#define LETTER_LIGHTGREEN_EX   ...
#define LETTER_LIGHTYELLOW_EX  ...
#define LETTER_LIGHTBLUE_EX    ...
#define LETTER_LIGHTMAGENTA_EX ...
#define LETTER_LIGHTCYAN_EX    ...
#define LETTER_LIGHTWHITE_EX   ...
```

## COLORES PARA EL FONDO

```C
#define BACKGROUND_COLOR_BLACK  ...
#define BACKGROUND_COLOR_RED    ...
#define BACKGROUND_COLOR_GREEN  ...
#define BACKGROUND_COLOR_YELLOW ...
#define BACKGROUND_COLOR_BLUE   ...
#define BACKGROUND_COLOR_PURPLE ...
#define BACKGROUND_COLOR_CYAN   ...
#define BACKGROUND_COLOR_WHITE  ...
#define BACKGROUND_COLOR_RESET  ...
```

# EXTRAS

```C
/* Mover el cursor hacia arriba */
#define UP(data, number)        ...

/* Mover el cursor hacia abajo */
#define DOWN(data, number)      ...

/* Mover el cursor hacia la derecha */
#define FORWARD(data, number)   ...

/* Mover el cursor hacia la izquierda */
#define BACK(data, number)      ...

/* Mover el cursor a una posición específica */
#define POS(number1, number2)   ...

/* cambiar titulo de la terminal: */
#define SET_TITLE(title)        ...

/* limpiar pantalla */
#define CLEAR_DISPLAY           ...

/* limpiar una linea */
#define CLEAR_LINE              ...

/* crear un string con punto verde al inicio */
#define POINTGREEN(data)        ...

/* esconder cursor */
#define HIDDEN_SLIDER           ...

/*  mostrar cursor */
#define SHOW_SLIDER             ...

/* cambiar el modo del cursor */
#define SET_MODE_SLIDER         ...

/* cambiar el tamaño del cursor */
#define SET_SIZE_SLIDER(size)   ...

/* crear un string con punto roojo al inicio */
#define POINTRED(data)          ...

/* permite borrar una linea */
void clear_line(); 

/* permite limpiar la pantalla entera */
void clear_display();

/* permite cambiar el titulo de la terminal */
void set_title(char *title);

/* permite mover el cursor a la cordenada (x, y) y imprimir la informacion contenida en data */
void pos(unsigned char x, unsigned char y, char *data);

/* permite retroceder el cursor n veces y mostrar informacion(data). */
void back(char *data, unsigned char number);

/* permite mover el cursor n veces a la derecha y mostrar informacion(data). */
void forward(char *data, unsigned char number);

/* permite mover el cursor n veces hacia abajo y mostrar informacion. */
void down(char *data, unsigned char number);

/* permite mover el cursor n veces hacia arriba y mostrar informacion. */
void up(char *data, unsigned char number);

/* version mejorada de printf: */
void printf_color(const char *format, ...);

/* permite cambiar el color de la terminal segun el ANSI */
void setConsoleColor(ConsoleColor foreground, ConsoleColor background);

/* resetea el color de la terminal al por defecto. */
void resetColorTerminal();

```

Otro formato a mencionar es sobre imprimir valores el binario.

```C
#include "colors.h"

int main(void)
{
    printf_color("El numero 12 en binario es: #{i8:12}\n");
    // => El numero 12 en binario es: 00001100

    printf_color("El numero 999 en binario es: #{i16:999}\n");
    // => El numero 999 en binario es: 0000001111100111

    return 0;
}

```

El valor maximo es de 64 bits (`i64`), pero estan disponibles: `i8`, `i16`, `i32` e `i64`.

----

## COLORES RGB

Podemos crear colores personalizados usando el sistema `RGB`. Para la tarea podemos crear una estructura `RGB_C` donde indicar los colores, usar la macro `RGB_CREATE` que crea esta misma, o podemos poner los valores red, green, blue directamente en lugar de crear la estructura.

Para crear una estructura RGB podemos hacerlo de estas maneras:
```C
RGB_C my_color_rgb = {100, 225, 30};

RGB_C my_color_rgb = RGB_CREATE(100, 225, 30);

RGB_C my_color_rgb = (RGB_C){
    .r = 100, 
    .g = 225, 
    .b = 30
};

RGB_C my_color_rgb = (RGB_C){
    .red = 100, 
    .green = 225, 
    .blue = 30
};
```
Todas las anteriores sirven para crear la misma estrutuctura, en este caso, tenemos un `'objeto RGB_C'` donde el rojo es 100, el verde es 225 y el azul es 30, recordar que el valor que podemos color aqui va de `0-255`.

Una vez realizado esto podemos usar 3 funciones para definir el color de fondo y la letra. Estas son:

- `foreground_color_custom(color_letra)`: para cambiar solo el color de la letra.
- `background_color_custom(color_fondo)`: para cambiar solo el color del fondo.
- `back_fore_color_custom(color_fondo, color_letra)`: para cambiar el color del fondo y la letra.

```C
RGB_C my_foreground = RGB_CREATE(100, 225, 30);
foreground_color_custom(my_foreground);
background_color_custom(RGB_CREATE(40, 30, 225));

back_fore_color_custom(RGB_CREATE(40, 30, 225), RGB_CREATE(100, 225, 30));
back_fore_color_custom(40, 30, 225, 100, 225, 30)
back_fore_color_custom(RGB_CREATE(40, 30, 225), my_foreground)
```

Todas las formas anteriormente vistas son validas y hacen lo mismo pero usando macros, estructuras directar, variables...(de distintas maneras hacer lo mismo).

----

### setConsoleColor()

Esta funcion permite cambiar el color de la letra y el fondo del terminal. Esta funcion recibe como primer argumento el `foreground` el cual a de ser un valor entero que forme parte de los colores `ANSI` del sistema deseado. Igual en el caso del segundo parametro `background`. Para facilitar la tarea tenemos un enum donde se definen los valores posibles que puede recibir la funcion:

```C
typedef enum ConsoleColor
{
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_YELLOW,
    COLOR_WHITE,

    COLOR_LIGHTBLACK,
    COLOR_LIGHTCYAN,
    COLOR_LIGHTRED,
    COLOR_LIGHTMAGENTA,
    COLOR_LIGHTYELLOW,
    COLOR_LIGHTWHITE
} ConsoleColor;
```

Hay que mencionar que los colores `COLOR_LIGH` no estan disponibles para el `background` con esta funcion, por lo que solo puede usar las versiones relativamente oscuras.

```C
setConsoleColor(COLOR_LIGHTYELLOW, COLOR_GREEN);
```
La definicion anterior cambia la letra a amarillo claro y el fondo a verde

----