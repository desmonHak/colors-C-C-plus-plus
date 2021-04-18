# colors-C-C-
aqui tenemos una cabzera que incluye el modulo stdio.h por defecto. esta cabezera te permite manipular colores con C/C++ de una foma mas sencilla. para usarla importamos la cabezera mediante la directiva include:
<br>
#include "colors.h"
<br>
y desde donde se preciso en su codigo usar el la funcion printf puede hacer uso de la siguiente manera:<br>
<br>
#include "colors.h"<br>
int main(){<br>
    printf("%snegro\n", color.BLACK);<br>
}<br>
<br>
o si prefiere puede usar las funciones POINTGREEN() o POINTRED() para mostrar cierta informacion relevante:
<br>
#include "colors.h"<br>
int main(){<br>
    POINTGREEN("hola mundo\n", color);<br>
    POINTRED("hola mundo\n", color);<br>
}<br>

 ![Alt text](https://raw.githubusercontent.com/desmonHak/colors-C-C-plus-plus/main/Screenshot%20from%202021-04-18%2020-23-54.png) 
