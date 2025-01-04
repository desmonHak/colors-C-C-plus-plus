#include "colors.c"
#include "colors.h"
#include <stdio.h>

int main(void){

    SET_FG_BLACK;
    printf_color(   "negro\n"   );
    SET_FG_RED;
    printf_color(     "rojo\n"    );
    SET_FG_GREEN;
    printf_color(   "verde\n"   );
    SET_FG_YELLOW;
    printf_color(  "amarillo\n");
    SET_FG_BLUE;
    printf_color(    "azul\n"    );
    SET_FG_MAGENTA;
    printf_color( "magenta\n" );
    SET_FG_CYAN;
    printf_color(    "cyan\n"    );
    SET_FG_WHITE;
    printf_color(   "blanco\n"  );
    LETTER_RESET;
    printf_color(   "reset color a por defecto\n");

    SET_FG_LIGHTBLACK;
    printf_color(   "negro claro\n"     );
    SET_FG_LIGHTRED;
    printf_color(     "rojo claro\n"      );
    SET_FG_LIGHTGREEN;
    printf_color(   "verde claro\n"     );
    SET_FG_LIGHTYELLOW;
    printf_color(  "amarillo claro\n"  );
    SET_FG_LIGHTBLUE;
    printf_color(    "azul claro\n"      );
    SET_FG_LIGHTMAGENTA;
    printf_color( "magenta claro\n"   );
    SET_FG_LIGHTCYAN;
    printf_color(    "cyan claro\n"      );
    SET_FG_LIGHTWHITE;
    printf_color(   "blanco claro\n"    );

    SET_FG_LIGHTRED;
    printf_color(      "rojo claro\n"   );
    SET_BG_COLOR_GREEN;
    printf_color(  "fondo verde#{reset}\n"  );
/*     printf_color(STYLE_BOLDED     "negrita\n"             );
    printf_color(STYLE_DARKENED   "oscurecida\n"          );
    printf_color(STYLE_ITALICS    "italica o cursiva\n"   );
    printf_color(STYLE_UNDERLINED "subrayado\n"           );
    printf_color(STYLE_BLIKING    "parpadeo\n"            );
    printf_color(STYLE_INVERTED   "colores invertidos\n"  );
 */
    SET_BG_COLOR_BLACK;
    printf_color(    "fondo negro#{reset}\n"        );
    SET_BG_COLOR_RED;
    printf_color(      "fondo rojo#{reset}\n"         );
    SET_BG_COLOR_GREEN;
    printf_color(    "fondo verde#{reset}\n"        );
    SET_BG_COLOR_YELLOW;
    printf_color(   "fondo amarillo#{reset}\n"     );
    SET_BG_COLOR_BLUE;
    printf_color(     "fondo azul#{reset}\n"         );
    SET_BG_COLOR_MAGENTA;
    printf_color(  "fondo magenta#{reset}\n"      );
    SET_BG_COLOR_CYAN;
    printf_color(     "fondo cyan#{reset}\n"         );
    SET_BG_COLOR_WHITE;
    printf_color(    "fondo blanco#{reset}\n"       );

    CONSOLE_COLOR_RESET;
    printf_color(    "fondo por defecto#{reset}\n"  );

/*     background_color_custom(RGB_CREATE(255, 0, 255)); */
    foreground_color_custom(0, 255, 255);
    printf_color("color custom#{FG:reset}\n");

    CONSOLE_COLOR_RESET;
    printf_color("#{BG:green}#{FG:red}Hola: %d, %c#{reset}\n", 1, 'c');    // Print "Hola: 1" in red
    printf_color("#{BG:blue}#{FG:green}Adios: %d, %f#{reset}\n", 2, 1.2f);  // Print "Adios: 2" with blue background

/*     RGB_C my_px = RGB_CREATE(20, 30, 40);
    printf_color("r:%d, g:%d, b:%d#{reset}\n", my_px.red, my_px.green, my_px.blue);
    foreground_color_custom(my_px);
    background_color_custom(RGB_CREATE(225, 30, 40));

    printf_color("hola#{reset}\n");

    back_fore_color_custom(40, 30, 225, 70, 120, 20);
    printf_color("adios#{reset}\n"); */

    printf_color("\n\nEstandar:\t");
    for (size_t i = 0; i <= COLOR_WHITE; i++){
        setConsoleForegroundColor(i + REGULAR_COLORS_BACKGROUND);
        printf_color(" %.3d ", i );
    }

    printf_color("\nIntense:\t");
    for (size_t i = 0; i <= COLOR_WHITE; i++){

        setConsoleForegroundColor(i + HIGH_INTENSTY_BACKGROUNG);
        printf_color(" %.3d ", i );
    }
    //unsigned char red = 0, green = 0, blue = 255;
    //printf("%d\n",16 + (red * 36) + (green * 5) * 6) + blue);

#define LOOP_TABLE(max, init, end) \
    for (size_t r = 0; r <= max; r+=36) { \
        for (size_t g = init; g <= end && r+g <= max; g++) { \
            printf_color(BACKGROUND_COLOR_CUSTOM("%d")" %.3d ",r+g, r+g); \
        } \
        puts(""); \
    } printf_color("\n");

    printf_color("\n\n");
    LOOP_TABLE(201, 16, 21)
    LOOP_TABLE(207, 22, 27)
    LOOP_TABLE(213, 28, 33)

    LOOP_TABLE(219, 34, 39)
    LOOP_TABLE(225, 40, 45)
    LOOP_TABLE(231, 46, 51)


    for (size_t r = 0; r < 255; r++) { \
        if (r % 6 == 0) {
            puts("");

        }
        printf_color(BACKGROUND_COLOR_CUSTOM("%d")" %.3d ",r, r);
        //resetColorTerminal();
    } printf_color("\n\n");

/*     unsigned int Avalue1, Avalue2, Avalue3, Bvalue1, Bvalue2, Bvalue3;
    int values[] = {12, 19, 5, 9, 3, 16};
    int _size = sizeof(values) / sizeof(values[0]);
    char my_str[] = "Hola mundo"; */

/*     for (size_t i=0;i< strlen(my_str); i++){
        generate_three_values(my_str[i], &Avalue1, &Avalue2, &Avalue3, values[0],values[1],values[2],values[3],values[4],values[5]);
        shuffle_array(values, _size);
        generate_three_values(my_str[i] % 64, &Bvalue1, &Bvalue2, &Bvalue3, values[0],values[1],values[2],values[3],values[4],values[5]);
        printf_color("#{FG:%d;%d;%d}#{BG:%d;%d;%d} %c #{reset}", Avalue1, Avalue2, Avalue3, Bvalue1, Bvalue2, Bvalue3, my_str[i]);
    } */
    puts("");
    printf_color("#{i32%d}\n", 0xf0f0f0f0);
    printf_color("#{i32:%d}\n", 0xf0f0f0f0);
}
