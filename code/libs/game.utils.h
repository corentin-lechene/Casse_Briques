
void run_game(Board *board);
void run_menu(Board *board);
void init_game(Board *board);

void display_menus(Board *board);
void display_menu_static(Board *board);
void display_menu_custom(Board *board);

char *get_event(int event);
void put_item(Board *board);


Coord *is_something_proxy_verti(Player *player, Map *map, char search, int include_walls) {
    for (int i = 1; i <= player->bomb_range; ++i) {
//        printf("[%d] x: %d, y: %d -> [%c][%c]\n", include_walls, player->x - i, player->y, search, map->body[player->x - i][player->y]);
        if(player->x - i >= 0) {
            if(include_walls && (map->body[player->x - i][player->y] == 'x' || map->body[player->x - i][player->y] == 'm')) {
                break;
            }
            if(map->body[player->x - i][player->y] == search) {
                Coord *coord = malloc(sizeof(Coord));
                coord->x = player->x - i;
                coord->y = player->y;
                return coord;
            }
        }
    }

    for (int i = 1; i <= player->bomb_range; ++i) {
        if(player->x + i < map->rows) {
            if(include_walls && (map->body[player->x + i][player->y] == 'x' || map->body[player->x + i][player->y] == 'm')) {
                break;
            }
            if(map->body[player->x + i][player->y] == search) {
                Coord *coord = malloc(sizeof(Coord));
                coord->x = player->x + i;
                coord->y = player->y;
                return coord;
            }
        }
    }
    return NULL;
}
Coord *is_something_proxy_hori(Player *player, Map *map, char search, int include_walls) {
    for (int i = 1; i <= player->bomb_range; ++i) {
        if(player->y - i >= 0) {
            if(include_walls && (map->body[player->x][player->y - i] == 'x' || map->body[player->x][player->y - i] == 'm')) {
                break;
            }
            if(map->body[player->x][player->y - i] == search) {
                Coord *coord = malloc(sizeof(Coord));
                coord->x = player->x;
                coord->y = player->y - i;
                return coord;
            }
        }
    }

    for (int i = 1; i <= player->bomb_range; ++i) {
        if(player->y + i < map->columns) {
            if(include_walls && (map->body[player->x][player->y + i] == 'x' || map->body[player->x][player->y + i] == 'm')) {
                break;
            }
            if(map->body[player->x][player->y + i] == search) {
                Coord *coord = malloc(sizeof(Coord));
                coord->x = player->x;
                coord->y = player->y + i;
                return coord;
            }
        }
    }
    return NULL;
}
Coord *is_something_proxy_diag_top(Player *player, Map *map, char search, int include_walls) {
    for (int i = 1; i <= player->bomb_range; ++i) {
//        printf("[%d] x: %d, y: %d -> [%c][%c]\n", include_walls, player->x - i, player->y, search, map->body[player->x - i][player->y]);
        if(player->x - i >= 0 && player->y + i < map->columns) {
            if(include_walls && (map->body[player->x - i][player->y + i] == 'x' || map->body[player->x - i][player->y + i] == 'm')) {
                break;
            }
            if(map->body[player->x - i][player->y + i] == search) {
                Coord *coord = malloc(sizeof(Coord));
                coord->x = player->x - i;
                coord->y = player->y + i;
                return coord;
            }
        }
    }

    for (int i = 1; i <= player->bomb_range; ++i) {
        if(player->x - i >= 0 && player->y - i >= 0) {
            if(include_walls && (map->body[player->x - i][player->y - i] == 'x' || map->body[player->x - i][player->y - i] == 'm')) {
                break;
            }
            if(map->body[player->x - i][player->y - i] == search) {
                Coord *coord = malloc(sizeof(Coord));
                coord->x = player->x - i;
                coord->y = player->y - i;
                return coord;
            }
        }
    }
    return NULL;
}
Coord *is_something_proxy_diag_bottom(Player *player, Map *map, char search, int include_walls) {
    for (int i = 1; i <= player->bomb_range; ++i) {
//        printf("[%d] x: %d, y: %d -> [%c][%c]\n", include_walls, player->x - i, player->y, search, map->body[player->x - i][player->y]);
        if(player->x + i >= 0 && player->y - i >= 0) {
            if(include_walls && (map->body[player->x + i][player->y - i] == 'x' || map->body[player->x + i][player->y - i] == 'm')) {
                break;
            }
            if(map->body[player->x + i][player->y - i] == search) {
                Coord *coord = malloc(sizeof(Coord));
                coord->x = player->x + i;
                coord->y = player->y - i;
                return coord;
            }
        }
    }

    for (int i = 1; i <= player->bomb_range; ++i) {
        if(player->x + i < map->rows && player->y + i < map->columns) {
            if(include_walls && (map->body[player->x + i][player->y + i] == 'x' || map->body[player->x + i][player->y + i] == 'm')) {
                break;
            }
            if(map->body[player->x + i][player->y + i] == search) {
                Coord *coord = malloc(sizeof(Coord));
                coord->x = player->x + i;
                coord->y = player->y + i;
                return coord;
            }
        }
    }
    return NULL;
}


