int plant_bomb(Board *board);
void init_bomb(Board *board);
void init_bomb_kick(Board *board);
void init_bomb_destroy(Board *board);

void decrement_bomb(Board *board);
void is_explosed(Board *board);

void remove_bomb(int index, Board *board);
void explosion(int index, Board *board);
int boom(int x, int y, Board *board);
int boom_destroy(Board *board,int x, int y);

void is_bomb_around(Board *board, int x, int y);
void recup_position(int x,int y, Board *board);


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
    return 1;
}

void init_bomb_kick(Board *board){
    Map *map = board->maps[board->current_map];

    Player *player = board->players[board->player_turn];
    Bomb *bomb = map->bombs[board->maps[board->current_map]->nb_bomb];

    if(player->bomb_type == bomb_kick){
        bomb->nb_turn = 4;
        int x = player->x;
        int y = player->y;
        int i = 1;
        if (player->direction == 3) {
            while (map->body[x][y+i] != 'm') {
                i++;
            }
            bomb->x = x;
            bomb->y = (y+i)-1;
            map->body[x][(y+i)-1] = board->items[player->bomb_type]->data->_char;
        }
        if (player->direction == 1) {
            while (map->body[x][y-i] != 'm') {
                i++;
            }
            bomb->x = x;
            bomb->y = (y-i)+1;
            map->body[x][(y-i)+1] = board->items[player->bomb_type]->data->_char;
        }
        if (player->direction == 2) {
            while (map->body[x-i][y] != 'm') {
                i++;
            }
            bomb->x = (x-i)+1;
            bomb->y = y;
            map->body[(x-i)+1][y] = board->items[player->bomb_type]->data->_char;
        }
        if (player->direction == 0) {
            while (map->body[x+i][y] != 'm') {
                i++;
            }
            bomb->x = (x+i)-1;
            bomb->y = y;
            map->body[(x+i)-1][y] = board->items[player->bomb_type]->data->_char;
        }
    }
}

void init_bomb_destroy(Board *board){
    Map *map = board->maps[board->current_map];
    Bomb *bomb = map->bombs[board->maps[board->current_map]->nb_bomb];
    Player *player = board->players[board->player_turn];

    bomb->nb_turn = 1;
    bomb->data->_char = board->items[player->bomb_type]->data->_char;
    bomb->x = player->x;
    bomb->y = player->y;
}
void init_bomb(Board *board){
    Player *player = board->players[board->player_turn];
    Map *map = board->maps[board->current_map];
    int nb_bomb = map->nb_bomb;
    board->maps[board->current_map]->bombs[nb_bomb] = malloc(sizeof (Bomb));
    Bomb *bomb = map->bombs[board->maps[board->current_map]->nb_bomb];
    bomb->data = malloc(sizeof (Data_item));
    //player->bomb_type = bomb_destroy;
    //player->bomb_type = bomb_kick;

    if(player->bomb_type == bomb_destroy){
        init_bomb_destroy(board);
    }else if (player->bomb_type == bomb_kick){
        init_bomb_kick(board);
    } else {
        bomb->nb_turn = 4;
        bomb->range = player->bomb_range;
        bomb->x = player->x;
        bomb->y = player->y;
    }

    bomb->player_id = board->players[board->player_turn]->id;
    board->maps[board->current_map]->nb_bomb+=1;
    if(player->nb_bomb - 1 >= 0){
        player->nb_bomb -=1;
    }

    if (bomb->nb_turn != 1){
        map->body[bomb->x][bomb->y] = board->items[player->bomb_type]->data->_char;
    }
}

void is_bomb_around(Board *board, int x, int y) {
    Map *map = board->maps[board->current_map];
    //TODO : faire pour ttes les bombes
    if(map->body[x][y] == board->items[item_bomb]->data->_char){
        recup_position(x,y, board);
    }
}

