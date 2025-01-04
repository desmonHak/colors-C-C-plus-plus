#include <stdarg.h>
#include "colors.h"

int main(void)
{
    printf(
        "%sHola %smundo%s!%s\n",
        FG_GREEN_ANSI,
        FG_RED_ANSI,
        ANSI_COLOR_BG("6"),
        FG_RESET_ANSI
    );


    printf_color("#{FG:green}Hola #{FG:red}mundo#{BG:cyan}!\n");
    return 0;
}
