
void get_maps_by_max_player(Board *board);

void copy_maps(Board *board);
char **_copy_body(Map *src);

void init_map(Board *board);
void set_next_map(Board *board);

Coord *get_coord_of(char search, int range, int diago, Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    Coord *coord = NULL;

    for (int i = player->x - range; i <= player->x + range; ++i) {
        for (int j = player->y - range; j <= player->y + range; ++j) {
            if(i >= 0 && i <= map->rows && j >= 0 && j <= map->columns) {
//                printf("[%c][%c] -> %d %d\n", map->body[i][j], search, i, j);
                if (map->body[i][j] == search) {
                    if(coord == NULL) {
                        coord = malloc(sizeof(Coord));
                        coord->x = i;
                        coord->y = j;
                        coord->distance = sqrt( pow(player->x - i, 2) + pow(player->y - j, 2) );
                        printf("joueur: %d %d, coord: %d %d %lf\n", player->x, player->y, i, j, coord->distance);
                        continue;
                    }
                    
                    double distance = sqrt( pow(player->x - i, 2) + pow(player->y - j, 2) );
                    if(!diago) {
                        distance = (int) distance + 1;
                    }
                    if((int) distance < coord->distance) {
                        coord->x = i;
                        coord->y = j;
                        coord->distance = distance;
                    }

                    printf("joueur: %d %d, coord: %d %d %lf\n", player->x, player->y, i, j, (int )distance );
                }
            }
        }
    }
//    pause();
    return coord;
}
//coord->distance = i;
//coord->x = player->x + i;
//coord->y = player->y;




/* ----------------------------------- */

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

void copy_maps(Board *board) {
//    free(board->maps[0]->body);

    board->maps = malloc(sizeof(Map *) * board->nb_selected_map);

    for (int i = 0; i < board->nb_selected_map; ++i) {
        unsigned short select_maps = board->selected_maps[i];
        board->maps[i] = malloc(sizeof(Map));

//        board->maps[i]->id = board->default_maps[select_maps]->id;
        board->maps[i]->rows = board->default_maps[select_maps]->rows;
        board->maps[i]->columns = board->default_maps[select_maps]->columns;
        board->maps[i]->bomb_default = board->default_maps[select_maps]->bomb_default;
        board->maps[i]->player_max = board->default_maps[select_maps]->player_max;
        board->maps[i]->body = _copy_body(board->default_maps[select_maps]);
        board->maps[i]->bombs = malloc(sizeof(Bomb *));
        board->maps[i]->nb_bomb = 1;
        for (int j = 0; j < board->maps[i]->nb_bomb; ++j) {
            board->maps[i]->bombs[j] = malloc(sizeof(Bomb));
            board->maps[i]->bombs[j]->data = malloc(sizeof(Data_item));
        }
    }
}
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

void init_map(Board *board) {
    for (int i = 0; i < board->nb_player; ++i) {
        for (int j = 0; j < board->maps[board->current_map]->rows; ++j) {
            for (int k = 0; k < board->maps[board->current_map]->columns; ++k) {
                if(board->maps[board->current_map]->body[j][k] == 'p') {
                    if(i > board->nb_player) {
                        break;
                    }
                    board->maps[board->current_map]->body[j][k] = board->players[i]->id;
                    i += 1;
                }
            }
        }
    }
}
void set_next_map(Board *board) {
    board->current_map = board->current_map + 1 > board->nb_selected_map ? 0 : board->current_map + 1;
}

Coord *is_bomb_on_player(Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];

    for (int i = 0; i < map->nb_bomb; ++i) {
        if(player->x == map->bombs[i]->x && player->y == map->bombs[i]->y) {
            Coord *coord = malloc(sizeof(Coord));
            coord->x = player->x;
            coord->y = player->y;
            coord->distance = 0;
            return coord;
        }
    }
    return NULL;
}


Coord *get_proximity_bombs(Board *board) {
    Player *player = board->players[board->player_turn];
    Coord *coord;
    int bombs[] = {item_bomb, item_bomb_kick, item_bomb_destroy};

    coord = is_bomb_on_player(board);
    if(coord != NULL) {
        return coord;
    }

    for (int i = 0; i < 3; ++i) {
        coord = get_coord_of(board->items[bombs[i]]->data->_char, player->bomb_range, 0, board);
        if(coord != NULL) {
            return coord;
        }
    }
    printf("jsute avant null");
    return NULL;
}
Coord *get_proximity_players(Board *board) {
    Coord *coord;
    for (int i = 0; i < board->nb_player; ++i) {
        if(board->players[i]->id != board->players[board->player_turn]->id) {
            coord = get_coord_of(board->players[i]->id, board->players[board->player_turn]->bomb_range, 1, board);
            if(coord != NULL) {
                return coord;
            }
        }
    }
    return NULL;
}
Coord *get_proximity_items(Board *board) {
    Player *player = board->players[board->player_turn];
    Coord *coord;
    int items[] = {item_bomb_up,
                   item_yellow_flame,
                   item_red_flame,
                   item_bomb_passes,
                   item_bomb_kick,
                   item_bomb_push,
                   item_invincibility,
                   item_heart,
                   item_life
    };
    
    for (int i = 0; i < 9; ++i) {
        coord = get_coord_of(board->items[items[i]]->data->_char, player->bomb_range + 1, 0, board);
        if(coord != NULL) {
            return coord;
        }
    }
    return NULL;
}
Coord *get_proximity_walls_desc(Board *board) {
    return get_coord_of('m', board->players[board->player_turn]->bomb_range, 1, board);
}

int is_close_to(char *search, Board *board) {
    printf("is_close_to: %s ? ->", search);
//    pause();
    if(strcmp(search, "bombs") == 0) {
        printf("is_close_to: %s\n", search);
        return get_proximity_bombs(board) != NULL;
    } else if(strcmp(search, "players") == 0) {
        printf("is_close_to: %s\n", search);
        return get_proximity_players(board) != NULL;
    } else if(strcmp(search, "items") == 0) {
        printf("is_close_to: %s\n", search);
        return get_proximity_items(board) != NULL;
    } else if(strcmp(search, "walls") == 0) {
        printf("is_close_to: %s\n", search);
        return get_proximity_walls_desc(board) != NULL;
    }
}


