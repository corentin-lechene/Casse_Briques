#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#include <conio.h>
#include "libs/misc.utils.h"
#include "libs/functions.utils.h"
#include "libs/display.utils.h"
#include "libs/config.utils.h"
#include "libs/map.utils.h"
#include "libs/game.utils.h"


void run_program(Board *board) {
    if(board->selected_menu == IN_GAME) {
        run_game(board);
    } else if(board->selected_menu == IN_PREP_GAME) {
        init_game(board);
        exit(0);
    } else {
        run_menu(board);
    }
}



int main() {
    Board *board = generate_board();

    board->default_maps = malloc(sizeof(Map) * 2);
    board->default_maps[0] = malloc(sizeof(Map));
    board->default_maps[0]->rows = 6;
    board->default_maps[0]->columns = 8;

    board->default_maps[0]->body = malloc(sizeof(char *) * board->default_maps[0]->rows);

    for (int i = 0; i < board->default_maps[0]->rows; ++i) {
        board->default_maps[0]->body[i] = malloc(sizeof(char) * board->default_maps[0]->columns);
    }

    for (int i = 0; i < board->default_maps[0]->rows; ++i) {
        for (int y = 0; y < board->default_maps[0]->columns; ++y) {
            board->default_maps[0]->body[i][y] = test[i][y];
        }
    }

    display_opening_credits();
    while (board->selected_menu >= 1) {
        run_program(board);
    }
    display_ending_credits();
    return 0;
}
