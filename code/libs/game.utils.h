
Board *generate_board();

void run_game(Board *board);
void run_menu(Board *board);

void menu_events(Board *board, int event);

void get_players(Board *board);
Player *create_bot(Player *bot, int *index);
void push(Board *dest, Player *source, int index);
void tab_mix(char *tab[], int size);


void set_player_direction(char event, Board *board);

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
    set_next_map(board);
    set_player_turn(board);

    copy_maps(board);
    init_players(board);
    init_map(board);

    display_board(board);
    display_next_menu(board, menu_game, &run_game);
}

int can_move(Board *board, int x, int y, int rows, int columns) {
    //TODO:bombe + next
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

//TODO : gestion player_turn
int move_player(Board *board) {
    Player *player = board->players[board->player_turn];
    Map *map = board->maps[board->current_map];

    if (can_move(board, player->x, player->y, map->rows-1, map->columns-1) == 0) {
        display_board(board);

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
    return 1;
}

void run_game(Board *board) {
    display_board(board);

    //if (kbhit()) {

        int event = my_getch();
        const char *event_name = get_event(event);
        if (strcmp(event_name, "move") == 0) {
            set_player_direction(event, board);
            move_player(board);

        } else if (strcmp(event_name, "bomb") == 0) {
            //            if(plant_bomb(board)) {
            //                display_map(board->maps[board->selected_map]);
            //            }
        } else if (strcmp(event_name, "resume") == 0) {
            //            display_resume(board);
        }
    //}
    //else {
      //  display_board(board);
    //}
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


void display_menus(Board *board) {
    Menu *current_menu = board->menus[board->current_menu];

    printf("menu: %s/%d | %d | choices: %d\n", board->menus[board->current_menu]->title, board->current_menu,
           board->current_choice, board->menus[board->current_menu]->nb_choice);
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
    int event = my_getch();
    int display = 0;

    Menu *current_menu = board->menus[board->current_menu];
    switch (event) {
        case KEY_CROSS_TOP:
            if (board->current_choice - 1 >= 0) {
                board->current_choice -= 1;
                display = 1;
            }
            break;
        case KEY_CROSS_BOTTOM:
            if (board->current_choice + 1 < current_menu->nb_choice) {
                board->current_choice += 1;
                display = 1;
            }
            break;
        case KEY_ENTER:
            if (board->current_choice == current_menu->nb_choice - 1) {
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

    if (display) {
        clear_console();
        display_menus(board);
    }
}


/**
 * @features : create a bot
 * */
Player *create_bot(Player *bot, int *index) {
    char *bot_name[10] = {"Bob", "Fox", "Mewtwo", "Ritcher", "Rob", "Joker", "Bot", "Ricky", "Toto", "Test"};
    int size = 10;
    tab_mix(bot_name, size);
    bot->name = bot_name[*index];
    bot->is_bot = 1;
    return bot;
}

/**
 * @features : add player into player's tab
 * */
void push(Board *dest, Player *source, int index) {
    dest->players[index] = source;
}

/**
 * @features : mix an array
 * */
void tab_mix(char *tab[], int size) {
    char *tmp;
    int nbRandom = 0;
    for (int i = 0; i < size; i++) {
        nbRandom = rand() % size;
        tmp = tab[i];
        tab[i] = tab[nbRandom];
        tab[nbRandom] = tmp;
    }
}