
void menu_home_case(Board *board);
void menu_options_case(Board *board);
void menu_languages_case(Board *board);
void menu_game_mode_case(Board *board);
void menu_solo_case(Board *board);
void menu_patch_notes_case(Board *board);
void menu_credits_case(Board *board);
void menu_maps_case(Board *board);
void menu_init_game_case(Board *board);
void menu_resume_case(Board *board);
void menu_players_case(Board *board);
void menu_game_case(Board *board);


void menu_home_case(Board *board) {
    menus_index next_menu[] = {menu_game_mode, menu_options, menu_patch_notes, menu_credits, menu_leave};
    choices_index choices_menu[] = {choice_play, choice_options, choice_patch_notes, choice_credits, choice_leave};

    board->menus[board->current_menu]->nb_choice = 5;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_options_case(Board *board) {
    menus_index next_menu[] = {menu_languages, menu_home};
    choices_index choices_menu[] = {choice_languages, choice_back};

    board->menus[board->current_menu]->nb_choice = 2;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_languages_case(Board *board) {
    struct dirent *dir;
    DIR *d = opendir(LANGUAGE_DIR);
    board->menus[board->current_menu]->next_menu = menu_options;

    if(d != NULL) {
        dir = readdir(d);
        while(!isalpha(dir->d_name[0])) {
            dir = readdir(d);
        }

        int i = 0;
        display_menu_header(board->menus[menu_languages]->title);
        while(dir != NULL) {
            printf("[%c]\t%s", board->current_choice == i++ ? 'X' : ' ', dir->d_name);
            printf("\t%s\n", strcmp(board->config->language, dir->d_name) == 0 ? "<--" : "");
            dir = readdir(d);
        }
        board->menus[board->current_menu]->nb_choice = i;
        display_choice_back(board, i);
        closedir(d);
        return;
    }
    board->current_menu = menu_options;
}

void menu_game_mode_case(Board *board) {
    menus_index next_menu[] = {menu_solo, menu_players, menu_online, menu_home};
    choices_index choices_menu[] = {choice_solo, choice_local, choice_online, choice_back};

    board->menus[board->current_menu]->nb_choice = 4;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_solo_case(Board *board) {
    board->nb_player = 1;
    create_players(board);

    board->current_menu = menu_maps;
    menu_maps_case(board);
}

void menu_patch_notes_case(Board *board) {
    if(!file_display_content(str_cat(PATCH_NOTES_DIR, board->config->language))) {
        board->current_menu = menu_home;
    } else {
        board->menus[board->current_menu]->next_menu = menu_home;
    }
}

void menu_credits_case(Board *board) {
    if(!file_display_content(str_cat(CREDITS_DIR, board->config->language))) {
        board->current_menu = menu_home;
    } else {
        board->menus[board->current_menu]->next_menu = menu_home;
    }
}

void menu_maps_case(Board *board) {
    get_maps_by_max_player(board);

    Menu *current_menu = board->menus[board->current_menu];
    current_menu->nb_choice = 3;
    short *new_selected_map = malloc(sizeof(short) * board->nb_selected_map);

    char q = 0;
    for (int i = 0; i < board->nb_selected_map; ++i) {
        do {
            clear_console();
            printf("Map %d/%d : \n\n", i + 1, board->nb_selected_map);

            printf("Voulez vous jouer sur cette carte ? \n\t- Oui: y\n\t- Non: n\n\t- %s q\n\n", i == 0 ? "Quitter" : "Retour");
            display_map(board->default_maps[board->selected_maps[i]], board->players);

            printf("Votre choix : ");
            fflush(stdin);
            scanf("%c", &q);
        } while(q != 'y' && q != 'n' && q != 'q');

        if(q == 'q' && i == 0) {
            break;
        } else if(q == 'y') {
            new_selected_map[i] = board->selected_maps[i];
        } else if(q == 'n') {
            new_selected_map[i] = -1;
        } else if(q == 'q' && i > 0) {
            new_selected_map[i - 1] = -1;
            i -= 2;
        }
    }

    if(q == 'q') {
        board->current_menu = menu_game_mode;
        clear_console();
        menu_game_mode_case(board);
        return;
    }

    int index = 0;
    for (int i = 0; i < board->nb_selected_map; ++i) {
        if(new_selected_map[i] != -1) {
            board->selected_maps[index++] = new_selected_map[i];
        }
    }

    if(index == 0) {
        board->current_menu = menu_game_mode;
        clear_console();
        menu_game_mode_case(board);
        return;
    }

    board->nb_selected_map = index;
    board->current_menu = menu_init_game;
}

void menu_reset_game_case(Board *board) {
    free_map_dim_arr(&board->maps, board->nb_selected_map);
    free_player_dim_arr(&board->players, board->nb_player);
    free_array((void **) &board->selected_maps, board->nb_selected_map);
    board->current_map = board->nb_map;
    board->nb_selected_map = 0;
    board->player_turn = board->nb_player;

    display_next_menu(board, menu_home, &menu_home_case);
}

void menu_resume_case(Board *board) {
    menus_index next_menu[] = {menu_game, menu_reset_game};
    choices_index choices_menu[] = {choice_continue, choice_leave};

    board->menus[board->current_menu]->nb_choice = 2;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_players_case(Board *board) {
    char q[3];
    do {
        clear_console();
        printf("Le nombre de joueur max est de 9\n");
        printf("Saisir le nombre de joueur (q pour quitter) : ");
        fflush(stdin);
        scanf("%s", q);
    } while(strcmp(q, "q") != 0 && !(atoi(q) > 1 && atoi(q) < 10));

    if(strcmp(q, "q") == 0) {
        clear_console();
        display_next_menu(board, menu_game_mode, &menu_game_mode_case);
        return;
    }
    board->nb_player = atoi(q);
    create_players(board);
    display_next_menu(board, menu_maps, &menu_maps_case);
}

