#include "colors.h"
#include <stdio.h>

int main(void){
    #if defined(_WIN32) && defined(_MSC_VER)
        _ACTIVATE_COLORS_ANSI_WIN__();
    #endif

    clear_display();

    printf_color( "#{FG:black }Negro   \n" );
    printf_color( "#{FG:red   }rojo    \n" );
    printf_color( "#{FG:green }verde   \n" );
    printf_color( "#{FG:yellow}Amarillo\n" );
    printf_color( "#{FG:blue  }Azul    \n" );
    printf_color( "#{FG:purple}Purpura \n" );
    printf_color( "#{FG:cyan  }Cyan    \n" );
    printf_color( "#{FG:white }Blanco  \n" );

    CONSOLE_COLOR_RESET;
    printf_color( "color por defecto\n" );

    printf_color( "#{FG:lblack  }Negro claro    \n" );
    printf_color( "#{FG:lred    }Rojo claro     \n" );
    printf_color( "#{FG:lgreen  }Verde claro    \n" );
    printf_color( "#{FG:lyellow }Amarillo claro \n" );
    printf_color( "#{FG:lblue   }Azul claro     \n" );
    printf_color( "#{FG:lpurple }Purpura claro  \n" );
    printf_color( "#{FG:lcyan   }Cyan claro     \n" );
    printf_color( "#{FG:lwhite  }Blanco claro   \n" );
    printf_color( "#{FG:lred    }Rojo claro     \n" );

    CONSOLE_COLOR_RESET;

    printf_color( "#{ST:bold      }negrita            #{reset}\n" );
    printf_color( "#{ST:darkened  }oscurecida         #{reset}\n" );
    printf_color( "#{ST:italics   }italica o cursiva  #{reset}\n" );
    printf_color( "#{ST:underline }subrayado          #{reset}\n" );
    printf_color( "#{ST:blink     }parpadeo           #{reset}\n" );
    printf_color( "#{ST:invert    }colores invertidos #{reset}\n" );

    printf_color( "#{BG:green  }Fondo verde   #{reset}\n" );
    printf_color( "#{BG:black  }Fondo negro   #{reset}\n" );
    printf_color( "#{BG:red    }Fondo rojo    #{reset}\n" );
    printf_color( "#{BG:green  }Fondo verde   #{reset}\n" );
    printf_color( "#{BG:yellow }Fondo amarillo#{reset}\n" );
    printf_color( "#{BG:blue   }Fondo azul    #{reset}\n" );
    printf_color( "#{BG:purple }Fondo purpura #{reset}\n" );
    printf_color( "#{BG:cyan   }Fondo cyan    #{reset}\n" );
    printf_color( "#{BG:white  }Fondo blanco  #{reset}\n" );

    print_aligned("aaaa", 20, ALIGN_CENTER);printf("\n");
    print_aligned("aaaa", 20, ALIGN_RIGHT);printf("\n");
    print_aligned("aaaa", 20, ALIGN_LEFT);printf("\n");

    printf_color("#{ALIGN:30:L}Hola mundo\n");
    printf_color("#{ALIGN:30:R}Hola mundo\n");

    int arr[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf_color("|#{ALIGN:20:C}%d", arr[i][j]);
        }
        printf("|\n");
    }





    CONSOLE_COLOR_RESET;
    printf_color( "fondo por defecto\n");

    /* or foreground_color_custom(255, 0, 255); */
    background_color_custom_(RGB_CREATE(255, 0, 255));

    /* or foreground_color_custom_(RGB_CREATE(0, 255, 255)); */
    foreground_color_custom(0, 255, 255);
    printf_color( "color custom#{reset}\n" );

    printf_color( "#{BG:green}#{FG:red  }Hola : %d, %c#{reset}\n", 1, 'c'  );
    printf_color( "#{BG:blue }#{FG:green}Adios: %d, %f#{reset}\n", 2, 1.2f );

    RGB_C my_px = RGB_CREATE(20, 30, 40);
    printf_color("r:%d, g:%d, b:%d#{reset}\n", my_px.red, my_px.green, my_px.blue);

    foreground_color_custom_( my_px );
    background_color_custom_( RGB_CREATE(225, 30, 40) );
    printf_color( "hola#{reset}\n" );

    back_fore_color_custom(40, 30, 225, 70, 120, 20);
    printf_color( "adios#{reset}\n" );

    printf_color( "\n\nEstandar:\t" );
    for (size_t i = 0; i <= COLOR_WHITE; i++){
        setConsoleBackgroundColor(i);
        printf_color(" %.3d ", i );
    }
    CONSOLE_COLOR_RESET;

    printf_color("\nIntense:\t");
    for (size_t i = 0; i <= COLOR_WHITE; i++){
        setConsoleBackgroundColor(i + HIGH_INTENSTY_BACKGROUNG);
        printf_color(" %.3d ", i );
    }
    CONSOLE_COLOR_RESET;

    #define LOOP_TABLE(max, init, end) \
        for (size_t r = 0; r <= max; r+=36) { \
            for (size_t g = init; g <= end && r+g <= max; g++) { \
                printf_color(BACKGROUND_COLOR_CUSTOM("%d")" %.3d ",r+g, r+g); \
            } \
            CONSOLE_COLOR_RESET; \
            puts(""); \
        }

    puts("\n");

    LOOP_TABLE(201, 16, 21)
    puts("");

    LOOP_TABLE(207, 22, 27)
    puts("");

    LOOP_TABLE(213, 28, 33)
    puts("");

    LOOP_TABLE(219, 34, 39)
    puts("");

    LOOP_TABLE(225, 40, 45)
    puts("");

    LOOP_TABLE(231, 46, 51)
    puts("");

    for (size_t r = 0; r < 255; r++) { \
        if (r % 6 == 0) {
            CONSOLE_COLOR_RESET;
            puts("");
        }
        printf_color(BACKGROUND_COLOR_CUSTOM("%d")" %.3d ",r, r);
    }

    CONSOLE_COLOR_RESET;
    puts("\n");

    uint32_t    fg_r, fg_g, fg_b,
                bg_r, bg_g, bg_b;

    int32_t values[] = {
            12, 19,  5,
            9,  3, 16
        };

    int32_t values_length = sizeof(values) / sizeof(values[0]);
    char str[] = "Hola mundo";

    for (size_t i=0;i< strlen(str); i++){
        generate_three_values(
            str[i],
            &fg_r, &fg_g, &fg_b,
            values[0], values[1], values[2], values[3], values[4], values[5]);

        // se puede usar este metodo, pero no se puede controlar de la mejor manera los valores
        // que genere el metodo
        //shuffle_array( values, values_length );

        generate_three_values(
            str[i] % 64,
            &bg_r, &bg_g, &bg_b,
            values[0], values[1], values[2], values[3], values[4], values[5]);

        printf_color("#{FG:%d;%d;%d}#{BG:%d;%d;%d} %c #{reset}", fg_r, fg_g, fg_b, bg_r, bg_g, bg_b, str[i]);
    }

    puts("");

    /* identificador invalido */
    printf_color("#{i32%d}\n", 0xf0f0f0f0);

    /* 0xf0f0f0f0: 0b11110000111100001111000011110000 */
    printf_color("0x%x: #{i32:%d}\n", 0xf0f0f0f0, 0xf0f0f0f0);

    #if defined(_WIN32) && defined(_MSC_VER)
        _RESET_COLOR__();
    #endif
}
