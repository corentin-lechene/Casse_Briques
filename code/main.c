#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "libs/game.utils.h"
#include "libs/display.utils.h"
#include "libs/misc.utils.h"
#include "libs/config.utils.h"
#include <stdarg.h>


Board *generate_board(Config *config) {
    Board *board = malloc(sizeof(Board));

    board->config = config;
    board->lang = get_lang(config->language);
    board->winner = malloc(sizeof(Player));
    board->players_turn = malloc(sizeof(Player));

    board->bo = 3;
    board->selected_choice = 0;
    board->selected_map = 0;

    return board;
}

void copy_map(Board *board, char **map) {

}

int main() {
    Board *board = malloc(sizeof(Board));
    board->config = malloc(sizeof(Config));

    board->config->language = malloc(sizeof(char) * 3);
    board->config->language = "FR";

    board = generate_board(board->config);

    //program
    board->nb_map = 2;
    board->map = malloc(sizeof(Map *) * board->nb_map);

    for (int i = 0; i < board->nb_map; ++i) {
        board->map[i] = malloc(sizeof(Map));
    }

    board->map[0]->rows = 5;
    board->map[0]->columns = 5;

    board->map[0]->body = malloc(sizeof(char *) * board->map[0]->rows);

    for (int i = 0; i < board->map[0]->columns; ++i) {
        board->map[0]->body[i] = malloc(sizeof(char) * board->map[0]->columns);
    }


    for (int i = 0; i < board->map[0]->rows; ++i) {
        for (int j = 0; j < board->map[0]->columns; ++j) {
            board->map[0]->body[i][j] = MAP[i][j];
        }
    }

    display_board(board);


    printf("[%d]", board->map[0]->rows);


    printf("\n");


    //fin

//    for (int i = 0; i < board->map[0]->columns; ++i) {
//        free(board->map[0]->body[i]);
//    }
//    free(board->map[0]->body);
    free(board->map[0]);
    free(board->map[1]);
    free(board->config);
    free(board->lang);
    free(board->winner);
    free(board->players_turn);
    return 0;
}
