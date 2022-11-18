Coord *is_bomb_on_player(Board *board);

int plant_bomb(Board *board);
void init_bomb(int x, int y, Board *board);

void decrement_bomb(Board *board);
void explose_bombs(Board *board);

void remove_bomb(Bomb *bomb, Board *board);
void explosion(Bomb *bomb, Board *board);
void init_bomb_destroy(Board *board);
void init_bomb_kick(Board *board);
void players_are_dead(Board *board);


/**
 * @features : planter une bombe + verifier si explosion des bombes
 * */
int plant_bomb(Board *board){
    Player *player = board->players[board->player_turn];
    Map *map = board->maps[board->current_map];
    if(player->nb_bomb == 0){
//        infof("Vous n'avez plus de bombe en stock !!!");
//        pause();
        return 0;
    }
    switch (player->bomb_type) {
        case item_bomb_kick:
            init_bomb_kick(board);
            break;
        case item_bomb_destroy:
            init_bomb_destroy(board);
            init_bomb(player->x, player->y, board);
            map->body[player->x][player->y] = board->items[player->bomb_type]->data->_char;
            player->bomb_type = item_bomb_kick;
            break;
        default:
            map->body[player->x][player->y] = board->items[player->bomb_type]->data->_char;
            init_bomb(player->x, player->y, board);
            break;
    }
    player->nb_bomb -= 1;
    return 1;
}



/**
 * @features : initialisation d'une bombe
 * */
void init_bomb(int x, int y, Board *board){
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    Item *item = board->items[player->bomb_type];
    map->nb_bomb += 1;
    int nb_bomb = map->nb_bomb;

    map->bombs = realloc(map->bombs, sizeof(Bomb *) * nb_bomb);
    map->bombs[nb_bomb - 1] = malloc(sizeof(Bomb));
    map->bombs[nb_bomb - 1]->data = malloc(sizeof(Data_item));

    map->bombs[nb_bomb - 1]->player_id = player->id;
    map->bombs[nb_bomb - 1]->range = player->bomb_range;
    map->bombs[nb_bomb - 1]->nb_turn = 4;
    map->bombs[nb_bomb - 1]->data->_char = item->data->_char;
    map->bombs[nb_bomb - 1]->data->_int = item->data->_int;
    map->bombs[nb_bomb - 1]->x = x;
    map->bombs[nb_bomb - 1]->y = y;
}


/**
 * @features : decremente tout le nb de tour de 1 pour chaque bombe
 * */
void decrement_bomb(Board *board){
    int player_turn = (int)board->player_turn - 1 < 0 ? board->nb_player - 1 : board->player_turn - 1;
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->player_id == board->players[player_turn]->id){
            board->maps[board->current_map]->bombs[i]->nb_turn -= 1;
        }
    }
}



Bomb *get_bomb_at(int x, int y, Board *board) {
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; ++i) {
        if(board->maps[board->current_map]->bombs[i]->x == x && board->maps[board->current_map]->bombs[i]->y == y) {
            return board->maps[board->current_map]->bombs[i];
        }
    }
    return NULL;
}

