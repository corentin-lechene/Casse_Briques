void display_menus(Board *board);

int create_players(Board *board);

Player *_create_player(Board *board, int id, short is_bot);
void add_bot_player(Board *board);

void init_players(Board *board);
void set_player_turn(Board *board);
void set_player_direction(char event, Board *board);

int can_move(Board *board, int x, int y, int rows, int columns);
int move_player(Board *board);
int is_space(Board *board, int x, int y);

short get_pos_player(Board *board, int index, char pos);
enum colors_index get_random_color_player(Board *board, int index);

int create_players(Board *board) {
    board->players = malloc(sizeof(Player) * board->nb_player);

    for (int i = 0; i < board->nb_player; ++i) {
        board->players[i] = _create_player(board, i, 0);
        if(board->players[i] == NULL) {
            board->current_menu = menu_game_mode;
            display_menus(board);
            return 0;
        }
    }
    return 1;
}

Player *_create_player(Board *board, int id, short is_bot) {
    Player *player = malloc(sizeof(Player));

    char name[50];

    if(!is_bot) {
        do {
            clear_console();
            display_menu_header(board);
            printf("Entrez le pseudo du joueur %d. (q pour quitter) : ", id  + 1);
            scanf("%s", name);
            display_wait();
            if(strcmp(name, "q") == 0) {
                break;
            }
        } while(strlen(name) <= 1);
    }

    if(strcmp(name, "q") == 0) {
        return NULL;
    }

    player->id = id + 48;
    if(is_bot) {
        player->name = set_value(PLAYER_NAMES[id]);
    } else {
        player->name = set_value(name);
    }

    player->color = get_random_color_player(board, player->id);
    player->is_bot = is_bot;
    player->score = 0;

    player->items = malloc(sizeof(Item *));
    player->nb_item = 0;
    return player;
}
void add_bot_player(Board *board) {
    if(board->game_mode == GAME_MODE_HOST) {
        return;
    }
    
    short min = board->maps[0]->player_max;
    for (int i = 0; i < board->nb_map; ++i) {
        if(board->maps[i]->player_max < min) {
            min = board->maps[i]->player_max;
        }
    }

    short map_player_max = min;
    short player_max = board->nb_player;

    for (int i = 0; i < map_player_max - player_max ; ++i) {
        Player *player = _create_player(board, player_max + i, 1);
        board->nb_player += 1;
        board->players = realloc(board->players, sizeof(Player *) * board->nb_player);
        board->players[player_max + i] = player;
    }
}

void init_players(Board *board) {
    for (int i = 0; i < board->nb_player; ++i) {
        board->players[i]->heart = 1;
        board->players[i]->nb_bomb = board->maps[board->current_map]->bomb_default; //todo not 1
        board->players[i]->x = get_pos_player(board, i, 'x');
        board->players[i]->y = get_pos_player(board, i, 'y');
        board->players[i]->bomb_range = 2;
        board->players[i]->bomb_type = item_bomb;

        board->players[i]->items = malloc(sizeof(Item *));
        board->players[i]->nb_item = 0;
    }
}

void set_player_turn(Board *board) {
    if(board->game_mode == GAME_MODE_HOST) {
        send_play(board);
    }
    board->player_turn = board->player_turn + 1 >= board->nb_player ? 0 : board->player_turn + 1;
}
void set_player_direction(char event, Board *board) {
    switch (event) {
        case KEY_CROSS_TOP :
        case KEY_z :
            board->players[board->player_turn]->direction = 0;
            break;
        case KEY_CROSS_LEFT :
        case KEY_q :
            board->players[board->player_turn]->direction = 3;
            break;
        case KEY_CROSS_BOTTOM :
        case KEY_s :
            board->players[board->player_turn]->direction = 2;
            break;
        case KEY_CROSS_RIGHT :
        case KEY_d :
            board->players[board->player_turn]->direction = 1;
            break;
    }
}

