#include "colors.h"

int main(){
    
    POINTGREEN("hola mundo\n", color);
    POINTRED("hola mundo\n", color);
    printf("%snegro\n", color.BLACK);
    printf("%srojo\n", color.RED);
    printf("%sverde\n", color.GREEN);
    printf("%samarillo\n", color.YELLOW);
    printf("%sazul\n", color.BLUE);
    printf("%smagenta\n", color.MAGENTA);
    printf("%scyan\n", color.CYAN);
    printf("%sblanco\n", color.WHITE);
    printf("%sreset color a por defecto\n", color.RESET);

    printf("%snegro claro\n", color.LIGHTBLACK_EX);
    printf("%srojo claro\n", color.LIGHTRED_EX);
    printf("%sverde claro\n", color.LIGHTGREEN_EX);
    printf("%samarillo claro\n", color.LIGHTYELLOW_EX);
    printf("%sazul claro\n", color.LIGHTBLUE_EX);
    printf("%smagenta claro\n", color.LIGHTMAGENTA_EX);
    printf("%scyan claro\n", color.LIGHTCYAN_EX);
    printf("%sblanco claro\n", color.LIGHTWHITE_EX);


}