void init_bomb_kick(Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    int all_items[] = {item_indestructible_wall,
                       item_destructible_wall,
                       item_bomb_up,
                       item_bomb_down,
                       item_yellow_flame,
                       item_blue_flame,
                       item_red_flame,
                       item_bomb,
                       item_bomb_destroy,
                       item_bomb_kick,
                       item_bomb_passes,
                       item_bomb_push,
                       item_invincibility,
                       item_heart,
                       item_life,
    };

    int i = 1;
    switch (player->direction) {
        case 0:
            while (1) {
                for (int j = 0; j < 15; ++j) {
                    if(!is_in_map(player->x - i, player->y, map)) {
                        init_bomb(player->x - i, player->y, board);
                        map->body[player->x - i + 1][player->y] = board->items[player->bomb_type]->data->_char;
                        return;
                    }
                    if(map->body[player->x - i][player->y] == board->items[all_items[j]]->data->_char) {
                        map->body[player->x - i + 1][player->y] = board->items[player->bomb_type]->data->_char;
                        init_bomb(player->x - i + 1, player->y, board);
                        return;
                    }
                }
                i++;
            }
        case 1:
            while (1) {
                for (int j = 0; j < 15; ++j) {
                    if(!is_in_map(player->x, player->y + i, map)) {
                        init_bomb(player->x, player->y + i - 1, board);
                        map->body[player->x][player->y + i - 1] = board->items[player->bomb_type]->data->_char;
                        return;
                    }
                    if(map->body[player->x][player->y + i] == board->items[all_items[j]]->data->_char) {
                        map->body[player->x][player->y + i - 1] = board->items[player->bomb_type]->data->_char;
                        init_bomb(player->x, player->y + i - 1, board);
                        return;
                    }
                }
                i++;
            }
        case 2:
            while (1) {
                for (int j = 0; j < 15; ++j) {
                    if(!is_in_map(player->x + i, player->y, map)) {
                        init_bomb(player->x + i - 1, player->y, board);
                        map->body[player->x + i - 1][player->y] = board->items[player->bomb_type]->data->_char;
                        return;
                    }
                    if(map->body[player->x + i][player->y] == board->items[all_items[j]]->data->_char) {
                        map->body[player->x + i - 1][player->y] = board->items[player->bomb_type]->data->_char;
                        init_bomb(player->x + i - 1, player->y, board);
                        return;
                    }
                }
                i++;
            }
        case 3:
            while (1) {
                for (int j = 0; j < 15; ++j) {
                    if(!is_in_map(player->x, player->y - i, map)) {
                        init_bomb(player->x, player->y - i, board);
                        map->body[player->x][player->y - i + 1] = board->items[player->bomb_type]->data->_char;
                        return;
                    }
                    if(map->body[player->x][player->y - i] == board->items[all_items[j]]->data->_char) {
                        map->body[player->x][player->y - i + 1] = board->items[player->bomb_type]->data->_char;
                        init_bomb(player->x, player->y - i + 1, board);
                        return;
                    }
                }
                i++;
            }
        default:
            break;
    }
}

void init_bomb_destroy(Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];

    int i = 0;
    while (map->body[i][player->y] == board->items[item_indestructible_wall]->data->_char) {
        map->body[i++][player->y] = ' ';
    }

    int y = 1;
    while (map->body[map->rows - y][player->y] == board->items[item_indestructible_wall]->data->_char) {
        map->body[map->rows - y++][player->y] = ' ';
    }

    i = 0;
    while (map->body[player->x][i] == board->items[item_indestructible_wall]->data->_char) {
        map->body[player->x][i++] = ' ';
    }

    y = 1;
    while (map->body[player->x][map->columns - y] == board->items[item_indestructible_wall]->data->_char) {
        map->body[player->x][map->columns - y++] = ' ';
    }
}

/**
 * @features : boucle pour exploser une bombe normal
 * */