int is_bomb_proxi_hori(Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    int bombs[3] = {item_bomb,item_bomb_destroy,item_bomb_kick};

    for (int i = 0; i < 3; ++i) {
        if(is_something_proxy_hori(player, map, board->items[bombs[i]]->data->_char, 1) != NULL) {
            return 1;
        }
    }
    return 0;
}
int is_bomb_proxi_verti(Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    int bombs[3] = {item_bomb,item_bomb_destroy,item_bomb_kick};

    for (int i = 0; i < 3; ++i) {
        if(is_something_proxy_verti(player, map, board->items[bombs[i]]->data->_char, 1) != NULL) {
            return 1;
        }
    }
    return 0;
}

int is_bomb_on_player(Board *board) {
    
}

int is_bomb_proximity(Board *board) {
    return is_bomb_proxi_hori(board) || is_bomb_proxi_verti(board);
}
int is_player_proximity(Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    for (int i = 0; i < board->nb_player; ++i) {
        if(is_something_proxy_verti(player, map, board->players[i]->id, 0) != NULL || 
            is_something_proxy_hori(player, map, board->players[i]->id, 0) != NULL ||
            is_something_proxy_diag_top(player, map, board->players[i]->id, 0) != NULL ||
            is_something_proxy_diag_bottom(player, map, board->players[i]->id, 0) != NULL) {
            return 1;
        }
    }
    return 0;
}
int is_item_proximity(Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    int items[] = {item_bomb_up,
                   item_yellow_flame,
                   item_red_flame,
                   item_bomb_passes,
                   item_bomb_kick,
                   item_bomb_push,
                   item_invincibility,
                   item_heart,
                   item_life
    };

    for (int i = 0; i < 8; ++i) {
        if(is_something_proxy_hori(player, map, board->items[items[i]]->data->_char, 0) != NULL ||
            is_something_proxy_verti(player, map, board->items[items[i]]->data->_char, 0) != NULL ||
            is_something_proxy_diag_top(player, map, board->items[items[i]]->data->_char, 0) != NULL ||
            is_something_proxy_diag_bottom(player, map, board->items[items[i]]->data->_char, 0) != NULL) {
            return 1;
        }
    }
    return 0;
}
int is_desc_wall_proximity(Board *board) {
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    return is_something_proxy_verti(player, map, 'm', 0) != NULL ||
           is_something_proxy_hori(player, map, 'm', 0) != NULL;
}

