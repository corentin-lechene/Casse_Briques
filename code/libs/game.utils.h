
void run_game(Board *board);
void run_menu(Board *board);
void init_game(Board *board);

void display_menus(Board *board);
void display_menu_static(Board *board);
void display_menu_custom(Board *board);

char *get_event(int event);
void put_item(Board *board, int x,int y);
void decrement_bomb(Board *board);
//#include <unistd.h>

/* ---------------------------------------- */
void init_bomb(Board *board, int x ,int y){

    Map *map = board->maps[board->current_map];
    int nb_bomb = map->nb_bomb;
    board->maps[board->current_map]->bombs[nb_bomb] = malloc(sizeof (Bomb));
    Bomb *bomb = map->bombs[board->maps[board->current_map]->nb_bomb];
    bomb->nb_turn = 4;
    bomb->x =x;
    bomb->y = y;
    bomb->player_id = board->players[board->player_turn]->id;
    board->maps[board->current_map]->nb_bomb+=1;

}
void plant_bomb(Board *board){
    Player *player = board->players[board->player_turn];
    Map *map = board->maps[board->current_map];
    int x = player->x;
    int y = player->y;
    init_bomb(board, x, y);
    map->body[x][y] = 'P';
    set_player_turn(board);
}

void is_explosed(Board *board){
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        if(board->maps[board->current_map]->bombs[i]->nb_turn == 0){
            printf("EXPLOSION !!");
            pause();
        }
        //board->maps[board->current_map]->bombs[i]->nb_turn-=1;
        //printf("Nombre de tour : %d\n", board->maps[board->current_map]->bombs[i]->nb_turn);
    }
    /*

    if(map->body[x][y+1] != 'x'){
        map->body[x][y+1] = board->items[7]->data->_char;
        put_item(board,x,y+1);

    }*/

}

void decrement_bomb(Board *board){
    for (int i = 0; i < board->maps[board->current_map]->nb_bomb; i++) {
        board->maps[board->current_map]->bombs[i]->nb_turn-=1;
    }
}

void run_game(Board *board) {
    if (kbhit()) {

        int event = my_getch();
        const char *event_name = get_event(event);

        if(event_name == NULL) {
            return;
        }

        if (strcmp(event_name, "move") == 0) {
            set_player_direction(event, board);
            move_player(board);
            display_board(board);
        } else if (strcmp(event_name, "bomb") == 0) {
            plant_bomb(board);
            display_board(board);

//            if(plant_bomb(board)) {
//                  display_board(board);
//            }
        } else if (strcmp(event_name, "resume") == 0) {
            display_next_menu(board, menu_resume, &menu_resume_case);
            return;
        }

        if(board->maps[board->current_map]->nb_bomb > 0){
            decrement_bomb(board);
            is_explosed(board);
            //pause();

        }
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
void init_game(Board *board) {
    set_next_map(board);
    set_player_turn(board);

    copy_maps(board);
    add_bot_player(board);
    init_players(board);
    init_map(board);
    board->maps[board->current_map]->bombs = malloc(sizeof (Bomb *));
    board->maps[board->current_map]->nb_bomb = 0;
    display_board(board);
    board->current_menu = menu_game;
}

void display_menus(Board *board) {
    display_menu_static(board);
    display_menu_custom(board);
}
void display_menu_static(Board *board) {
    switch (board->current_menu) {
        case menu_home:
            menu_home_case(board);
            break;
        case menu_options:
            menu_options_case(board);
            break;
        case menu_set_languages:
            menu_set_languages_case(board);
        case menu_game_mode:
            menu_game_mode_case(board);
            break;
        case menu_reset_game:
            menu_reset_game_case(board);
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
void display_menu_custom(Board *board) {
    switch (board->current_menu) {
        case menu_languages:
            menu_languages_case(board);
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
        default:
            break;
    }
}

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
void put_item(Board *board, int x, int y){
    Map *map = board->maps[board->current_map];
    items_rarity items_rarity[] = {blue_flame, yellow_flame, bomb_up, bomb_down};
    items_rarity_epic items_rarity_epic[] = {bomb_passes, bomb_kick, invincibility, heart};
    items_rarity_legendary items_rarity_legendary[] = {life, red_flame, bomb_destroy};

    char item;
    unsigned int item_rarity;
    unsigned int choice_item;
    int is_item = random_between(1,3);

    if(is_item == 1){
        item_rarity = random_between(1,100);

        if(item_rarity >= 50 && item_rarity <= 100){
            choice_item = random_between(0, items_len_rare-1);
            item = board->items[items_rarity[choice_item]]->data->_char;
        }else if(item_rarity >= 20 && item_rarity < 45){
            choice_item = random_between(0, items_len_epic-1);
            item = board->items[items_rarity_epic[choice_item]]->data->_char;
        }else {
            choice_item = random_between(0, items_len_leg-1);
            item = board->items[items_rarity_legendary[choice_item]]->data->_char;
        }
        map->body[x][y] = item;
    }
}



//Player *create_bot(Player *bot, int *index) {
//    char *bot_name[10] = {"Bob", "Fox", "Mewtwo", "Ritcher", "Rob", "Joker", "Bot", "Ricky", "Toto", "Test"};
//    int size = 10;
//    tab_mix(bot_name, size);
//    bot->name = bot_name[*index];
//    bot->is_bot = 1;
//    return bot;
//}
