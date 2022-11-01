
void create_players(Board *board);

Player *_create_player(Board *board, int id);

void init_players(Board *board);
enum colors_index get_random_color_player(Board *board, int index);



void create_players(Board *board) {
    board->players = malloc(sizeof(Player) * board->nb_player);

    for (int i = 0; i < board->nb_player; ++i) {
        board->players[i] = _create_player(board, i);
        if(board->players[i] == NULL) {
            board->current_menu = menu_game_mode;
            break;
        }
    }
}


/**
 * @features : create player
 * */
Player *_create_player(Board *board, int id) {
    Player *player = malloc(sizeof(Player));

    char name[50];

    do {
        clear_console();
        printf("Entrez le joueur %c pseudo (q pour quitter) : ", id + 48 + 1);
        scanf("%s", name);
        if(strcmp(name, "q") == 0) {
            break;
        }
    } while(strlen(name) <= 1);

    if(strcmp(name, "q") == 0) {
        return NULL;
    }

    player->name = set_value(name);
    player->color = get_random_color_player(board, id);
    player->id = id + 48;
    player->is_bot = 0;
    player->score = 0;
    return player;
}

void init_players(Board *board) {
    for (int i = 0; i < board->nb_player; ++i) {
        board->players[i]->heart = 1;
        board->players[i]->nb_bomb = board->maps[board->current_map]->bomb_default;
        board->players[i]->bomb_range = 2;
        board->players[i]->bomb_type = item_bomb;
        board->players[i]->items = malloc(sizeof(Item));
        board->players[i]->bombs = malloc(sizeof(Bomb));
    }
}
enum colors_index get_random_color_player(Board *board, int index) {
    enum colors_index color;
    short unique;

    do {
        unique = 1;
        color = get_random_color();
        for (int i = 0; i < index; ++i) {
            if(color == board->players[i]->color || color == color_red || color == COLOR_DEFAULT || color == COLOR_BG_DEFAULT) {
                unique = 0;
                break;
            }
        }
    } while(!unique);

    return color;
}