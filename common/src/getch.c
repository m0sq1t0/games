#include <stdio.h>
#include "getch.h"

static struct termios cooked;
static struct termios raw;

int getch(void)
{
    int c;
    tcgetattr(STDIN_FILENO, &cooked);
    raw = cooked;
    cfmakeraw(&raw);

    tcsetattr(STDIN_FILENO, 0, &raw); // 端末をrawモードにセット
    c = getchar();
    tcsetattr(STDIN_FILENO, 0, &cooked); // 端末をcookedモードにセット
    return c;
}
