#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
//#include <conio.h>
#include "libs/functions.utils.h"
#include "libs/misc.utils.h"
#include "libs/config.utils.h"
#include "libs/display.utils.h"
#include "libs/game.utils.h"


void run_program(Board *board) {
    if(board->selected_menu == IN_GAME) {
        run_game(board);
    } else {
        run_menu(board);
    }
}



int main() {
    Board *board = generate_board();

    board->selected_maps = malloc(sizeof(Map) * 2);
    board->selected_maps[0] = malloc(sizeof(Map));
    board->selected_maps[0]->rows = 12;
    board->selected_maps[0]->columns = 20;

    board->selected_maps[0]->body = malloc(sizeof(char *) * board->selected_maps[0]->rows);

    for (int i = 0; i < board->selected_maps[0]->rows; ++i) {
        board->selected_maps[0]->body[i] = malloc(sizeof(char) * board->selected_maps[0]->columns);
    }

    for (int i = 0; i < board->selected_maps[0]->rows; ++i) {
        for (int y = 0; y < board->selected_maps[0]->columns; ++y) {
            board->selected_maps[0]->body[i][y] = test3[i][y];
        }
    }


    display_opening_credits();
    while (board->selected_menu >= 1) {
        run_program(board);
    }
    display_ending_credits();
    return 0;
}
