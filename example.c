#include "colors.h"
#include <stdio.h>

int main(){
    
    CLEAR()
    POINTGREEN("hola mundo\n");
    POINTRED("hola mundo\n");
    printf("%snegro\n", LETTER_BLACK);
    printf("%srojo\n", LETTER_RED);
    printf("%sverde\n", LETTER_GREEN);
    printf("%samarillo\n", LETTER_YELLOW);
    printf("%sazul\n", LETTER_BLUE);
    printf("%smagenta\n", LETTER_MAGENTA);
    printf("%scyan\n", LETTER_CYAN);
    printf("%sblanco\n", LETTER_WHITE);
    printf("%sreset color a por defecto\n", LETTER_RESET);

    printf("%snegro claro\n", LETTER_LIGHTBLACK_EX);
    printf("%srojo claro\n", LETTER_LIGHTRED_EX);
    printf("%sverde claro\n", LETTER_LIGHTGREEN_EX);
    printf("%samarillo claro\n", LETTER_LIGHTYELLOW_EX);
    printf("%sazul claro\n", LETTER_LIGHTBLUE_EX);
    printf("%smagenta claro\n", LETTER_LIGHTMAGENTA_EX);
    printf("%scyan claro\n", LETTER_LIGHTCYAN_EX);
    printf("%sblanco claro\n", LETTER_LIGHTWHITE_EX);

    printf("%sfondo negro\n", BACKGROUND_BLACK);
    printf("%sfondo rojo\n", BACKGROUND_RED);
    printf("%sfondo verde\n", BACKGROUND_GREEN);
    printf("%sfondo amarillo\n", BACKGROUND_YELLOW);
    printf("%sfondo azul\n", BACKGROUND_BLUE);
    printf("%sfondo magenta\n", BACKGROUND_PURPLE);
    printf("%sfondo cyan\n", BACKGROUND_CYAN);
    printf("%sfondo blanco\n", BACKGROUND_WHITE);
    printf("%sfondo por defecto\n", BACKGROUND_RESET);

}
