#if !defined(__COLORS__)
#define __COLORS__

#include <stdio.h>

typedef struct _color
{
    const char *BLACK;  //"\033[30m"
    const char *RED;    //"\033[31m"
    const char *GREEN;  //"\033[32m"
    const char *YELLOW; //"\033[33m"
    const char *BLUE;   //"\033[34m"
    const char *MAGENTA;//"\033[35m"
    const char *CYAN;   //"\033[36m"
    const char *WHITE;  //"\033[37m"
    const char *RESET;  //"\033[38m"

    const char *LIGHTBLACK_EX;  //"\033[90m"
    const char *LIGHTRED_EX;    //"\033[91m"
    const char *LIGHTGREEN_EX;  //"\033[92m"
    const char *LIGHTYELLOW_EX; //"\033[93m"
    const char *LIGHTBLUE_EX;   //"\033[94m"
    const char *LIGHTMAGENTA_EX;//"\033[95m"
    const char *LIGHTCYAN_EX;   //"\033[96m"
    const char *LIGHTWHITE_EX;  //"\033[97m"

    void (*UP)(const char *, int);
    void (*DOWN)(const char *, int);
    void (*FORWARD)(const char *, int);
    void (*BACK)(const char *, int);
    void (*POS)(const char *, int, int);
    void (*SET_TITLE)(const char *);
    void (*CLEAR)(void);

} _color;

void _UP(const char *data, int number)
{
    printf("\033[%dA%s", number, data);
}
void _DOWN(const char *data, int number)
{
    printf("\033[%dB%s", number, data);
}
void _FORWARD(const char *data, int number)
{
    printf("\033[%dC%s", number, data);
}
void _BACK(const char *data, int number)
{
    printf("\033[%dD%s", number, data);
}
void _POS(const char *data, int number1, int number2)
{
    printf("\033[%d;%dH%s", number1, number2, data);
}
void _SET_TITLE(const char *title)
{
    printf("\033]2;%s\007", title);
}
void _CLEAR(void)
{
    printf("\033[3J\033[H\033[2J");
}
void POINTGREEN(const char *data, _color color)
{
    printf("%s[%s*%s]%s %s", color.LIGHTGREEN_EX, color.BLUE, color.LIGHTGREEN_EX, color.LIGHTWHITE_EX, data, color.RESET);
}
void POINTRED(const char *data, _color color)
{
    printf("%s[%s*%s]%s %s", color.LIGHTYELLOW_EX, color.RED, color.LIGHTYELLOW_EX, color.LIGHTMAGENTA_EX, data, color.RESET);
}

const _color color = {
    "\033[30m",
    "\033[31m",
    "\033[32m",
    "\033[33m",
    "\033[34m",
    "\033[35m",
    "\033[36m",
    "\033[37m",
    "\033[37m\033[38m",

    "\033[90m",
    "\033[91m",
    "\033[92m",
    "\033[93m",
    "\033[94m",
    "\033[95m",
    "\033[96m",
    "\033[97m",

    _UP,
    _DOWN,
    _FORWARD,
    _BACK,
    _POS,
    _SET_TITLE,
    _CLEAR,

};

#endif
