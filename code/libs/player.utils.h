
void display_menus(Board *board);

void create_players(Board *board);

Player *_create_player(Board *board, int id, short is_bot);
void add_bot_player(Board *board);

void init_players(Board *board);
void set_player_turn(Board *board);
void set_player_direction(char event, Board *board);

int can_move(Board *board, int x, int y, int rows, int columns);
int move_player(Board *board);

short get_pos_player(Board *board, int index, char pos);
enum colors_index get_random_color_player(Board *board, int index);



void create_players(Board *board) {
    board->players = malloc(sizeof(Player) * board->nb_player);

    for (int i = 0; i < board->nb_player; ++i) {
        board->players[i] = _create_player(board, i, 0);
        if(board->players[i] == NULL) {
            board->current_menu = menu_game_mode;
            display_menus(board);
            break;
        }
    }
}

Player *_create_player(Board *board, int id, short is_bot) {
    Player *player = malloc(sizeof(Player));

    char name[50];

    if(!is_bot) {
        do {
            clear_console();
            printf("Entrez le joueur %c pseudo (q pour quitter) : ", id + 48 + 1);
            scanf("%s", name);
            if(strcmp(name, "q") == 0) {
                break;
            }
        } while(strlen(name) <= 1);
    }

    if(strcmp(name, "q") == 0) {
        return NULL;
    }

    player->id = id + 48;
    player->name = set_value(name);
    player->color = get_random_color_player(board, player->id);
    player->is_bot = is_bot;
    player->score = 0;

    player->bombs = malloc(sizeof(Bomb *));
    player->nb_bomb = 1;
    for (int j = 0; j < player->nb_bomb; ++j) {
        player->bombs[j] = malloc(sizeof(Bomb));
        player->bombs[j]->data = malloc(sizeof(Data_item));
    }

    player->items = malloc(sizeof(Item *));
    player->nb_item = 1;
    for (int i = 0; i < player->nb_item; ++i) {
        player->items[i] = malloc(sizeof(Item));
        player->items[i]->data = malloc(sizeof(Data_item));
        player->items[i]->name = malloc(sizeof(char) * 1);
    }
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
        board->players[i]->nb_bomb = board->maps[board->current_map]->bomb_default;
        board->players[i]->x = get_pos_player(board, i, 'x');
        board->players[i]->y = get_pos_player(board, i, 'y');
        board->players[i]->bomb_range = 2;
        board->players[i]->bomb_type = item_bomb;

        board->players[i]->bombs = malloc(sizeof(Bomb *));
        for (int j = 0; j < board->players[i]->nb_bomb; ++j) {
            board->players[i]->bombs[j] = malloc(sizeof(Bomb));
            board->players[i]->bombs[j]->data = malloc(sizeof(Data_item));
        }

        board->players[i]->items = malloc(sizeof(Item *));
        board->players[i]->nb_item = 1;
        for (int j = 0; j < board->players[i]->nb_item; ++j) {
            board->players[i]->items[j] = malloc(sizeof(Item));
            board->players[i]->items[j]->data = malloc(sizeof(Data_item));
            board->players[i]->items[j]->name = NULL;
        }
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
        return 0;
    }
    map->body[player->x][player->y] = ' ';
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
    set_player_turn(board);
    return 1;
}
int can_move(Board *board, int x, int y, int rows, int columns) {
    //TODO:bombe + id + next
    switch (board->players[board->player_turn]->direction) {
        case 0 :
            if (x == 0 && board->maps[board->current_map]->body[rows][y] != ' ') {
                return 0;
            } else if (x == 0 && board->maps[board->current_map]->body[rows][y] == ' ') {
                return 1;
            }
            if (board->maps[board->current_map]->body[x - 1][y] == 'x' || board->maps[board->current_map]->body[x - 1][y] == 'm' ||
                board->maps[board->current_map]->body[x - 1][y] == 'p') {
                return 0;
            }
            break;
        case 1 :
            if (y == columns && board->maps[board->current_map]->body[x][0] != ' ') {
                return 0;
            } else if (y == columns && board->maps[board->current_map]->body[x][0] == ' ') {
                return 1;
            }
            if (board->maps[board->current_map]->body[x][y + 1] == 'x' || board->maps[board->current_map]->body[x][y + 1] == 'm' ||
                board->maps[board->current_map]->body[x][y + 1] == 'p') {
                return 0;
            }
            break;
        case 2 :
            if (x == rows && board->maps[board->current_map]->body[0][y] != ' ') {
                return 0;
            } else if (x == rows && board->maps[board->current_map]->body[0][y] == ' ') {
                return 1;
            }
            if (board->maps[board->current_map]->body[x + 1][y] == 'x' || board->maps[board->current_map]->body[x + 1][y] == 'm' ||
                board->maps[board->current_map]->body[x + 1][y] == 'p') {
                return 0;
            }
            break;
        case 3:
            if (y == 0 && board->maps[board->current_map]->body[x][columns] != ' ') {
                return 0;
            } else if (y == 0 && board->maps[board->current_map]->body[x][columns] == ' ') {
                return 1;
            }
            if (board->maps[board->current_map]->body[x][y - 1] == 'x' || board->maps[board->current_map]->body[x][y - 1] == 'm' ||
                board->maps[board->current_map]->body[x][y - 1] == 'p') {
                return 0;
            }
            break;
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