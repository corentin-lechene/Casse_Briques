
Board *generate_board();

void run_game(Board *board);
void run_menu(Board *board);

void menu_events(Board *board, int event);

void get_players(Board *board);
Player *create_bot(Player *bot, int *index);
void push(Board *dest, Player *source, int index);
void tab_mix(char *tab[], int size);


char *get_event(int event) {
    switch (event) {
        case KEY_CROSS_TOP:
        case KEY_z:
        case KEY_CROSS_BOTTOM:
        case KEY_s:
        case KEY_CROSS_LEFT:
        case KEY_q:
        case KEY_CROSS_RIGHT:
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
    printf("[%d]", board->nb_selected_map);
    copy_maps(board);
//    init_players();
//
//    set_next_map(board);
    board->current_menu = IN_GAME;
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


void display_menus(Board *board) {
    Menu *current_menu = board->menus[board->current_menu];

    printf("menu: %s/%d | %d | choices: %d\n", board->menus[board->current_menu]->title, board->current_menu, board->current_choice, board->menus[board->current_menu]->nb_choice);
    printf("next: %d\n\n", current_menu->next_menu);

    switch (board->current_menu) {
        case menu_leave:
            break;
        case menu_home:
            menu_home_case(board);
            break;
        case menu_options:
            menu_options_case(board);
            break;
        case menu_languages:
            menu_languages_case(board);
            break;
        case menu_game_mode:
            menu_game_mode_case(board);
            break;
        case menu_solo:
            menu_solo_case(board);
            break;
        case menu_players:
            menu_players_case(board);
            break;
        case menu_maps:
            menu_maps_case(board);
            break;
        case menu_init_game:
            break;
        case menu_game:
            break;
        case menu_winner_summary:
            break;
        case menu_resume:
            menu_resume_case(board);
            break;
        case menu_patch_notes:
            menu_patch_notes_case(board);
            break;
        case menu_credits:
            menu_credits_case(board);
            break;
        default:
            break;
    }
}


void run_menu(Board *board) {
    int event = getch();
    int display = 0;

    Menu *current_menu = board->menus[board->current_menu];
    switch (event) {
        case KEY_CROSS_TOP:
            if(board->current_choice - 1 >= 0) {
                board->current_choice -= 1;
                display = 1;
            }
            break;
        case KEY_CROSS_BOTTOM:
            if(board->current_choice + 1 < current_menu->nb_choice) {
                board->current_choice += 1;
                display = 1;
            }
            break;
        case KEY_ENTER:
            if(board->current_choice == current_menu->nb_choice - 1) {
                board->current_menu = current_menu->next_menu;
                board->current_choice = 0;
                display = 1;
            } else {
                board->current_menu = current_menu->next_menu;
                board->current_choice = 0;
                display = 1;
            }
            break;
        case KEY_ESCAPE:
//            if(
//                    board->current_menu == menu_patch_notes ||
//                    board->current_menu == menu_credits
//                    ) {
//                board->current_menu = menu_home;
//                display = 1;
//            }
            break;

        case 'p':
            die();
        default:
            break;
    }

    if(display) {
        clear_console();
        display_menus(board);
    }
}





/**
 * @fetaures : get players
 * */
//void get_players(Board *board){
//    clear_console();
//    board->players = malloc(sizeof (Player *)*board->nb_player);
//    for(int i =0; i<board->nb_player; i++){
//        push(board, create_player( &i), i);
//    }
//
//    for(int i =0; i<board->nb_player; i++){
//        printf("\n%s", board->players[i]->color);
//        printf(" Pseudo => %s", board->players[i]->name);
//        printf(" IsBot => %d", board->players[i]->is_bot);
//        printf(" ID => %d", board->players[i]->id);
//    }
//    printf("%s\n", WHITE);
//    system("pause");
//}



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