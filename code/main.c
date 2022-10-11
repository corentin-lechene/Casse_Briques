#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "libs/game.utils.h"
#include "libs/display.utils.h"
#include "libs/misc.utils.h"
#include "libs/config.utils.h"


Board *generate_board(Config *config) {
    Board *board = malloc(sizeof(Board));

    board->config = config;
    board->lang = get_lang(config->language);
    board->winner = malloc(sizeof(Player));
    board->players_turn = malloc(sizeof(Player));

    board->bo = 3;
    board->cursor = 0;
    board->selected_map = 0;

    return board;
}

int main() {
    Board *board = malloc(sizeof(Board));
    board->config = malloc(sizeof(Config));

    board->config->language = malloc(sizeof(char) * 3);
    board->config->language = "FR";

    board = generate_board(board->config);

    //program
    board->map = malloc(sizeof(Board) * 1);

    /*
    board->map[0]->body = malloc(sizeof(char [5][10]));
    board->map[0]->rows = 5;
    board->map[0]->columns = 10;
     */

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("[%c]", MAP[i][j]);
        }
        printf("\n");
    }


    printf("%s", board->map[0]->body[0]);

    //fin
    free(board->config);
    free(board->lang);
    free(board->winner);
    free(board->players_turn);
    return 0;
}
