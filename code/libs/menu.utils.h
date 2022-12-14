
void menu_home_case(Board *board);
void menu_options_case(Board *board);
void menu_languages_case(Board *board);
void menu_set_languages_case(Board *board);
void menu_game_mode_case(Board *board);
void menu_online_case(Board *board);
void menu_host_case(Board *board);
void menu_client_case(Board *board);
void menu_wait_players_case(Board *board);
void menu_solo_case(Board *board);
void menu_patch_notes_case(Board *board);
void menu_credits_case(Board *board);
void menu_maps_case(Board *board);
void menu_resume_case(Board *board);
void menu_players_case(Board *board);
void menu_winner_summary_case(Board *board);


void menu_home_case(Board *board) {
    menus_index next_menu[] = {menu_game_mode, menu_options, menu_patch_notes, menu_credits, menu_leave};
    choices_index choices_menu[] = {choice_play, choice_options, choice_patch_notes, choice_credits, choice_leave};

    board->menus[board->current_menu]->nb_choice = 5;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    free_map_dim_arr(&board->maps, board->nb_selected_map);
    free_player_dim_arr(&board->players, board->nb_player);

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
        while(dir->d_name[0] == '.') {
            dir = readdir(d);
        }

        int i = 0;
        display_menu_header(board);
        while(dir != NULL) {
            printf("[%c]\t%s\n", board->current_choice == i ? 'X' : ' ', dir->d_name);

            if(board->current_choice == i) {
                board->config->language = set_value(dir->d_name);
                board->menus[board->current_menu]->next_menu = menu_set_languages;
            }
            i++;
            dir = readdir(d);
        }
        board->menus[board->current_menu]->nb_choice = i;
        if(board->current_choice == i) {
            board->menus[board->current_menu]->next_menu = menu_options;
            board->config->language = file_get_value("language", CONFIG_DIR);
        }
        display_choice_back(board, i);
        closedir(d);
        return;
    }
    board->current_menu = menu_options;
}

void menu_set_languages_case(Board *board) {
    file_set_value("language", board->config->language, CONFIG_DIR);
    infof("Le jeu doit redemarrer");
    pause();
    exit(0);
}

