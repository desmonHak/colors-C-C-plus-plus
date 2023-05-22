#include "colors.h"
#include <stdio.h>

int main(){
    
    CLEAR()
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

    printf(BACKGROUND_COLOR_BLACK    "fondo negro\n"        );
    printf(BACKGROUND_COLOR_RED      "fondo rojo\n"         );
    printf(BACKGROUND_COLOR_GREEN    "fondo verde\n"        );
    printf(BACKGROUND_COLOR_YELLOW   "fondo amarillo\n"     );
    printf(BACKGROUND_COLOR_BLUE     "fondo azul\n"         );
    printf(BACKGROUND_COLOR_PURPLE   "fondo magenta\n"      );
    printf(BACKGROUND_COLOR_CYAN     "fondo cyan\n"         );
    printf(BACKGROUND_COLOR_WHITE    "fondo blanco\n"       );
    printf(BACKGROUND_COLOR_RESET    "fondo por defecto\n"  );

}
