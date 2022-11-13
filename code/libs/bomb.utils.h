int plant_bomb(Board *board);
void init_bomb(int x, int y, Board *board);

void decrement_bomb(Board *board);
void explose_bombs(Board *board);

void remove_bomb(Bomb *bomb, Board *board);
void explosion(Bomb *bomb, Board *board);
void init_bomb_destroy(Board *board);
void init_bomb_kick(Board *board);
int _boom(int x, int y, Board *board);

void is_bomb_around(Board *board, int x, int y);
void recup_position(int x,int y, Board *board);

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
        default:
            map->body[player->x][player->y] = board->items[player->bomb_type]->data->_char;
            init_bomb(player->x, player->y, board);
            break;
    }
    player->nb_bomb -= 1;
    return 1;
}

int find_space(int x, int y, Board *board){
    Map *map = board->maps[board->current_map];
    if(map->body[x][y] != ' ') return 0;
    else {
        return 1;
    }

}

int place_bomb_kick(int x, int y , Board *board) {
    Map *map = board->maps[board->current_map];
    Bomb *bomb = map->bombs[board->maps[board->current_map]->nb_bomb];

    if(map->body[x][y] != 'x' && map->body[x][y] != 'm') return 0;
    else {
        bomb->x =x;
        bomb->y = y;
        return 1;
    }
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
    map->bombs[nb_bomb - 1]->nb_turn = 3;
    map->bombs[nb_bomb - 1]->data->_char = item->data->_char;
    map->bombs[nb_bomb - 1]->data->_int = item->data->_int;
    map->bombs[nb_bomb - 1]->x = x;
    map->bombs[nb_bomb - 1]->y = y;
}


/**
 * @features : decremente tout le nb de tour de 1 pour chaque bombe
 * */
void decrement_bomb(Board *board){
    int player_turn = (int)board->player_turn - 1 < 0 ? board->nb_player : board->player_turn - 1;
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->player_id == board->players[player_turn]->id){
            board->maps[board->current_map]->bombs[i]->nb_turn -= 1;
        }
    }
}