int move_player(Board *board) {
    Player *player = board->players[board->player_turn];
    Map *map = board->maps[board->current_map];
    int i = 2;
    int check = can_move(board, player->x, player->y, map->rows-1, map->columns-1);
    if (check == 0) {
//        infof("Vous ne pouvez pas bouger dans cette direction !!!");
//        pause();
        return 0;
    }
    if(get_bomb_at(player->x, player->y, board) == NULL) {
        map->body[player->x][player->y] = ' ';
    }
    switch (player->direction) {
        case 0:
            if(check == 2){
                int pos = (int) player->x - i;
                if(pos >= 0) {
                    while(is_space(board,pos,player->y) != 1){
                        if(map->body[pos][player->y] == 'm' || map->body[pos][player->y] == 'x' ||(map->body[pos][player->y] >= 48 && map->body[pos][player->y] <= 57)) return 0;
                        decrement_or_reset((unsigned short *) &pos, map->rows - 1);
                        if(pos == player->x) return 0;
                    }
                    player->x = pos+1;
                }
            }
            decrement_or_reset(&player->x, map->rows-1);
            break;
        case 2:
            if(check == 2){
                unsigned short pos = player->x + i;
                if(pos < map->rows) {
                    while(is_space(board,pos,player->y) != 1){
                        if(map->body[pos][player->y] == 'm' || map->body[pos][player->y] == 'x' ||(map->body[pos][player->y] >= 48 && map->body[pos][player->y] <= 57)) return 0;
                        increment_or_reset(&pos,map->rows-1);
                        if(pos == player->x) return 0;
                    }
                    player->x = pos-1;
                }
            }
            increment_or_reset(&player->x, map->rows-1);
            break;
        case 1:
            if(check == 2){
                unsigned short pos = player->y + i;
                if(pos < map->columns) {
                    while(is_space(board,player->x,pos) != 1){
                        if(map->body[player->x][pos] == 'm' || map->body[player->x][pos] == 'x' ||(map->body[player->x][pos] >= 48 && map->body[player->x][pos] <= 57)) return 0;
                        increment_or_reset(&pos,map->columns-1);
                        if(pos == player->y) return 0;
                    }
                    player->y = pos-1;
                }
            }
            increment_or_reset(&player->y, map->columns-1);
            break;
        case 3 :
            if(check == 2){
                int pos = (int) player->y - i;
                if(pos >= 0) {
                    while(is_space(board,player->x,pos) != 1){
                        if(map->body[player->x][pos] == 'm' || map->body[player->x][pos] == 'x' ||(map->body[player->x][pos] >= 48 && map->body[player->x][pos] <= 57)) return 0;
                        decrement_or_reset((unsigned short *) &pos, map->columns - 1);
                        if(pos == player->y) return 0;
                    }
                    player->y = pos+1;   
                }
            }
            decrement_or_reset(&player->y, map->columns-1);
            break;
    }
    map->body[player->x][player->y] = player->id;

    set_player_turn(board);
    return 1;
}


int is_space(Board *board, int x, int y){
    if (board->maps[board->current_map]->body[x][y] != ' ') {
        int index_item = is_item(board,x,y);
        if(index_item == -2) return 0;
        if(index_item != -1) {
            get_item(board,index_item);
            return 1;
        }
        if(has_item(board, bomb_passes) == 1){
            return 2;
        }
        return 0;

    } else if (board->maps[board->current_map]->body[x][y] == ' ') {
        return 1;
    }
}


int can_move(Board *board, int x, int y, int rows, int columns) {
    int check = 0;
    switch (board->players[board->player_turn]->direction) {
        case 0 :
            if(x==0){
                if(is_space(board,rows,y) == 0) return 0;
                else return 1;
            }
            check = is_space(board,x-1,y);
            if(check == 0) return 0;
            else if(check == 2) return 2;
            else return 1;

        case 1 :
            if(y==columns){
                if(is_space(board,x,0) == 0) return 0;
                else return 1;
            }
            check = is_space(board,x,y+1);
            if(check == 0) return 0;
            else if(check == 2) return 2;
            else return 1;
        case 2 :
            if(x==rows){
                if(is_space(board,0,y) == 0) return 0;
                else return 1;
            }
            check = is_space(board,x+1,y);
            if(check == 0) return 0;
            else if(check == 2) return 2;
            else return 1;

        case 3:
            if(y==0){
                if(is_space(board,x,columns) == 0) return 0;
                else return 1;
            }
            check = is_space(board,x,y-1);
            if(check == 0) return 0;
            else if(check == 2) return 2;
            else return 1;

    }
}

short get_pos_player(Board *board, int index, char pos) {
    int nb_p = 0;

    for (int x = 0; x < board->maps[board->current_map]->rows; ++x) {
        for (int y = 0; y < board->maps[board->current_map]->columns; ++y) {
            if(board->maps[board->current_map]->body[x][y] == 'p') {
                if(nb_p == index) {
                    return pos == 'x' ? x : y;
                }
                nb_p += 1;
            }
        }
    }
    return -1;
}
enum colors_index get_random_color_player(Board *board, int index) {
    enum colors_index color;
    short unique;

    do {
        unique = 1;
        color = get_random_color();
        for (int i = 0; i < index - 48; ++i) {
            if(color == board->players[i]->color) {
                unique = 0;
                break;
            }
        }
    } while(!unique);
    return color;
}