void menu_game_mode_case(Board *board) {
    board->nb_map = board->nb_default_map;
    menus_index next_menu[] = {menu_solo, menu_players, menu_online, menu_home};
    choices_index choices_menu[] = {choice_solo, choice_local, choice_online, choice_back};

    board->menus[board->current_menu]->nb_choice = 4;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_solo_case(Board *board) {
    board->game_mode = GAME_MODE_LOCAL;

    board->nb_player = 1;
    if(create_players(board)) {
        board->current_menu = menu_maps;
        menu_maps_case(board);
    }
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
            display_menu_header(board);
            printf("Map %d/%d : \n\n", i + 1, board->nb_selected_map);
            printf("%s ?\n", board->lang[lang_play_with_this_map]->str);
            printf("\t - %s: y\n", board->lang[lang_yes]->str);
            printf("\t - %s: n\n", board->lang[lang_no]->str);
            printf("\t - %s: q\n\n", board->lang[lang_leave]->str);
            
            display_default_map(board->default_maps[board->selected_maps[i]], board);

            printf("%s :", board->lang[lang_your_choice]->str);
            fflush(stdin);
            scanf("%c", &q);
            display_wait(board);
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
        if(board->game_mode == GAME_MODE_HOST) {
            send_leave(board);
        }
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
    free(board->selected_maps);
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
    board->game_mode = GAME_MODE_LOCAL;

    char q[3];
    do {
        clear_console();
        display_menu_header(board);
        text_color(color_light_blue);
        printf("%s 9 ", board->lang[lang_max_player]->str);
        printf("%s (q: %s)\n", board->lang[lang_enter_number_of_player]->str, board->lang[lang_leave]->str);
        text_color_default();
        printf("%s :", board->lang[lang_your_choice]->str);
        fflush(stdin);
        scanf("%s", q);
    } while(strcmp(q, "q") != 0 && !(atoi(q) > 1 && atoi(q) < 10));

    if(strcmp(q, "q") == 0) {
        clear_console();
        display_next_menu(board, menu_game_mode, &menu_game_mode_case);
        return;
    }
    
    board->nb_player = atoi(q);
    if(create_players(board)) {
        display_next_menu(board, menu_maps, &menu_maps_case);
    }
}

void menu_winner_summary_case(Board *board) {
    display_menu_header(board);
    printf("%s, %s\n", board->players[0]->name, board->lang[lang_you_won]->str);
    short min = board->maps[0]->player_max;
    for (int i = 0; i < board->nb_map; ++i) {
        if(board->maps[i]->player_max < min) {
            min = board->maps[i]->player_max;
        }
    }
    for (int i = 1; i < min; ++i) {
        if(board->game_mode == GAME_MODE_HOST && i == 2) {
            break;
        }
        printf("%s (%d eme), %s\n", board->players[i]->name, i + 1, board->lang[lang_sad]->str);
    }
    display_choice_continue(board);
    
    board->nb_player = board->game_mode == GAME_MODE_LOCAL ? min : 2;
    board->current_menu = menu_init_game;
}

void menu_online_case(Board *board) {
    menus_index next_menu[] = {menu_host, menu_client, menu_game_mode};
    choices_index choices_menu[] = {choice_create_server, choice_join_server, choice_back};

    board->menus[board->current_menu]->nb_choice = 3;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_host_case(Board *board) {
    board->game_mode = GAME_MODE_HOST;
    board->nb_player = 2;
    if(create_players(board)) {
        clear_console();
        display_menu_header(board);
        infof("Creation du serveur en cours...");
        if(create_server(board)) {
            infof("Serveur cree");
            display_next_menu(board, menu_wait_players, &menu_wait_players_case);
        } else {
            errorf("Impossible de creer le serveur");
        }
    } else {
        errorf("Impossible de creer les joueurs");
        display_next_menu(board, menu_game_mode, &menu_game_mode_case);
    }
}

void menu_wait_players_case(Board *board) {
    clear_console();
    display_menu_header(board);

    if(board->game_mode == GAME_MODE_HOST) {
        text_color(color_light_blue);
        printf("[INFO]-> %s : \n", board->lang[lang_your_info_connexion]->str);
        printf("\t%s: %s\n", board->lang[lang_ip]->str, board->server->ip);
        printf("\t%s: %d\n", board->lang[lang_port]->str, PORT);
        text_color_default();
        display_waiting_for_player(board);
        if(is_player_join(board)) {
            display_next_menu(board, menu_maps, &menu_maps_case);
        }
    } else {
        infof(board->lang[lang_player_set_maps]->str);
        display_waiting_for_player(board);
        printf("%s...\n", board->lang[lang_loading]->str);
        if(game_is_started(board)) {
            board->nb_player = 2;
            board->player_turn = PLAYER_ID_HOST;
            board->current_menu = menu_game;
            board->players = malloc(sizeof(Player *) * 2);
            board->players[0] = malloc(sizeof(Player));
            board->players[0]->id = PLAYER_ID_HOST;
            board->players[0]->color = color_green;
            board->players[1] = malloc(sizeof(Player));
            board->players[1]->id = PLAYER_ID_CLIENT;
            board->players[1]->color = color_cyan;

            clear_console();
            display_menu_header(board);
            Map *map = get_decoded_map(board->client->recv_buf);
            for (int i = 0; i < map->rows; ++i) {
                for (int j = 0; j < map->columns; ++j) {
                    if(map->body[i][j] == '0' || map->body[i][j] == '1') {
                        for (int k = 0; k < board->nb_player; ++k) {
                            if (map->body[i][j] == board->players[k]->id + 48) {
                                text_color(board->players[k]->color);
                                printf("%c", map->body[i][j]);
                                text_color_default();
                                break;
                            }
                        }
                    } else {
                        printf("%c", _convert_item(map->body[i][j], board));
                    }
                }
                printf("\n");
            }
        } else {
            display_next_menu(board, menu_home, &menu_home_case);
        }
    }
}

void menu_client_case(Board *board) {
    board->game_mode = GAME_MODE_CLIENT;

    char port[10];
    int client_connected = 0;
    int count = 0, count_ip = 0, count_port = 0;
    char ip[30];
    
    
    do {
        clear_console();
        count_ip = 0;
        count_port = 0;
        
        if(count > 0) {
            text_color(color_red);
            printf("Error-> %s.\n\n", board->lang[lang_error_connexion]->str);
            text_color_default();
        }
        
        do {
            if(count_ip > 0) {
                clear_console();
                text_color(color_red);
                printf("Error-> %s.\n", board->lang[lang_ip_incorrect]->str);
                text_color_default();
            }
            
            infof("Example %s : 192.168.1.18");
            printf("%s %s (q: %s) : ", board->lang[lang_enter]->str, board->lang[lang_ip]->str, board->lang[lang_leave]->str);
            fflush(stdin);
            scanf("%s", ip);
            count_ip++;
            if(strcmp(ip, "q") == 0) {
                display_next_menu(board, menu_online, &menu_online_case);
                return;
            }
        } while(!(strlen(ip) > 8 && strlen(ip) <= 15));
        
        do {
            clear_console();
            if(count_port > 0) {
                text_color(color_red);
                printf("Erreur-> %s.\n", board->lang[lang_port_incorrect]->str);
                text_color_default();
            }

            infof("Exemple : 27015");
            printf("%s %s (q : %s): ", board->lang[lang_enter]->str, board->lang[lang_port]->str, board->lang[lang_leave]->str);
            fflush(stdin);
            scanf("%s", port);
            if(strcmp(port, "q") == 0) {
                display_next_menu(board, menu_online, &menu_online_case);
                return;
            }
            count_port++;
        } while(strlen(port) != 5);

        if(join_server(ip, port, board) != SOCKET_ERROR) {
            client_connected = 1;
            infof("\n\nConnexion r??ussite...");
        }
        count++;
    } while(client_connected == 0);

    display_next_menu(board, menu_wait_players, &menu_wait_players_case);
}


