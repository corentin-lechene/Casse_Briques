void run_game(Board *board);
void run_menu(Board *board);
void init_game(Board *board);

void display_menus(Board *board);
void display_menu_static(Board *board);
void display_menu_custom(Board *board);

char *get_event(int event);


int try_to_move(int direction, Board *board) {
    board->players[board->player_turn]->direction = direction;
    return move_player(board);
}
void try_to_move_anywhere(Board *board) {
    if(!try_to_move(0, board)) {
        if(!try_to_move(1, board)) {
            if(!try_to_move(2, board)) {
                if(!try_to_move(3, board)) {
                    set_player_turn(board);
                }
            }
        }
    }
}
void move_bot_by_coord(Coord *coord, Board *board) {
    if(coord == NULL) {
        return;
    }
    
    int row = coord->y - board->players[board->player_turn]->y;
    int column = coord->x - board->players[board->player_turn]->x;

    if(row > 0) {
        //go bas
        if(!try_to_move(1, board)) {
            if(!try_to_move(0, board)) {
                if(!try_to_move(2, board)) {
                    set_player_turn(board);
                }
            }
        }
    } else if(row < 0) {
        //go up
        if(!try_to_move(3, board)) {
            if(!try_to_move(0, board)) {
                if(!try_to_move(2, board)) {
                    set_player_turn(board);
                }
            }
        }
    } else if(column > 0) {
        //go droite
        if(!try_to_move(2, board)) {
            if(!try_to_move(1, board)) {
                if(!try_to_move(3, board)) {
                    set_player_turn(board);
                }
            }
        }
    } else if(column < 0) {
        //go gauche
        if(!try_to_move(0, board)) {
            if(!try_to_move(1, board)) {
                if(!try_to_move(3, board)) {
                    set_player_turn(board);
                }
            }
        }
    } else {
        set_player_turn(board);
    }
}
void move_bot_unsafe(Board *board) {
    Player *player = board->players[board->player_turn];
    Coord *coord = get_proximity_bombs(board);

    if(player->x - coord->x == 0) {
        if(!try_to_move(0, board)) {
            if(!try_to_move(2, board)) {
                if(!try_to_move(1, board)) {
                    if(!try_to_move(3, board)) {
                        if(!plant_bomb(board)) { 
                            set_player_turn(board); 
                        }
                    }
                };
            };
        };
    } else if(player->y - coord->y == 0) {
        if(!try_to_move(1, board)) {
            if(!try_to_move(3, board)) {
                if(!try_to_move(0, board)) {
                    if(!try_to_move(2, board)) {
                        if(!plant_bomb(board)) {
                            set_player_turn(board);
                        }
                    }
                };
            };
        };
    } else {
        int choice = random_between(0, 4);
        if(choice == 1) {
            plant_bomb(board);
        } else if(choice == 2) {
            try_to_move_anywhere(board);
            return;
        }
        set_player_turn(board);
    }
}

void move_bot(Board *board) {
    //not safe
    if(is_close_to("bombs", board)) {
        move_bot_unsafe(board);
        decrement_bomb(board);
        explose_bombs(board);
        return;
    }
    //safe
    if(is_close_to("players", board)) {
        if (plant_bomb(board)) {
            set_player_turn(board);
            return;
        } else {
            try_to_move_anywhere(board);
        }
    } else if(is_close_to("items", board)) {
        move_bot_by_coord(get_proximity_items(board), board);
    } else if(is_close_to("walls", board)) {
        Coord *coord = get_coord_of('m', board->players[board->player_turn]->bomb_range - 1, 0, board);
        if(coord != NULL && plant_bomb(board)) {
            set_player_turn(board);
            free(coord);
            return;
        } else {
            move_bot_by_coord(get_proximity_walls_desc(board), board);
        }
    } else {
        set_player_turn(board);
    }
    decrement_bomb(board);
    explose_bombs(board);
}
void move_player_real_time(Board *board) {
    if (kbhit()) {
        int event = my_getch();
        const char *event_name = get_event(event);

        if(event_name == NULL) {
            return;
        }

        if (strcmp(event_name, "move") == 0) {
            set_player_direction(event, board);
            if(move_player(board)) {
                decrement_bomb(board);
                explose_bombs(board);
                display_board(board);
            }
        } else if (strcmp(event_name, "bomb") == 0) {
            if(plant_bomb(board)){
                set_player_turn(board);
                display_board(board);
            }
        } else if (strcmp(event_name, "resume") == 0) {
            display_next_menu(board, menu_resume, &menu_resume_case);
            return;
        } else if (strcmp(event_name, "pass") == 0) {
            set_player_turn(board);
            decrement_bomb(board);
            explose_bombs(board);
            display_board(board);
            return;
        }
    }
}
int is_victory(Board *board) {
    players_are_dead(board);
    if(board->nb_player == 1) {
        display_next_menu(board, menu_winner_summary, &menu_winner_summary_case);
        return 1;
    }
    return 0;
}

/* ---------------------------------------- */


void run_game_local(Board *board) {
    if(is_victory(board)) {
        return;
    }

    //Plus de joueur réel
    int only_bot = 1;
    for (int i = 0; i < board->nb_player; ++i) {
        if(board->players[i]->is_bot == 0) {
            only_bot = 0;
        }
    }

    //si plus de joueur réel
    if(only_bot) {
        if(kbhit()) {
            //Finir le jeu
            int t = 0;
            while (board->nb_player > 1) {
                players_are_dead(board);
                move_bot(board);
                t++;
                if(t == 20000) {
                    break;
                }
            }
            display_next_menu(board, menu_winner_summary, &menu_winner_summary_case);
            return;
        } else {
            //Regarde le jeu
            move_bot(board);
            display_board(board);
            return;
        }
    }

    //Bouger les bots
    if(board->players[board->player_turn]->is_bot) {
        move_bot(board);
        display_board(board);
        return;
    }

    //Déplacement du joueur réel
    move_player_real_time(board);
}

void run_game(Board *board) {
    if(board->game_mode == GAME_MODE_LOCAL) {
        run_game_local(board);
    } else if(board->game_mode == GAME_MODE_HOST) {
        
    } else if(board->game_mode == GAME_MODE_CLIENT) {
        
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
    clear_console();
    display_wait();
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
        case menu_online:
            menu_online_case(board);
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
        case menu_host:
            menu_host_case(board);
            break;
        case menu_client:
            menu_client_case(board);
            break;
        case menu_wait_players:
            menu_wait_players_case(board);
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
            return "bomb";

        case KEY_SPACE:
            return "pass";

        case KEY_ESCAPE:
            return "resume";

        default:
            return NULL;
    }
}
