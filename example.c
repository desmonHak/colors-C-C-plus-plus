#include "colors.h"
#include <stdio.h>

int main(){
    
    clear_display();
    printf_color(POINTGREEN("hola mundo\n") );
    printf_color(POINTRED("hola mundo\n")   );
    LETTER_BLACK;
    printf_color(   "negro\n"   );
    LETTER_RED;
    printf_color(     "rojo\n"    );
    LETTER_GREEN;
    printf_color(   "verde\n"   );
    LETTER_YELLOW;
    printf_color(  "amarillo\n");
    LETTER_BLUE;
    printf_color(    "azul\n"    );
    LETTER_MAGENTA;
    printf_color( "magenta\n" );
    LETTER_CYAN;
    printf_color(    "cyan\n"    );
    LETTER_WHITE;
    printf_color(   "blanco\n"  );
    LETTER_RESET;
    printf_color(   "reset color a por defecto\n");

    LETTER_LIGHTBLACK_EX;
    printf_color(   "negro claro\n"     );
    LETTER_LIGHTRED_EX;
    printf_color(     "rojo claro\n"      );
    LETTER_LIGHTGREEN_EX;
    printf_color(   "verde claro\n"     );
    LETTER_LIGHTYELLOW_EX;
    printf_color(  "amarillo claro\n"  );
    LETTER_LIGHTBLUE_EX;
    printf_color(    "azul claro\n"      );
    LETTER_LIGHTMAGENTA_EX;
    printf_color( "magenta claro\n"   );
    LETTER_LIGHTCYAN_EX;
    printf_color(    "cyan claro\n"      );
    LETTER_LIGHTWHITE_EX;
    printf_color(   "blanco claro\n"    );

    LETTER_LIGHTRED_EX;
    printf_color(      "rojo claro\n"   );
    BACKGROUND_COLOR_GREEN;
    printf_color(  "fondo verde\n"  );
    printf_color(STYLE_BOLDED     "negrita\n"             );
    printf_color(STYLE_DARKENED   "oscurecida\n"          );
    printf_color(STYLE_ITALICS    "italica o cursiva\n"   );
    printf_color(STYLE_UNDERLINED "subrayado\n"           );
    printf_color(STYLE_BLIKING    "parpadeo\n"            );
    printf_color(STYLE_INVERTED   "colores invertidos\n"  );

    BACKGROUND_COLOR_BLACK;
    printf_color(    "fondo negro#{BG:reset}\n"        );
    BACKGROUND_COLOR_RED;
    printf_color(      "fondo rojo#{BG:reset}\n"         );
    BACKGROUND_COLOR_GREEN;
    printf_color(    "fondo verde#{BG:reset}\n"        );
    BACKGROUND_COLOR_YELLOW;
    printf_color(   "fondo amarillo#{BG:reset}\n"     );
    BACKGROUND_COLOR_BLUE;
    printf_color(     "fondo azul#{BG:reset}\n"         );
    BACKGROUND_COLOR_MAGENTA;
    printf_color(  "fondo magenta#{BG:reset}\n"      );
    BACKGROUND_COLOR_CYAN;
    printf_color(     "fondo cyan#{BG:reset}\n"         );
    BACKGROUND_COLOR_WHITE;
    printf_color(    "fondo blanco#{BG:reset}\n"       );
    BACKGROUND_COLOR_RESET;
    printf_color(    "fondo por defecto#{BG:reset}\n"  );

    background_color_custom(RGB_CREATE(255, 0, 255));
    foreground_color_custom(0, 255, 255);
    printf_color("color custom#{FG:reset}\n");
    BACKGROUND_COLOR_RESET;

    printf_color("#{BG:green}#{FG:red}Hola: %d, %c#{BG:reset}\n", 1, 'c');    // Print "Hola: 1" in red
    printf_color("#{BG:blue}#{FG:green}Adios: %d, %f#{BG:reset}\n", 2, 1.2f);  // Print "Adios: 2" with blue background

    RGB_C my_px = RGB_CREATE(20, 30, 40);
    printf_color("r:%d, g:%d, b:%d#{FG:reset}\n", my_px.red, my_px.green, my_px.blue);
    foreground_color_custom(my_px);
    background_color_custom(RGB_CREATE(225, 30, 40));

    printf_color("hola#{FG:reset}\n");

    back_fore_color_custom(40, 30, 225, 70, 120, 20);
    printf_color("adios#{FG:reset}\n");

    printf_color("\n\nEstandar:\t");
    for (size_t i = 0; i <= ANSI_WHITE; i++){
        ANSI_back_color(i + REGULAR_COLORS_BACKGROUND);
        printf_color(" %.3d ", i );
    }
    printf_color("\nIntense:\t");
    for (size_t i = 0; i <= ANSI_WHITE; i++){
        ANSI_back_color(i + HIGH_INTENSTY_BACKGROUNG);
        printf_color(" %.3d ", i );
    }
    //unsigned char red = 0, green = 0, blue = 255;
    //printf("%d\n",16 + (red * 36) + (green * 5) * 6) + blue);

#define LOOP_TABLE(max, init, end) \
    for (size_t r = 0; r < max; r+=36) { \ 
        for (size_t g = init; g <= end; g++) { \
            printf_color("\033[48;5;%dm %.3d ",r+g, r+g); \
        } \
        puts(""); \
    } printf_color("\n\n");
    //background_color_custom(r, 0, g);

    printf_color("\n\n");
    LOOP_TABLE(201, 16, 21)
    LOOP_TABLE(207, 22, 27)
    LOOP_TABLE(213, 28, 33)


    //setConsoleColor(C_WHITE, C_BLACK);
}
