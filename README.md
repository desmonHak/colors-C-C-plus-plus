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
    printf(BLACK "negro\n");
    return 0;
}
```

Si prefiere puede usar las funciones POINTGREEN() o POINTRED() para mostrar cierta informacion relevante:

```C
#include "colors.h"

int main(){
    printf(POINTGREEN("hola mundo\n") );
    printf(POINTRED("hola mundo\n")   );
}
```

![Alt text](https://raw.githubusercontent.com/desmonHak/colors-C-C-plus-plus/main/imagen.png) 

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
// posicionar el cursor n veces
#define UP(data, number)        ...

// bajar cursor n veces
#define DOWN(data, number)      ...

#define FORWARD(data, number)   ...

// cursor hacia atras:
#define BACK(data, number)      ...

// cursor hacia adelante
#define POS(number1, number2)   ...

// cambiar titulo a la ventana
#define SET_TITLE(title)        ...

// limpiar la ventana
#define CLEAR()                 ...

// crear un string con punto verde al inicio
#define POINTGREEN(data)        ...

// crear un string con punto roojo al inicio
#define POINTRED(data)          ...

```