Bomb *_get_bomb_at(int x, int y, Board *board) {
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

    int bomb_planted = 0;
    int i = 1;
    switch (player->direction) {
        case 0:
            while (!bomb_planted) {
                for (int j = 0; j < 15; ++j) {
                    if(map->body[player->x - i][player->y] == board->items[all_items[j]]->data->_char) {
                        map->body[player->x - i + 1][player->y] = board->items[player->bomb_type]->data->_char;
                        bomb_planted = 1;
                        init_bomb(player->x - i + 1, player->y, board);
                        return;
                    }
                }
                i++;
            }
            break;
        case 1:
            while (!bomb_planted) {
                for (int j = 0; j < 15; ++j) {
                    if(map->body[player->x][player->y + i] == board->items[all_items[j]]->data->_char) {
                        map->body[player->x][player->y + i - 1] = board->items[player->bomb_type]->data->_char;
                        bomb_planted = 1;
                        init_bomb(player->x, player->y + i - 1, board);
                        return;
                    }
                }
                i++;
            }
            break;
        case 2:
            while (!bomb_planted) {
                for (int j = 0; j < 15; ++j) {
                    if(map->body[player->x + i][player->y] == board->items[all_items[j]]->data->_char) {
                        map->body[player->x + i - 1][player->y] = board->items[player->bomb_type]->data->_char;
                        bomb_planted = 1;
                        init_bomb(player->x + i - 1, player->y, board);
                        return;
                    }
                }
                i++;
            }
            break;
        case 3:
            while (!bomb_planted) {
                for (int j = 0; j < 15; ++j) {
                    if(map->body[player->x][player->y - i] == board->items[all_items[j]]->data->_char) {
                        map->body[player->x][player->y - i + 1] = board->items[player->bomb_type]->data->_char;
                        bomb_planted = 1;
                        init_bomb(player->x, player->y - i + 1, board);
                        return;
                    }
                }
                i++;
            }
            break;
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

//TODO : verfif si un joueur n'est pas à cote d'une bombe
/**
 * @features : boucle pour exploser une bombe normal
 * */
void explosion(Bomb *bomb, Board *board){
    if(bomb == NULL) {
        return;
    }
    
    Map *map = board->maps[board->current_map];
    char item_dest_wall = board->items[item_destructible_wall]->data->_char;
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
    
    //droite
    for (int i = 1; i <= bomb->range; ++i) {
        if(bomb->y + i < map->columns) {
            int can_explose = 1;
            if(map->body[bomb->x][bomb->y + i] == item_dest_wall) {
                map->body[bomb->x][bomb->y + i] = ' ';
                break;
            }
            for (int j = 0; j < 13; ++j) {
                char _char = map->body[bomb->x][bomb->y + i];
                if(_char == board->items[item_bomb]->data->_char ||
                   _char == board->items[item_bomb_destroy]->data->_char ||
                   _char == board->items[item_bomb_kick]->data->_char) {
                    Bomb *next_bomb = _get_bomb_at(bomb->x, bomb->y + i, board);
                    explosion(next_bomb, board);
                    remove_bomb(next_bomb, board);
                }
                if(map->body[bomb->x][bomb->y + i] == board->items[all_items[j]]->data->_char) {
                    can_explose = 0;
                }
            }
            if(can_explose && map->body[bomb->x][bomb->y + i] != board->items[item_indestructible_wall]->data->_char) {
                map->body[bomb->x][bomb->y + i] = ' ';
            }
        }
    }
    //gauche
    for (int i = 1; i <= bomb->range; ++i) {
        if((int) bomb->y - i >= 0) {
            int can_explose = 1;
            if(map->body[bomb->x][bomb->y - i] == item_dest_wall) {
                map->body[bomb->x][bomb->y - i] = ' ';
                break;
            }
            for (int j = 0; j < 13; ++j) {
                char _char = map->body[bomb->x][bomb->y - i];
                if(_char == board->items[item_bomb]->data->_char || 
                    _char == board->items[item_bomb_destroy]->data->_char || 
                    _char == board->items[item_bomb_kick]->data->_char) {
                    Bomb *next_bomb = _get_bomb_at(bomb->x, bomb->y - i, board);
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
            if(map->body[bomb->x - i][bomb->y] == item_dest_wall) {
                map->body[bomb->x - i][bomb->y] = ' ';
                break;
            }
            for (int j = 0; j < 13; ++j) {
                char _char = map->body[bomb->x - i][bomb->y];
                if(_char == board->items[item_bomb]->data->_char ||
                   _char == board->items[item_bomb_destroy]->data->_char ||
                   _char == board->items[item_bomb_kick]->data->_char) {
                    Bomb *next_bomb = _get_bomb_at(bomb->x - i, bomb->y, board);
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
            if(map->body[bomb->x + i][bomb->y] == item_dest_wall) {
                map->body[bomb->x + i][bomb->y] = ' ';
                break;
            }
            for (int j = 0; j < 13; ++j) {
                char _char = map->body[bomb->x + i][bomb->y];
                if(_char == board->items[item_bomb]->data->_char ||
                   _char == board->items[item_bomb_destroy]->data->_char ||
                   _char == board->items[item_bomb_kick]->data->_char) {
                    Bomb *next_bomb = _get_bomb_at(bomb->x + i, bomb->y, board);
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
    int player_turn = (int)board->player_turn - 1 < 0 ? board->nb_player : board->player_turn - 1;
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->nb_turn <= 0){
            explosion(board->maps[board->current_map]->bombs[i], board);
            remove_bomb(board->maps[board->current_map]->bombs[i], board);
            board->players[player_turn]->nb_bomb += 1;
        }
    }
}



/**
 * @features : suppression d'une bombe dans le tableau de bombe
 * */
void remove_bomb(Bomb *bomb, Board *board) {
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
