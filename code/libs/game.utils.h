Board *generate_board();

void run_game(Board *board);
void run_menu(Board *board);
void get_players();
void menu_events(Board *board, int event);

void run_game(Board *board) {
    printf("RUN GAME");
}

void run_menu(Board *board) {
    int event = getch();
    menu_events(board, event);

    display_menus(board);

    if(board->selected_menu == IN_PLAYERS) {
        //board->players = get_players();
    } else if(board->selected_menu == IN_MAPS) {
//        board->selected_maps = get_selected_maps();
    }
}

void menu_events(Board *board, int event) {
    switch (event) {
        case CROSS_TOP:
        case KEY_z:
            if (board->selected_choice - 1 >= 0) {
                board->selected_choice -= 1;
            }
            break;
        case CROSS_BOTTOM:
        case KEY_s:
            board->selected_choice += 1;
            break;
        case KEY_ENTER:
            if(board->selected_menu == 1 && board->selected_choice == 2){
                board->selected_menu = 0;
            } else if ((board->selected_menu == 2 && board->selected_choice == 3) ||
                       (board->selected_menu == 3 && board->selected_choice == 3)) {
                board->selected_menu -= 1;
            } else if (board->selected_menu == 4 && board->selected_choice == 2) {
                board->selected_menu = 2;
            } else if (board->selected_menu == 2 && board->selected_choice == 2) {
                board->selected_menu = 4;
            } else {
                if (board->selected_menu + 1 < 5) {
                    board->selected_menu += 1;
                }
            }
            break;
        default:
            break;
    }
}

Board *generate_board() {

    Board *board = malloc(sizeof(Board));
    Config *config = malloc(sizeof(Config));

    config->language = malloc(sizeof(char) * 3);
    config->language = "FR";

    board->config = config;
    board->lang = get_lang(config->language);
    board->winner = malloc(sizeof(Player));
    board->players_turn = malloc(sizeof(Player));

    //    board->maps = get_maps();
    //    board->nb_map = get_nb_map(board->maps);

    //    unsigned short nb_map;          //le nombre de carte
    //    unsigned short nb_player;       //le nombre de joueur

    board->bo = 3;
    board->selected_menu = 1;
    board->selected_choice = 0;
    board->selected_map = 0;

    return board;
}

/**
 * @features : mélanger un tableau
 * */
void tab_mix(char *tab[], int size){
    char *tmp;
    int nbRandom=0;
    for(int i =0; i< size; i++){
        nbRandom = rand()%10;
        tmp = tab[i];
        tab[i] = tab[nbRandom];
        tab[nbRandom] = tmp;
    }
}

/**
 * @features : créer un bot
 * */
Player *create_bot(Player *bot, int *index){
    char *bot_name[10] = {"Bob","Fox","Mewtwo","Ritcher","Rob","Joker","Bot","Ricky","Toto","Test"};
    int size = 10;
    tab_mix(bot_name, size);
    bot->name = bot_name[*index];
    bot->is_bot = 1;
    return bot;
}

/**
 * @features : create player
 * */
Player *create_player(int *nb_added_player, int *nb_real_player,int *index){
    Player *player = malloc(sizeof(Player));
    player->name = malloc(sizeof (char));
    player->id = *index+48;
    player->score = 0;
    player->heart = 1;
    //couleur
    if(*nb_added_player != *nb_real_player){
        printf("Entrez votre pseudo : ");
        scanf("%s", player->name);
        player->is_bot = 0;
        *nb_added_player += 1;
        return player;
    }else {
        create_bot(player,index);
        return player;
    }
}

/**
 * @features : add player into player's tab
 * */
void push(Board *dest, Player *source, int index){
    dest->players[index] = source;
}
