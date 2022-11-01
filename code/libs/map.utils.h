void get_maps_by_max_player(Board *board);


char **_copy_body(Map *src) {
    char **body = malloc(sizeof(char *) * src->rows);

    for (int i = 0; i < src->rows; ++i) {
        body[i] = malloc(sizeof(char) * src->columns);
    }

    for (int i = 0; i < src->rows; ++i) {
        for (int j = 0; j < src->columns; ++j) {
            body[i][j] = src->body[i][j];
        }
    }
    return body;
}

void copy_maps(Board *board) {
//    free(board->maps[0]->body);
    free(board->maps);

    board->maps = malloc(sizeof(Map) * board->nb_selected_map);

    for (int i = 0; i < board->nb_selected_map; ++i) {
        unsigned short select_maps = board->selected_maps[i];
        board->maps[i] = malloc(sizeof(Map));

//        board->maps[i]->id = board->default_maps[select_maps]->id;
        board->maps[i]->rows = board->default_maps[select_maps]->rows;
        board->maps[i]->columns = board->default_maps[select_maps]->columns;
        board->maps[i]->bomb_default = board->default_maps[select_maps]->bomb_default;
        board->maps[i]->player_max = board->default_maps[select_maps]->player_max;
        board->maps[i]->body = _copy_body(board->default_maps[select_maps]);
    }
}

void get_maps_by_max_player(Board *board) {
    unsigned short maps_index[board->nb_map];
    board->nb_selected_map = 0;

    for (int i = 0; i < board->nb_map; i++) {
        if(board->nb_player == 1 && board->default_maps[i]->player_max >= 2) {
            maps_index[board->nb_selected_map++] = i;
        } else if(board->default_maps[i]->player_max >= board->nb_player) {
            maps_index[board->nb_selected_map++] = i;
        }
    }
    if(board->nb_selected_map == 0) {
        errorf("0 maps_index");
        return;
    }

    board->selected_maps = malloc(sizeof(short) * board->nb_selected_map);
    for (int i = 0; i < board->nb_selected_map; ++i) {
        board->selected_maps[i] = maps_index[i];
    }
}


void set_next_map(Board *board) {
    board->current_map = board->current_map + 1 > board->nb_selected_map ? 0 : board->current_map + 1;
}

void init_map(Board *board) {
    for (int i = 0; i < board->nb_player; ++i) {
        for (int j = 0; j < board->maps[board->current_map]->rows; ++j) {
            for (int k = 0; k < board->maps[board->current_map]->columns; ++k) {
                if(board->maps[board->current_map]->body[j][k] == 'p') {
                    board->maps[board->current_map]->body[j][k] = board->players[i]->id;
                    i += 1;
                }
            }
        }
    }
}