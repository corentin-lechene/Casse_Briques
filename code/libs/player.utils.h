
void create_players(Board *board);

Player *_create_player(Board *board, int id);

enum colors_index get_random_color_player(Board *board, int index);

void create_players(Board *board) {
    board->players = malloc(sizeof(Player) * board->nb_player);

    for (int i = 0; i < board->nb_player; ++i) {
        printf("player[%d]\n", i);
        board->players[i] = _create_player(board, i);
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
        printf("Entrez le joueur %c pseudo : ", id + 48);
        scanf("%s", name);
    } while(strlen(name) <= 1);


    player->name = set_value(name);
    player->color = get_random_color_player(board, id);
    player->id = id + 48;
    player->is_bot = 0;
    return player;
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