void recup_position(int x,int y, Board *board) {
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->x == x && board->maps[board->current_map]->bombs[i]->y == y){
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

int boom_destroy(Board *board,int x, int y){
    Map *map = board->maps[board->current_map];
    if(map->body[x][y] == 'x') {
        map->body[x][y]=' ';
        return 0;
    }
    if(is_item(board,x,y) == -1){
        map->body[x][y]=' ';
    }
    return 1;
}

/**
 *
 *
 * */
void explosion_bomb_destroy(int index, Board *board){
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    Bomb *bomb = map->bombs[index];
    int x = bomb->x;
    int y = bomb->y;
    int tmp = 1;
    int j =0;
    int i = 0;
    if (player->direction == 3) {
        while(tmp != 0){
            i++;
            if(y-i < 0){
                j++;
                tmp = boom_destroy(board,x,(map->columns)-j);
            }else {
                tmp = boom_destroy(board,x,y-i);
            }
        }
    }
    j=0;
    if (player->direction == 1) {
        i = 0;
        while(tmp != 0){
            i++;
            if(y+i > map->columns-1){
                j++;
                tmp = boom_destroy(board,x,-1+j);
            }else {
                tmp = boom_destroy(board,x,y+i);
            }
        }
    }
    j = 0;
    if (player -> direction == 2) {
        i = 0;
        while(tmp != 0){
            i++;
            if(x+i > map->rows-1){
                j++;
                tmp = boom_destroy(board,-1+j,y);
            }else {
                tmp = boom_destroy(board,x+i,y);
            }
        }
    }
    if (player -> direction == 0) {
        i = 0;
        while(tmp != 0){
            i++;
            if(x-i < 0){
                j++;
                tmp = boom_destroy(board,map->rows-j,y);
            }else {
                tmp = boom_destroy(board,x-i,y);
            }
        }
    }

    player->nb_bomb += 1;
}


void is_explosed(Board *board){
    //Vérfication explosion des bombes
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->nb_turn <= 0){
            //verif si c'est une bomb_destroy
            if(board->maps[board->current_map]->bombs[i]->data->_char == board->items[bomb_destroy]->data->_char){
                explosion_bomb_destroy(i,board);
            }else {
                explosion(i,board);//en focntion du type de la bombe(destroy)
            }
        }
    }

    //Suppression des bombes du tableau
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->nb_turn <= 0){
            remove_bomb(i, board);
        }
    }
}

//TODO : verfif si un joueur n'est pas à cote d'une bombe
void explosion(int index, Board *board){
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    Bomb *bomb = map->bombs[index];
    int x = bomb->x;
    int y = bomb->y;
    int tmp = 0;
    /*Explosion Bombe Normal*/
    //A gauche
    for(int i = 1; i<= bomb->range; i++){
        if(y-i < 0){
            tmp++;
            if(boom(x, map->columns - tmp, board) == 0){
                break;
            }
        }else {
            is_bomb_around(board, x, y - i);
            if(boom(x, y - i, board) == 0 || boom(x, y - i, board) == -1) break;
        }
    }
    tmp = 0;
    //Droite
    for(int i = 1; i<= bomb->range; i++){
        if(y+i > map->columns-1){
            tmp++;
            if(boom(x, -1 + tmp, board) == 0){
                break;
            }
        }else{
            is_bomb_around(board, x, y + i);
            if(boom(x, y + i, board) == 0 || boom(x, y + i, board) == -1) break;
        }
    }
    tmp = 0;

    //Haut
    for(int i = 1; i<= bomb->range; i++){
        if(x-i < 0){
            tmp++;
            if(boom(map->rows - tmp, y, board) == 0){
                break;
            }
        }else {
            is_bomb_around(board, x-i, y);
            if(boom(x - i, y, board) == 0 || boom(x - i, y, board) == -1) break;
        }
    }
    tmp=0;
    //Bas
    for(int i = 1; i<= bomb->range; i++){
        if(x+i > map->rows-1){
            tmp++;
            if(boom(-1 + tmp, y, board) == 0){
                break;
            }
        }else {
            is_bomb_around(board, x+i, y);
            if(boom(x + i, y, board) == 0 || boom(x + i, y, board) == -1) break;
        }
    }

    map->body[bomb->x][bomb->y] = ' ';
    player->nb_bomb += 1;
}

int boom(int x, int y, Board *board){
    Map *map = board->maps[board->current_map];
    if(x == - 1 || y == -1 || x==map->rows || y == map->columns)return 0;
    if(map->body[x][y] == 'm'){
        map->body[x][y] = ' ';
        put_item(board,x,y);
        return 0;
    }else if(map->body[x][y] == 'x') return -1;
    if(is_item(board,x,y) == -1){
        map->body[x][y] = ' ';
    }
}

void remove_bomb(int index, Board *board){
    for (int i = index; i < board->maps[board->current_map]->nb_bomb; i++) {
        board->maps[board->current_map]->bombs[i] = board->maps[board->current_map]->bombs[i+1];
    }
    board->maps[board->current_map]->nb_bomb-=1;
}
