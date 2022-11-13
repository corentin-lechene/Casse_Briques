void run_game(Board *board);
void run_menu(Board *board);
void init_game(Board *board);

void display_menus(Board *board);
void display_menu_static(Board *board);
void display_menu_custom(Board *board);

char *get_event(int event);


int try_to_move(int direction, Board *board) {
    board->players[board->player_turn]->direction = direction;
    printf("Try to move %d\n", direction);
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
        printf("go droite au gauche");
        if(!try_to_move(0, board)) {
            if(!try_to_move(2, board)) {
                if(!try_to_move(1, board)) {
                    if(!try_to_move(3, board)) {
                        set_player_turn(board);
                    }
                };
            };
        };
    } else if(player->y - coord->y == 0) {
        printf("go haut ou bas");
        if(!try_to_move(1, board)) {
            if(!try_to_move(3, board)) {
                if(!try_to_move(0, board)) {
                    if(!try_to_move(2, board)) {
                        set_player_turn(board);
                    }
                };
            };
        };
    } else {
        try_to_move_anywhere(board);
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
    }
    decrement_bomb(board);
    explose_bombs(board);
}

/* ---------------------------------------- */

void run_game(Board *board) {
    players_are_dead(board);
    
    if(board->nb_player == 1) {
        display_next_menu(board, menu_winner_summary, &menu_winner_summary_case);
        return;
    }

    if(board->players[board->player_turn]->is_bot) {
        move_bot(board);
        display_board(board);
        return;
    }


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
        }else if (strcmp(event_name, "pass") == 0) {
            set_player_turn(board);
            display_board(board);
            return;
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
            return "bomb";

        case KEY_SPACE:
            return "pass";

        case KEY_ESCAPE:
            return "resume";

        default:
            return NULL;
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
