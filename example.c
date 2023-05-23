#include "colors.h"
#include <stdio.h>

int main(){
    
    clear_display();
    printf(POINTGREEN("hola mundo\n") );
    printf(POINTRED("hola mundo\n")   );
    printf(LETTER_BLACK   "negro\n"   );
    printf(LETTER_RED     "rojo\n"    );
    printf(LETTER_GREEN   "verde\n"   );
    printf(LETTER_YELLOW  "amarillo\n");
    printf(LETTER_BLUE    "azul\n"    );
    printf(LETTER_MAGENTA "magenta\n" );
    printf(LETTER_CYAN    "cyan\n"    );
    printf(LETTER_WHITE   "blanco\n"  );
    printf(LETTER_RESET   "reset color a por defecto\n");

    printf(LETTER_LIGHTBLACK_EX   "negro claro\n"     );
    printf(LETTER_LIGHTRED_EX     "rojo claro\n"      );
    printf(LETTER_LIGHTGREEN_EX   "verde claro\n"     );
    printf(LETTER_LIGHTYELLOW_EX  "amarillo claro\n"  );
    printf(LETTER_LIGHTBLUE_EX    "azul claro\n"      );
    printf(LETTER_LIGHTMAGENTA_EX "magenta claro\n"   );
    printf(LETTER_LIGHTCYAN_EX    "cyan claro\n"      );
    printf(LETTER_LIGHTWHITE_EX   "blanco claro\n"    );

    printf(LETTER_LIGHTRED_EX      "rojo claro\n"   );
    printf(BACKGROUND_COLOR_GREEN  "fondo verde\n"  );
    printf(STYLE_BOLDED     "negrita\n"             );
    printf(STYLE_DARKENED   "oscurecida\n"          );
    printf(STYLE_ITALICS    "italica o cursiva\n"   );
    printf(STYLE_UNDERLINED "subrayado\n"           );
    printf(STYLE_BLIKING    "parpadeo\n"            );
    printf(STYLE_INVERTED   "colores invertidos\n"  );

    printf(BACKGROUND_COLOR_BLACK    "fondo negro\n"        );
    printf(BACKGROUND_COLOR_RED      "fondo rojo\n"         );
    printf(BACKGROUND_COLOR_GREEN    "fondo verde\n"        );
    printf(BACKGROUND_COLOR_YELLOW   "fondo amarillo\n"     );
    printf(BACKGROUND_COLOR_BLUE     "fondo azul\n"         );
    printf(BACKGROUND_COLOR_MAGENTA  "fondo magenta\n"      );
    printf(BACKGROUND_COLOR_CYAN     "fondo cyan\n"         );
    printf(BACKGROUND_COLOR_WHITE    "fondo blanco\n"       );
    printf(BACKGROUND_COLOR_RESET    "fondo por defecto\n"  );

    printf(BACKGROUND_COLOR_CUSTOM("225", "0", "225")  FOREGROUND_COLOR_CUSTOM("0", "225", "225")  "color custom" BACKGROUND_COLOR_RESET "\n");

    printf_color("#{BG:green}#{FG:red}Hola: %d, %c#{BG:reset}\n", 1, 'c');    // Print "Hola: 1" in red
    printf_color("#{BG:blue}#{FG:green}Adios: %d, %f\n", 2, 1.2f);  // Print "Adios: 2" with blue background
    puts(LETTER_RESET);

    RGB_C my_px = RGB_CREATE(20, 30, 40);
    printf("r:%d, g:%d, b:%d\n", my_px.red, my_px.green, my_px.blue);
    foreground_color_custom(my_px);
    background_color_custom(RGB_CREATE(225, 30, 40));
    
    puts("hola");
    resetColorTerminal();
    foreground_color_custom(40, 30, 20);
    background_color_custom(RGB_CREATE(40, 30, 225));
    puts("adios");
    resetColorTerminal();

    //setConsoleColor(C_WHITE, C_BLACK);
}
