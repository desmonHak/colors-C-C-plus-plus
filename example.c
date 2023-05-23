#include "colors.h"
#include <stdio.h>

int main(){
    
    clear_display();
    printf_color(POINTGREEN("hola mundo\n") );
    printf_color(POINTRED("hola mundo\n")   );
    printf_color(LETTER_BLACK   "negro\n"   );
    printf_color(LETTER_RED     "rojo\n"    );
    printf_color(LETTER_GREEN   "verde\n"   );
    printf_color(LETTER_YELLOW  "amarillo\n");
    printf_color(LETTER_BLUE    "azul\n"    );
    printf_color(LETTER_MAGENTA "magenta\n" );
    printf_color(LETTER_CYAN    "cyan\n"    );
    printf_color(LETTER_WHITE   "blanco\n"  );
    printf_color(LETTER_RESET   "reset color a por defecto\n");

    printf_color(LETTER_LIGHTBLACK_EX   "negro claro\n"     );
    printf_color(LETTER_LIGHTRED_EX     "rojo claro\n"      );
    printf_color(LETTER_LIGHTGREEN_EX   "verde claro\n"     );
    printf_color(LETTER_LIGHTYELLOW_EX  "amarillo claro\n"  );
    printf_color(LETTER_LIGHTBLUE_EX    "azul claro\n"      );
    printf_color(LETTER_LIGHTMAGENTA_EX "magenta claro\n"   );
    printf_color(LETTER_LIGHTCYAN_EX    "cyan claro\n"      );
    printf_color(LETTER_LIGHTWHITE_EX   "blanco claro\n"    );

    printf_color(LETTER_LIGHTRED_EX      "rojo claro\n"   );
    printf_color(BACKGROUND_COLOR_GREEN  "fondo verde\n"  );
    printf_color(STYLE_BOLDED     "negrita\n"             );
    printf_color(STYLE_DARKENED   "oscurecida\n"          );
    printf_color(STYLE_ITALICS    "italica o cursiva\n"   );
    printf_color(STYLE_UNDERLINED "subrayado\n"           );
    printf_color(STYLE_BLIKING    "parpadeo\n"            );
    printf_color(STYLE_INVERTED   "colores invertidos\n"  );

    printf_color(BACKGROUND_COLOR_BLACK    "fondo negro#{BG:reset}\n"        );
    printf_color(BACKGROUND_COLOR_RED      "fondo rojo#{BG:reset}\n"         );
    printf_color(BACKGROUND_COLOR_GREEN    "fondo verde#{BG:reset}\n"        );
    printf_color(BACKGROUND_COLOR_YELLOW   "fondo amarillo#{BG:reset}\n"     );
    printf_color(BACKGROUND_COLOR_BLUE     "fondo azul#{BG:reset}\n"         );
    printf_color(BACKGROUND_COLOR_MAGENTA  "fondo magenta#{BG:reset}\n"      );
    printf_color(BACKGROUND_COLOR_CYAN     "fondo cyan#{BG:reset}\n"         );
    printf_color(BACKGROUND_COLOR_WHITE    "fondo blanco#{BG:reset}\n"       );
    printf_color(BACKGROUND_COLOR_RESET    "fondo por defecto#{BG:reset}\n"  );

    printf_color(BACKGROUND_COLOR_CUSTOM("225", "0", "225")  FOREGROUND_COLOR_CUSTOM("0", "225", "225")  "color custom" BACKGROUND_COLOR_RESET "\n");

    printf_color("#{BG:green}#{FG:red}Hola: %d, %c#{BG:reset}\n", 1, 'c');    // Print "Hola: 1" in red
    printf_color("#{BG:blue}#{FG:green}Adios: %d, %f#{BG:reset}\n", 2, 1.2f);  // Print "Adios: 2" with blue background

    RGB_C my_px = RGB_CREATE(20, 30, 40);
    printf_color("r:%d, g:%d, b:%d#{FG:reset}\n", my_px.red, my_px.green, my_px.blue);
    foreground_color_custom(my_px);
    background_color_custom(RGB_CREATE(225, 30, 40));

    printf_color("hola\n");

    back_fore_color_custom(40, 30, 225, 70, 120, 20);
    printf_color("adios\n");


    //setConsoleColor(C_WHITE, C_BLACK);
}