void explosion(Bomb *bomb, Board *board){
    if(bomb == NULL) {
        return;
    }

    Map *map = board->maps[board->current_map];
    char item_dest_wall = board->items[item_destructible_wall]->data->_char;
    int player_turn = (int)board->player_turn - 1 < 0 ? board->nb_player - 1 : board->player_turn - 1;
    int all_items[] = {item_bomb_up,
                       item_bomb_down,
                       item_yellow_flame,
                       item_blue_flame,
                       item_red_flame,
                       item_bomb,
                       item_bomb_destroy,
                       item_bomb_kick,
                       item_bomb_passes,
                       item_bomb_push,
                       item_invincibility,
                       item_heart,
                       item_life,
    };

    //remove bomb
    map->body[bomb->x][bomb->y] = ' ';
    //add +1 bomb
    for (int i = 0; i < board->nb_player; ++i) {
        if(bomb->player_id == board->players[i]->id) {
            board->players[i]->nb_bomb += 1;
            break;
        }
    }
    
    //is bomb on player
    for (int i = 0; i < map->nb_bomb; ++i) {
        if(map->bombs[i]->x == board->players[player_turn]->x && map->bombs[i]->y == board->players[player_turn]->y) {
            board->players[player_turn]->heart -= 1;
            break;
        }
    }

    //droite
    for (int i = 1; i <= bomb->range; ++i) {
        if(bomb->y + i < map->columns) {
            int can_explose = 1;
            //vérif joueur
            for (int j = 0; j < board->nb_player; ++j) {
                if(map->body[bomb->x][bomb->y + i] == board->players[j]->id) {
                    board->players[j]->heart -= 1;
                }
            }
            //s'arrete si mur destructible
            if(map->body[bomb->x][bomb->y + i] == item_dest_wall) {
                map->body[bomb->x][bomb->y + i] = ' ';
                put_item(board, bomb->x, bomb->y + i);
                break;
            }
            //ne fait rien si il y a un item
            for (int j = 0; j < 13; ++j) {
                char _char = map->body[bomb->x][bomb->y + i];
                if(_char == board->items[item_bomb]->data->_char ||
                   _char == board->items[item_bomb_destroy]->data->_char ||
                   _char == board->items[item_bomb_kick]->data->_char) {
                    Bomb *next_bomb = get_bomb_at(bomb->x, bomb->y + i, board);
                    explosion(next_bomb, board);
                    remove_bomb(next_bomb, board);
                }
                if(map->body[bomb->x][bomb->y + i] == board->items[all_items[j]]->data->_char) {
                    can_explose = 0;
                }
            }
            //explosion
            if(can_explose && map->body[bomb->x][bomb->y + i] != board->items[item_indestructible_wall]->data->_char) {
                map->body[bomb->x][bomb->y + i] = ' ';
            }
        }
    }
    //gauche
    for (int i = 1; i <= bomb->range; ++i) {
        if((int) bomb->y - i >= 0) {
            int can_explose = 1;
            //vérif joueur
            for (int j = 0; j < board->nb_player; ++j) {
                if(map->body[bomb->x][bomb->y - i] == board->players[j]->id) {
                    board->players[j]->heart -= 1;
                }
            }
            //s'arrete si mur destructible
            if(map->body[bomb->x][bomb->y - i] == item_dest_wall) {
                map->body[bomb->x][bomb->y - i] = ' ';
                put_item(board, bomb->x, bomb->y - i);
                break;
            }
            for (int j = 0; j < 13; ++j) {
                char _char = map->body[bomb->x][bomb->y - i];
                if(_char == board->items[item_bomb]->data->_char ||
                   _char == board->items[item_bomb_destroy]->data->_char ||
                   _char == board->items[item_bomb_kick]->data->_char) {
                    Bomb *next_bomb = get_bomb_at(bomb->x, bomb->y - i, board);
                    explosion(next_bomb, board);
                    remove_bomb(next_bomb, board);
                }
                if(map->body[bomb->x][bomb->y - i] == board->items[all_items[j]]->data->_char) {
                    can_explose = 0;
                }
            }
            if(can_explose && map->body[bomb->x][bomb->y - i] != board->items[item_indestructible_wall]->data->_char) {
                map->body[bomb->x][bomb->y - i] = ' ';
            }
        }
    }
    //top
    for (int i = 1; i <= bomb->range; ++i) {
        if((int)bomb->x - i >= 0) {
            int can_explose = 1;
            //vérif joueur
            for (int j = 0; j < board->nb_player; ++j) {
                if(map->body[bomb->x - i][bomb->y] == board->players[j]->id) {
                    board->players[j]->heart -= 1;
                }
            }
            //s'arrete si mur destructible
            if(map->body[bomb->x - i][bomb->y] == item_dest_wall) {
                map->body[bomb->x - i][bomb->y] = ' ';
                put_item(board, bomb->x - i, bomb->y);
                break;
            }
            for (int j = 0; j < 13; ++j) {
                char _char = map->body[bomb->x - i][bomb->y];
                if(_char == board->items[item_bomb]->data->_char ||
                   _char == board->items[item_bomb_destroy]->data->_char ||
                   _char == board->items[item_bomb_kick]->data->_char) {
                    Bomb *next_bomb = get_bomb_at(bomb->x - i, bomb->y, board);
                    explosion(next_bomb, board);
                    remove_bomb(next_bomb, board);
                }
                if(map->body[bomb->x - i][bomb->y] == board->items[all_items[j]]->data->_char) {
                    can_explose = 0;
                }
            }
            if(can_explose && map->body[bomb->x - i][bomb->y] != board->items[item_indestructible_wall]->data->_char) {
                map->body[bomb->x - i][bomb->y] = ' ';
            }
        }
    }
    //bottom
    for (int i = 1; i <= bomb->range; ++i) {
        if((int) bomb->x + i < map->rows) {
            int can_explose = 1;
            //vérif joueur
            for (int j = 0; j < board->nb_player; ++j) {
                if(map->body[bomb->x + i][bomb->y] == board->players[j]->id) {
                    board->players[j]->heart -= 1;
                }
            }
            //s'arrete si mur destructible
            if(map->body[bomb->x + i][bomb->y] == item_dest_wall) {
                map->body[bomb->x + i][bomb->y] = ' ';
                put_item(board, bomb->x + i, bomb->y);
                break;
            }
            for (int j = 0; j < 13; ++j) {
                char _char = map->body[bomb->x + i][bomb->y];
                if(_char == board->items[item_bomb]->data->_char ||
                   _char == board->items[item_bomb_destroy]->data->_char ||
                   _char == board->items[item_bomb_kick]->data->_char) {
                    Bomb *next_bomb = get_bomb_at(bomb->x + i, bomb->y, board);
                    explosion(next_bomb, board);
                    remove_bomb(next_bomb, board);
                }
                if(map->body[bomb->x + i][bomb->y] == board->items[all_items[j]]->data->_char) {
                    can_explose = 0;
                }
            }
            if(can_explose && map->body[bomb->x + i][bomb->y] != board->items[item_indestructible_wall]->data->_char) {
                map->body[bomb->x + i][bomb->y] = ' ';
            }
        }
    }
}


