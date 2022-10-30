Board *generate_board();

void run_game(Board *board);
void run_menu(Board *board);

void menu_events(Board *board, int event);

void get_players(Board *board);
Player *create_player(int *index);
Player *create_bot(Player *bot, int *index);
void push(Board *dest, Player *source, int index);
void tab_mix(char *tab[], int size);

void get_maps_by_number_player(Board *board);

char *get_event(int event) {
    switch (event) {
        case CROSS_TOP:
        case KEY_z:
        case CROSS_BOTTOM:
        case KEY_s:
        case CROSS_LEFT:
        case KEY_q:
        case CROSS_RIGHT:
        case KEY_d:
            return "move";

        case KEY_ENTER:
        case KEY_SPACE:
            return "bomb";

        case KEY_ESCAPE:
            return "resume";

        default:
            return NULL;
    }
}


void init_game(Board *board) {
    copy_maps(board);
//    init_players();
//
//    set_next_map(board);
    board->selected_menu = IN_GAME;
    display_map(board->maps[0]);
}


void run_game(Board *board) {
    if(kbhit()) {
        int event = getch();
        const char *event_name = get_event(event);

        if(strcmp(event_name, "move") == 0) {
//            set_player_direction(event);
//            if(move_player(board)) {
//                display_map(board->maps[board->selected_map]);
//            }
        } else if(strcmp(event_name, "bomb") == 0) {
//            if(plant_bomb(board)) {
//                display_map(board->maps[board->selected_map]);
//            }
        } else if(strcmp(event_name, "resume") == 0) {
//            display_resume(board);
        }
    }
}

void run_menu(Board *board) {
    int event = getch();
    menu_events(board, event);
    display_menus(board);

    if(board->selected_menu == IN_PLAYERS) {
        get_players(board);
        get_maps_by_number_player(board);
        board->selected_menu = MENU_SELECT_MAPS;
        display_menus(board);
    }
}

void menu_events(Board *board, int event) {
    switch (event) {
        case CROSS_TOP:
        case KEY_z:
        case CROSS_BOTTOM:
        case KEY_s:
            board->selected_choice += 1;
            break;
        case KEY_ENTER:
            if(board->selected_menu == MENU_START && board->selected_choice == 2){
                board->selected_menu = IN_EXIT;
            } else if ((board->selected_menu == MENU_MODE_GAME && board->selected_choice == 3) ||
                    (board->selected_menu == MENU_NUMBER_PLAYER && board->selected_choice == 6)) {
                board->selected_menu -= 1;
            } else if (board->selected_menu == MENU_ONLINE && board->selected_choice == 2) {
                board->selected_menu = MENU_MODE_GAME;
            } else if (board->selected_menu == MENU_MODE_GAME && board->selected_choice == 2) {
                board->selected_menu = MENU_ONLINE;
            }else if(board->selected_menu == MENU_SELECT_MAPS && board->selected_choice == 3){
                board->selected_menu = MENU_NUMBER_PLAYER;
            }else if(board->selected_menu == MENU_NUMBER_PLAYER){
                board->nb_player = board->selected_choice + 1; //recup le nombre de joueur réel choisit
                board->selected_menu = IN_PLAYERS;
            }else if(board->selected_menu == MENU_START && board->selected_choice == 1){
                board->selected_menu = IN_CONFIG;
            } else if(board->selected_menu == MENU_SELECT_MAPS){
                board->selected_menu = IN_GAME;
            }
            else if(board->selected_menu == IN_CONFIG){
                if(board->selected_choice == 2){
                    board->selected_menu = MENU_START;
                }else if(board->selected_choice == 0){
                    board->config->language = "FR";
                }else if(board->selected_choice == 1){
                    board->config->language = "EN";
                }
//                board->lang = get_langs(board->config->language);
                board->selected_menu = MENU_START;
            }
            else {
                    if (board->selected_menu + 1 < 12) {
                        board->selected_menu += 1;
                    }
                }

            board->selected_choice = 0;
            break;
        default:
            break;
    }
}


void get_maps_by_number_player(Board *board){
//    int j =0;
//    for(int i =0; i<board->nb_map; i++){
////        if(board->maps[i]->player_max >= board->nb_player){
//            board->selected_maps[j] = board->maps[i];
//            board->selected_map++;
//            j++;
////        }
//    }
}



/**
 * @fetaures : get players
 * */
void get_players(Board *board){
    clear_console();
    board->players = malloc(sizeof (Player *)*board->nb_player);
    for(int i =0; i<board->nb_player; i++){
        push(board, create_player( &i), i);
    }

    for(int i =0; i<board->nb_player; i++){
        printf("\n%s", board->players[i]->color);
        printf(" Pseudo => %s", board->players[i]->name);
        printf(" IsBot => %d", board->players[i]->is_bot);
        printf(" ID => %d", board->players[i]->id);
    }
    printf("%s\n", WHITE);
    system("pause");
}

/**
 * @features : create player
 * */
Player *create_player(int *index){
    char *colors[6] = {RED, GREEN,YELLOW,BLUE,PURPLE,CYAN};
    Player *player = malloc(sizeof(Player));
    player->color = malloc(sizeof (char));
    player->name = malloc(sizeof (char));
    player->color = colors[*index];
    player->id = *index+48;
    player->score = 0;
    player->heart = 1;
    printf("Entrez votre pseudo : ");
    scanf("%s", player->name);
    player->is_bot = 0;
    return player;
}

/**
 * @features : create a bot
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
 * @features : add player into player's tab
 * */
void push(Board *dest, Player *source, int index){
    dest->players[index] = source;
}

/**
 * @features : mix an array
 * */
void tab_mix(char *tab[], int size){
    char *tmp;
    int nbRandom=0;
    for(int i =0; i< size; i++){
        nbRandom = rand()%size;
        tmp = tab[i];
        tab[i] = tab[nbRandom];
        tab[nbRandom] = tmp;
    }
}