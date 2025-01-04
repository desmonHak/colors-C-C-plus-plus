#include <stdarg.h>
#include "colors.h"

void print_color(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vprintf_color(format, args);

    va_end(args);
}

int main(void)
{
    print_color("#{FG:red} Hola\n");
    return 0;
}
