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
int is_bomb(Board *board, int x,int y);

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
    short map_player_max = board->maps[board->current_map]->player_max;
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
        //board->players[i]->nb_bomb = board->maps[board->current_map]->bomb_default;
        board->players[i]->nb_bomb = 1;
        board->players[i]->x = get_pos_player(board, i, 'x');
        board->players[i]->y = get_pos_player(board, i, 'y');
        board->players[i]->bomb_range = 2;
        board->players[i]->bomb_type = item_bomb;

        board->players[i]->items = malloc(sizeof(Item *));
        board->players[i]->nb_item = 0;
    }
}

void set_player_turn(Board *board) {
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

    if (can_move(board, player->x, player->y, map->rows-1, map->columns-1) == 0) {
        infof("Vous ne pouvez pas bouger dans cette direction !!!");
        pause();
        return 0;
    }
    if(map->body[player->x][player->y] != board->items[player->bomb_type]->data->_char){
        map->body[player->x][player->y] = ' ';
    }
    switch (player->direction) {
        case 0:
            decrement_or_reset(&player->x, map->rows-1);
            break;
        case 2:
            increment_or_reset(&player->x, map->rows-1);
            break;
        case 1:
            increment_or_reset(&player->y, map->columns-1);
            break;
        case 3 :
            decrement_or_reset(&player->y, map->columns-1);
            break;
    }
    map->body[player->x][player->y] = player->id;

    if(board->maps[board->current_map]->nb_bomb > 0){
        decrement_bomb(board);
        is_explosed(board);

    }
    set_player_turn(board);
    return 1;
}


int is_bomb(Board *board, int x,int y){
    Map *map = board->maps[board->current_map];
    int items_bomb[] = {item_bomb, item_bomb_destroy, item_bomb_kick, item_bomb_push};

    for(int i =0; i<4;i++){
        if(map->body[x][y] == board->items[items_bomb[i]]->data->_char ){
            return 0;
        }
    }
    return 1;
}

int is_space(Board *board, int x, int y){
    if (board->maps[board->current_map]->body[x][y] != ' ') {
        return 0;
    } else if (board->maps[board->current_map]->body[x][y] == ' ') {
        return 1;
    }
}


int can_move(Board *board, int x, int y, int rows, int columns) {
    switch (board->players[board->player_turn]->direction) {
        case 0 :
            if(x==0){
                if(is_space(board,rows,y) == 0) return 0;
                else return 1;
            }
            if(is_space(board,x-1,y) == 0) return 0;
            else return 1;
        case 1 :
            if(y==columns){
                if(is_space(board,x,0) == 0) return 0;
                else return 1;
            }
            if(is_space(board,x,y+1) == 0) return 0;
            else return 1;
        case 2 :
            if(x==rows){
                if(is_space(board,0,y) == 0) return 0;
                else return 1;
            }
            if(is_space(board,x+1,y) == 0) return 0;
            else return 1;
        case 3:
            if(y==0){
                if(is_space(board,x,columns) == 0) return 0;
                else return 1;
            }
            if(is_space(board,x,y-1) == 0) return 0;
            else return 1;
    }
    return 1;
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



