
void clear_console();
DWORD WINAPI display_opening_credits();
void display_ending_credits(Board *board);

void display_board(Board *board);
void display_menu(Board *board, choices_index *choices);
void display_map(Board *board);

void display_menu_header(Board *board);
void display_player_turn(Board *board);
void display_player_infos(Board *board);

void _display_border(Board *board);
int _convert_item(char item, Board *board);


/* -------------------------------------------- */


void display_menu_header(Board *board) {
    printf("----------------------------------\n\n");
    printf("\t%s\n", board->menus[board->current_menu]->title);
    printf("\n----------------------------------\n\n");
}

void display_choice_back(Board *board, int index) {
    board->menus[board->current_menu]->nb_choice += 1;
    printf("[%c]\t%s\n", index == board->current_choice ? 'X' : ' ', file_get_value(CHOICES_NAME[choice_back], board->config->lang_dir));
}

void display_choice_continue(Board *board) {
    pause();
}


void display_next_menu(Board *board, menus_index next_menu, void (*pf)(Board *)) {
    clear_console();
    board->current_menu = next_menu;
    (*pf)(board);
}

void display_menu(Board *board, choices_index *choices) {
    display_menu_header(board);
    for (int i = 0; i < board->menus[board->current_menu]->nb_choice; ++i) {
        printf("[%c]\t%s\n", i == board->current_choice ? 'X' : ' ', file_get_value(CHOICES_NAME[choices[i]], board->config->lang_dir));
    }
}




void display_board(Board *board){
    clear_console();
    display_menu_header(board);
    display_player_turn(board);
    display_player_infos(board);
    display_map(board);
}



void display_map(Board *board) {
    _display_border(board);
    Map *map = board->maps[board->current_map];

    for (int i = 0; i < map->rows; ++i) {
        printf("\t");
        for (int j = 0; j < map->columns; ++j) {
            if(map->body[i][j] >= 48 && map->body[i][j] <= 57) {
                for (int k = 0; k < board->nb_player; ++k) {
                    if (map->body[i][j] == board->players[k]->id) {
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
    _display_border(board);
}

void display_player_turn(Board *board) {
    text_color(board->players[board->player_turn]->color);
    printf("  %s(%d), %s.\n", board->players[board->player_turn]->name, board->player_turn, board->lang[lang_your_turn]->str);
    text_color_default();
}

void display_player_infos(Board *board) {
    printf("%s : %d |", board->lang[lang_your_items]->str, board->players[board->player_turn]->nb_item);
    printf("%s : %d |", board->lang[lang_bomb_remaining]->str, board->players[board->player_turn]->nb_bomb);
    printf("%s : %d \n", board->lang[lang_life]->str, board->players[board->player_turn]->heart);
    for (int i = 0; i < board->players[board->player_turn]->nb_item; ++i) {
        printf("\t  -> %s, %c\n", board->players[board->player_turn]->items[i]->name, board->players[board->player_turn]->items[i]->data->_int);
    }
    printf("\n\n");
}

void _display_border(Board *board) {
    printf("\n\t\b\b");
    for (int i = 0; i < board->maps[board->current_map]->columns + 4; ++i) {
        printf("%c", i % 2 ? '-' : '=');
    }
    printf("\n");
}


int _convert_item(char item, Board *board) {
    for (int i = 0; i < items_len; ++i) {
        if(item == '\n') {
            return (int)' ';
        }
        if(item == 'p' || (item >= 48 && item <= 57) || item == ' ') {
            return item;
        }
        if(item == board->items[i]->data->_char) {
            return board->items[i]->data->_int;
        }
    }
    printf("[%c] <- ", item);
    errorf("Item char not found");
}


void display_ending_credits(Board *board) {
    clear_console();
    printf("%s\n", board->lang[lang_ending_opening]->str);
}


void display_wait(Board *board) {
    clear_console();
    printf("%s\n", board->lang[lang_loading]->str);
}


void display_loading(Loading *loading, int loading_index) {
//    loading->loading_item[loading_index]->item = 1;
//    clear_console();
//    for (int i = 0; i < loading_len; ++i) {
//        printf("[%s] %s\n", loading->loading_item[i]->item ? "OK" : "..", loading->loading_item[i]->name);
//    }
}

void display_default_map(Map *map, Board *board) {
    for (int i = 0; i < map->rows; ++i) {
        for (int j = 0; j < map->columns; ++j) {
            printf("%c", _convert_item(map->body[i][j], board));
        }
        printf("\n");
    }
}

void display_waiting_for_player(Board *board) {
    printf("%s...\n", board->lang[lang_loading_players]->str);
}


//
int _update_flowers(Flower *flower) {
    int random = random_between(0, flower->flowers_len + 1);
    if(flower->flowers[random] == flower->flower_steps[flower->flowers_steps_len - 1]) {
        return 0;
    }
    for (int i = 0; i < flower->flowers_steps_len - 1; ++i) {
        if(flower->flowers[random] == flower->flower_steps[i]) {
            flower->flowers[random] = flower->flower_steps[i + 1];
            return 1;
        }
    }
}

DWORD WINAPI _display_flower(Flower *flower) {
    clock_t begin = clock();
    double delta_ms = 0;
    
    while((int)delta_ms < 4250) {
        clock_t end = clock();
        delta_ms = ((double)(end - begin) / CLOCKS_PER_SEC * 1000000.0)/1000;

        _update_flowers(flower);
        usleep(3333);
    }
    return 0;
}



DWORD WINAPI display_opening_credits(int *wait) {
    Flower *flower = malloc(sizeof(Flower));
    int columns = 14;
    flower->flowers_len = 7 * columns;
    flower->flowers_steps_len = 3;
    flower->flower_steps[0] = '.';
    flower->flower_steps[1] = 'o';
    flower->flower_steps[2] = 'O';
    for (int i = 0; i < flower->flowers_len; ++i) {
        flower->flowers[i] = flower->flower_steps[0];
    }

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) _display_flower, flower, 0, NULL);

    clock_t begin = clock();
    double delta_ms = 0;
    flower->start = 1;
    while((int)delta_ms < 5000) {
        clock_t end = clock();
        delta_ms = ((double)(end - begin) / CLOCKS_PER_SEC * 1000000.0)/1000;

        if(_update_flowers(flower)) {
            clear_console();
            printf("Chargement...\n\n\t\t");
            for (int i = 1; i < flower->flowers_len; ++i) {
                printf("%c", flower->flowers[i]);
                if(i % columns == 0) {
                    printf("\n\t\t");
                }
            }
        } else {
            continue;
        }
        usleep(1000000.0 / 250.0);
    }
    free(flower);
    flower = NULL;
    *wait = 0;
    return 0;
}