int try_to_move(int direction, Board *board) {
    board->players[board->player_turn]->direction = direction;
    printf("Try to move %d\n", direction);
    return move_player(board);
}
void move_bot_by_coord(Coord *coord, Board *board) {
    int row = coord->y - board->players[board->player_turn]->y;
    int column = coord->x - board->players[board->player_turn]->x;
    if(row > 0) {
        //go bas
        if(!try_to_move(1, board)) {
            if(!try_to_move(0, board)) {
                try_to_move(2, board);
            }
        }
    } else if(row < 0) {
        //go up
        if(!try_to_move(3, board)) {
            if(!try_to_move(0, board)) {
                try_to_move(2, board);
            }
        }
    } else if(column > 0) {
        //go droite
        if(!try_to_move(2, board)) {
            if(!try_to_move(1, board)) {
                try_to_move(3, board);
            }
        }
    } else if(column < 0) {
        //go gauche
        if(!try_to_move(0, board)) {
            if(!try_to_move(1, board)) {
                try_to_move(3, board);
            }
        }
    }
}
void move_bot_unsafe(Board *board) {
    int row = is_bomb_proxi_hori(board);
    int column = is_bomb_proxi_verti(board);

    if(row && column) {
        if(!try_to_move(0, board)) {
            if(!try_to_move(1, board)) {
                if(!try_to_move(2, board)) {
                    try_to_move(3, board);
                };
            };
        };
    } else if(row) {
        if(!try_to_move(0, board)) {
            try_to_move(2, board);
        };
    } else {
        if(!try_to_move(1, board)) {
            try_to_move(3, board);
        };
    }
}
void move_bot_to_item(Board *board) {
    Coord *coord = malloc(sizeof(Coord));
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];
    int items[] = {item_bomb_up, item_yellow_flame, item_red_flame,
                   item_bomb_passes, item_bomb_kick, item_bomb_push,
                   item_invincibility, item_heart, item_life
    };

    //Récup coord
    for (int i = 0; i < 8; ++i) {
        coord = is_something_proxy_verti(player, map, board->items[items[i]]->data->_char, 0);
        if(coord != NULL) {
            break;
        }
        coord = is_something_proxy_hori(player, map, board->items[items[i]]->data->_char, 0);
        if(coord != NULL) {
            break;
        }
        coord = is_something_proxy_diag_top(player, map, board->items[items[i]]->data->_char, 0);
        if(coord != NULL) {
            break;
        }
        coord = is_something_proxy_diag_bottom(player, map, board->items[items[i]]->data->_char, 0);
        if(coord != NULL) {
            break;
        }
    }
    
    if(coord == NULL) {
        return;
    }

    printf("x: %d, y: %d <-> %d, %d\n", player->x, player->y, coord->x, coord->y);
    move_bot_by_coord(coord, board);
    free(coord);
}
void move_bot_to_wall(Board *board) {
    Coord *coord = malloc(sizeof(Coord));
    Map *map = board->maps[board->current_map];
    Player *player = board->players[board->player_turn];

    coord = is_something_proxy_verti(player, map, 'm', 0);
    if(coord == NULL) {
        coord = is_something_proxy_hori(player, map, 'm', 0);
        if(coord == NULL) {
            return;
        }
    }

    int row = coord->y - player->y;
    int column = coord->x - player->x;
    printf("x: %d, y: %d <-> %d, %d\n", player->x, player->y, coord->x, coord->y);
    
    if(row == 0 && (column == -1 || column == 1)) {
        printf("Plant bomb 1");
        pause();
    } else if(column == 0 && (row == -1 || row == 1)) {
        printf("Plant bomb 2");
        pause();
    } else {
        printf("move");
        pause();
        move_bot_by_coord(coord, board);
    }
    free(coord);
}

void move_bot(Board *board) {
    //not safe
    if(is_bomb_proximity(board)) {
        move_bot_unsafe(board);
        return;
    }
    //safe
    if(is_player_proximity(board)) {
//        plant_bomb(board)
    } else if(is_item_proximity(board)) {
        move_bot_to_item(board);
    } else if(is_desc_wall_proximity(board)) {
        move_bot_to_wall(board);
    }
}

/* ---------------------------------------- */

void run_game(Board *board) {
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
            move_player(board);
            display_board(board);
        } else if (strcmp(event_name, "bomb") == 0) {
            put_item(board);
//            if(plant_bomb(board)) {
//                  display_board(board);
//            }
        } else if (strcmp(event_name, "resume") == 0) {
            display_next_menu(board, menu_resume, &menu_resume_case);
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
void put_item(Board *board){
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
        map->body[1][1] = item;
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
