#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#include <conio.h>
#include "libs/functions.utils.h"
#include "libs/misc.utils.h"
#include "libs/config.utils.h"
#include "libs/display.utils.h"
#include "libs/map.utils.h"
#include "libs/game.utils.h"


void run_program(Board *board) {
    if(board->selected_menu == IN_GAME) {
        run_game(board);
    } else {
        run_menu(board);
    }
}



int main() {
    //Board *board = generate_board();

    Board *board = malloc(sizeof (Board));
    board->maps = get_maps();
    display_board(board);
    free(board);

    return 0;
}
