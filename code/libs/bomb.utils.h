int plant_bomb(Board *board);
void init_bomb(Board *board);
void decrement_bomb(Board *board);
void is_explosed(Board *board);
void is_bomb_arround(int index,Board *board, int x,int y);
void recup_position(int x,int y, Board *board);
void remove_bomb(int index, Board *board);
void explosion(int index, Board *board);
int boom(int x, int y, Map *map);

int plant_bomb(Board *board){
    if(board->players[board->player_turn]->nb_bomb == 0){
        infof("Vous n'avez plus de bombe en stock !!!");
        pause();
        return 0;
    }
    init_bomb(board);
    if(board->maps[board->current_map]->nb_bomb > 0){
        decrement_bomb(board);
        is_explosed(board);
    }
}

void init_bomb(Board *board){
    Player *player = board->players[board->player_turn];
    Map *map = board->maps[board->current_map];
    int nb_bomb = map->nb_bomb;
    board->maps[board->current_map]->bombs[nb_bomb] = malloc(sizeof (Bomb));
    Bomb *bomb = map->bombs[board->maps[board->current_map]->nb_bomb];
    bomb->nb_turn = 4;
    bomb->x = player->x;
    bomb->y = player->y;
    bomb->range = player->bomb_range;
    bomb->player_id = board->players[board->player_turn]->id;
    board->maps[board->current_map]->nb_bomb+=1;
    if(player->nb_bomb - 1 >= 0){
        player->nb_bomb -=1;
    }
    map->body[bomb->x][bomb->y] = board->items[player->bomb_type]->data->_char;
}

void is_bomb_arround(int i,Board *board, int x,int y){
    Map *map = board->maps[board->current_map];
    if(map->body[x][y] == board->items[item_bomb]->data->_char){
        recup_position(x,y, board);
    }
}

void recup_position(int x,int y, Board *board) {
    //pause();
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->x == x && board->maps[board->current_map]->bombs[i]->y == y){
            //TODO : mettre à 0 le nb_turn
            board->maps[board->current_map]->bombs[i]->nb_turn = 0;
        }
    }

}
void decrement_bomb(Board *board){
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->player_id == board->players[board->player_turn]->id){
            board->maps[board->current_map]->bombs[i]->nb_turn-=1;
        }
    }
}

void is_explosed(Board *board){
    //Vérfication explosion des bombes
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->nb_turn <= 0){
            explosion(i,board);
        }
    }

    //Suppression des bombes du tableau
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->nb_turn <= 0){
            remove_bomb(i, board);
        }
    }
}

//TODO : range
//TODO : verfif si un joueur n'est pas à cote d'une bombe
//TODO : put item
void explosion(int index, Board *board){
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    Bomb *bomb = map->bombs[index];
    int x = bomb->x;
    int y = bomb->y;
    int tmp = 0;
    /*Explosion Bombe Normal*/
    //A gauche
    for(int i = 1; i<= player->bomb_range; i++){
        if(y-i < 0){
            tmp++;
            if(boom(x, map->columns - tmp, map) == 0){
                break;
            }
        }else {
            is_bomb_arround(i,board,x,y-i);
            if(boom(x, y - i, map) == 0 || boom(x, y - i, map) == -1) break;
        }
    }
    tmp = 0;
    //Droite
    for(int i = 1; i<= player->bomb_range; i++){
        if(y+i > map->columns-1){
            tmp++;
            if(boom(x, -1 + tmp, map) == 0){
                break;
            }
        }else{
            is_bomb_arround(i,board,x,y+i);
            if(boom(x, y + i, map) == 0 || boom(x, y + i, map) == -1) break;
        }
    }
    tmp = 0;

    //Haut
    for(int i = 1; i<= player->bomb_range; i++){
        if(x-i < 0){
            tmp++;
            if(boom(map->rows - tmp, y, map) == 0){
                break;
            }
        }else {
            is_bomb_arround(i,board,x,x-i);
            if(boom(x - i, y, map) == 0 || boom(x - i, y, map) == -1) break;
        }
    }
    tmp=0;
    //Bas
    for(int i = 1; i<= player->bomb_range; i++){
        if(x+i > map->rows-1){
            tmp++;
            if(boom(-1 + tmp, y, map) == 0){
                break;
            }
        }else {
            is_bomb_arround(i,board,x,x+i);
            if(boom(x + i, y, map) == 0 || boom(x + i, y, map) == -1) break;
        }
    }

    map->body[bomb->x][bomb->y] = ' ';
    player->nb_bomb += 1;
}

int boom(int x, int y, Map *map){
    if(map->body[x][y] == 'm'){
        map->body[x][y] = ' ';
        return 0;
    }else if(map->body[x][y] == 'x') return -1;
    map->body[x][y] = ' ';
}

void remove_bomb(int index, Board *board){
    for (int i = index; i < board->maps[board->current_map]->nb_bomb; i++) {
        board->maps[board->current_map]->bombs[i] = board->maps[board->current_map]->bombs[i+1];
    }
    board->maps[board->current_map]->nb_bomb-=1;
}
