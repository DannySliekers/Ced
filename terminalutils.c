#include <stdio.h>
#include "terminalutils.h"

void clear_screen() {
    // \033[H will position the cursor to the home position 
    // and \033[J stands for erase lines below.
    printf("\033[H\033[J");
}