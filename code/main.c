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

Map *new_map(char *body[], int rows, int columns, int player_max, int bomb_max) {
    Map *map = malloc(sizeof(Map));

    map->rows = rows;
    map->columns = columns;
    map->player_max = player_max;
    map->bomb_max = bomb_max;

    map->body = malloc(sizeof(char *) * map->rows);
    for (int i = 0; i < map->rows; ++i) {
        map->body[i] = malloc(sizeof(char) * map->columns);
    }

    for (int i = 0; i < map->rows; ++i) {
        for (int y = 0; y < map->columns; ++y) {
            map->body[i][y] = body[i][y];
        }
    }

    return map;
}

Map **get_maps(Board *board) {
    board->nb_map = 1;
    Map **maps = malloc(sizeof(Map) * board->nb_map);

    maps[0] = new_map(MAP, 5, 5, 2, 10);
    return maps;
}

int main() {
    Board *board = malloc(sizeof(Board));
    board->config = malloc(sizeof(Config));

    board->config->language = malloc(sizeof(char) * 3);
    board->config->language = "FR";

    board = generate_board(board->config);

    board->maps = get_maps(board);



    display_board(board);


    printf("[%d]\n", board->maps[0]->rows);

    //Fin Free
    for (int i = 0; i < board->maps[0]->columns; ++i) {
        free(board->maps[0]->body[i]);
    }
    free(board->maps[0]->body);
    free(board->maps);
    free(board->config);
    free(board->lang);
    free(board->winner);
    free(board->players_turn);
    return 0;
}