/**
 * @features : verifie dans le tab de bombe si une bombe doit exploser
 * */
void explose_bombs(Board *board){
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->nb_turn <= 0){
            explosion(board->maps[board->current_map]->bombs[i], board);
            remove_bomb(board->maps[board->current_map]->bombs[i], board);
            if(board->player_turn == board->nb_player || board->player_turn + 1 == board->nb_player) {
                board->player_turn = 0;
            }
        }
    }
}



/**
 * @features : suppression d'une bombe dans le tableau de bombe
 * */
void remove_bomb(Bomb *bomb, Board *board) {
    if(bomb == NULL) {
        return;
    }

    Map *map = board->maps[board->current_map];
    int index;

    if(map->nb_bomb > 1) {
        for (int i = 0; i < map->nb_bomb; ++i) {
            if(map->bombs[i]->x == bomb->x && map->bombs[i]->y == bomb->y) {
                index = i;
                break;
            }
        }
        for (int i = index; i < map->nb_bomb - 1; ++i) {
            map->bombs[i]->x = map->bombs[i + 1]->x;
            map->bombs[i]->y = map->bombs[i + 1]->y;
            map->bombs[i]->nb_turn = map->bombs[i + 1]->nb_turn;
            map->bombs[i]->range = map->bombs[i + 1]->range;
            map->bombs[i]->player_id = map->bombs[i + 1]->player_id;
            map->bombs[i]->data->_char = map->bombs[i + 1]->data->_char;
            map->bombs[i]->data->_int = map->bombs[i + 1]->data->_int;
        }
    }

    free(map->bombs[map->nb_bomb - 1]->data);
    free(map->bombs[map->nb_bomb - 1]);
    map->nb_bomb -= 1;
    map->bombs = realloc(map->bombs, sizeof(Bomb *) * map->nb_bomb);
}

void remove_player(Player *player, Board *board) {
    int index;

    if(board->nb_player > 1) {
        for (int i = 0; i < board->nb_player; ++i) {
            if(player->id == board->players[i]->id) {
                index = i;
                break;
            }
        }

        for (int i = index; i < board->nb_player - 1; ++i) {
            Player *temp = board->players[i];
            board->players[i] = board->players[i + 1];
            board->players[i + 1] = temp;
        }
    }

    board->nb_player -= 1;
}

void players_are_dead(Board *board) {
    for (int i = 0; i < board->nb_player; ++i) {
        if(board->players[i]->heart == 0) {
            //todo send_end_game(board->players[i], board); 
            //todo (à l'interieur : if(board->game_mode == PLAYER_ID_HOST) send_win || send_dead
            remove_player(board->players[i], board);
        }
    }
}
