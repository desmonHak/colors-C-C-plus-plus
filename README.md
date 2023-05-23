# colors-C-C++

----

Aqui tenemos una cabzera que incluye el modulo stdio.h por defecto y Windows.h. esta cabezera te permite manipular colores con C/C++ de una foma mas sencilla en Windows y linux(Colores ANSI). Para poder usar colores ANSI en windows es necesario activar esta caracteristica, nuestro codigo se encarga de incluir una subrutina constructora que activa esta caracteristica si no lo esta cada vez que ejecutemos el programa. Puedes situar el archivo `example.c` con un ejemplo del uso de esta cabecera.
Para usarla incluiremos la cabezera mediante la directiva `include`:

```C
#include "colors.h"
```

Desde donde se preciso en su codigo usar el la funcion printf puede hacer uso de la siguiente manera:

```C
#include "colors.h"

int main(){
    printf_color(BLACK "negro\n");
    return 0;
}
```

Si prefiere puede usar las funciones POINTGREEN() o POINTRED() para mostrar cierta informacion relevante:

```C
#include "colors.h"

int main(){
    printf(POINTGREEN("hola mundo\n") );
    printf_color(POINTRED("hola mundo\n")   );
}
```

![imagen](https://raw.githubusercontent.com/desmonHak/colors-C-C-plus-plus/main/imagen.png) 

![imagen1](https://raw.githubusercontent.com/desmonHak/colors-C-C-plus-plus/main/imagen1.png) 


----

# Opciones disponibles:

Para letras:
```C
// letra negro oscuro
#define LETTER_BLACK           ...

// letra rojo ocuro
#define LETTER_RED             ...

// letra verde ocuro
#define LETTER_GREEN           ...

// letra amarillo oscuro
#define LETTER_YELLOW          ...

// letra azul oscuro
#define LETTER_BLUE            ...

// letra magenta oscuro
#define LETTER_MAGENTA         ...

// letra cyan ocuro:
#define LETTER_CYAN            ...

// letra blanco oscuro
#define LETTER_WHITE           ...

// resetear el color de la letra a la por defecto
#define LETTER_RESET           ...

// versiones claras de los colores de letra:
#define LETTER_LIGHTBLACK_EX   ...
#define LETTER_LIGHTRED_EX     ...
#define LETTER_LIGHTGREEN_EX   ...
#define LETTER_LIGHTYELLOW_EX  ...
#define LETTER_LIGHTBLUE_EX    ...
#define LETTER_LIGHTMAGENTA_EX ...
#define LETTER_LIGHTCYAN_EX    ...
#define LETTER_LIGHTWHITE_EX   ...
```

Colores de fondo:
```C
// fondo negro:
#define BACKGROUND_COLOR_BLACK  ...

// fondo rojo:
#define BACKGROUND_COLOR_RED    ...
#define BACKGROUND_COLOR_GREEN  ...
#define BACKGROUND_COLOR_YELLOW ...
#define BACKGROUND_COLOR_BLUE   ...
#define BACKGROUND_COLOR_PURPLE ...
#define BACKGROUND_COLOR_CYAN   ...
#define BACKGROUND_COLOR_WHITE  ...
#define BACKGROUND_COLOR_RESET  ...
```

Operaciones especiales:
```C
// Mover el cursor hacia arriba:
#define UP(data, number)        ...

// Mover el cursor hacia abajo:
#define DOWN(data, number)      ...

// Mover el cursor hacia la derecha:
#define FORWARD(data, number)   ...

// Mover el cursor hacia la izquierda
#define BACK(data, number)      ...

// Mover el cursor a una posición específica
#define POS(number1, number2)   ...

// cambiar titulo de la terminal:
#define SET_TITLE(title)        ...

// limpiar pantalla:
#define CLEAR_DISPLAY           ...

// limpiar una linea:
#define CLEAR_LINE              ...

// crear un string con punto verde al inicio
#define POINTGREEN(data)        ...

// esconder cursor
#define HIDDEN_SLIDER           ...

//  mostrar cursor
#define SHOW_SLIDER             ...

// cambiar el modo del cursor
#define SET_MODE_SLIDER         ...

// cambiar el tamaño del cursor
#define SET_SIZE_SLIDER(size)   ...

// crear un string con punto roojo al inicio
#define POINTRED(data)          ...

```

----

## Colores personalizados.

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