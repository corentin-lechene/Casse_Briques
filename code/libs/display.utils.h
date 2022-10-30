
void clear_console();
void display_opening_credits();
void display_ending_credits();

void display_menu_header(char *title);
void display_menu(Board *board, choices_index *choices);

void display_board(Board *board);
void display_map(Map *map);

void display_menu_carte(unsigned short *cursor,Board *board);
void _display_border(Board *board);
void _display_margin_y(Board *board);
void _display_margin_x();
void _display_content(Board *board);
void _display_items(int *item_index, Board *board);
int _get_char_ascii(char c);



/**
 * @features : display maps
 * */
void display_menu_carte(unsigned short *cursor,Board *board){
    clear_console();
    display_menu_header("CARTES");
    //printf("%d", board->selected_menu);
    for(int i = 0; i<1; i++){
        printf("\n");
       //printf("[%c]\n\n", i == *cursor ? 'X' : ' ');
        printf("[X]\n\n");
        display_map(board->maps[i]);
    }
}

void display_menu_header(char *title) {
    printf("----------------------------------\n\n");
    printf("\t%s\n", title);
    printf("\n----------------------------------\n\n");
}

void display_choice_back(Board *board, int index) {
    board->menus[board->current_menu]->nb_choice += 1;
    printf("[%c]\t%s\n", index == board->current_choice ? 'X' : ' ', file_get_value(CHOICES_NAME[choice_back], board->config->lang_dir));
}

void display_choice_yes(Board *board, int index) {
    board->menus[board->current_menu]->nb_choice += 1;
    printf("[%c]\t%s\n", index == board->current_choice ? 'X' : ' ', file_get_value(CHOICES_NAME[choice_yes], board->config->lang_dir));
}

void display_choice_no(Board *board, int index) {
    board->menus[board->current_menu]->nb_choice += 1;
    printf("[%c]\t%s\n", index == board->current_choice ? 'X' : ' ', file_get_value(CHOICES_NAME[choice_no], board->config->lang_dir));
}

void display_menu(Board *board, choices_index *choices) {
    display_menu_header(board->menus[board->current_menu]->title);
    for (int i = 0; i < board->menus[board->current_menu]->nb_choice; ++i) {
        printf("[%c]\t%s\n", i == board->current_choice ? 'X' : ' ', file_get_value(CHOICES_NAME[choices[i]], board->config->lang_dir));

    }
}

char test[6][8] = {
        "xxxxxxxx",
        "xp xmmmx",
        "x xmmx x",
        "x xmmx x",
        "xmmmx px",
        "xxxxxxxx",
};

char test2[6][15] = {
        "xxxxxxxxxxxxxxx",
        "xp xmmmx m xxxx",
        "x xmmx mm xxxxx",
        "xmmmx pxmmmxxxx",
        "x xmmx mm xxxxx",
        "xxxxxxxxxxxxxxx",
};

char test3[12][20] = {
        "xxxxxxxxxxxxxxxxxxxx",
        "xp xmmmx m mm mmmxxx",
        "x xmmx mm mmm  mmxxx",
        "xmmmx pxmmmx     xxx",
        "x xmmx mm xxxx  pxxx",
        "xxxxxxxxxxxxxxxxxxxx",
};




void display_board(Board *board){
    clear_console();

    _display_border(board);
    _display_margin_y(board);

    _display_content(board);

    _display_margin_y(board);
    _display_border(board);
}


int _get_char_ascii(char c) {
    int res = 0;
//    printf("[%c]", c);
//    sleep(1);
    switch (c) {
        case 'x':
            res = ITEM_MI;
            break;
        case 'm':
            res = ITEM_MD;
            break;
        case ' ':
            res = ITEM_SP;
            break;
        case 'p':
            res = 49;
            break;
        default:
            break;
    }
    return res;
}

void display_map(Map *map) {
    for (int i = 0; i < map->rows; ++i) {
        for (int j = 0; j < map->columns; ++j) {
//            printf("%c", _get_char_ascii(test[i][j]));
            printf("%c", map->body[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void _display_content(Board *board) {
    int item_index = 0;
    for (int i = 0; i < board->maps[board->current_map]->rows; ++i) {
        printf("|");
        _display_margin_x();
        for (int j = 0; j < board->maps[board->current_map]->columns; ++j) {
//            printf("%c", _get_char_ascii(test[i][j]));
            printf("%c", test[i][j]);
        }
        _display_margin_x();
        printf("|");
        _display_margin_x();
        _display_items(&item_index, board);
        _display_margin_x();
        printf("|\n");
    }
}

void _display_items(int *item_index, Board *board) {
    //todo récuperer l'objet le plus long
    for (int j = 0; j < items_len / 5; ++j) {
        if(*item_index < items_len) {
//            printf("%s : %s", ITEMS_NAME[*item_index], ITEMS_STRING[*item_index]);
            unsigned short offset = strlen(ITEMS_NAME[9]) - strlen(ITEMS_NAME[*item_index]);
            if(*item_index + 1 >= items_len) {
                offset += strlen(ITEMS_NAME[9]) + 4;
            }
            for (int i = 0; i < offset; ++i) {
                printf(" ");
            }
            *item_index += 1;
            if(j == items_len / 5 - 2) {
                _display_margin_x();
            }
        }
    }
}

void _display_margin_y(Board *board) {
    unsigned short column_map = board->maps[board->current_map]->columns;
    unsigned short len_board = MARGIN_X + column_map + MARGIN_X;
    unsigned short len_items = MARGIN_X + strlen(ITEMS_NAME[9]) + 4 + MARGIN_X + strlen(ITEMS_NAME[9]) + 4 + MARGIN_X;
    for (int j = 0; j < MARGIN_Y; ++j) {
        printf("|");
        for (int i = 0; i < len_board; ++i) {
            printf(" ");
        }
        printf("|");
        for (int i = 0; i < len_items; ++i) {
            printf(" ");
        }
        printf("|\n");
    }
}

void _display_margin_x() {
    for (int i = 0; i < MARGIN_X; ++i) {
        printf(" ");
    }
}

void _display_border(Board *board) {
    unsigned short column_map = board->maps[board->current_map]->columns;
    unsigned short len_board = 1 + MARGIN_X + column_map + MARGIN_X + 1;
    unsigned short len_items = MARGIN_X + strlen(ITEMS_NAME[9]) + 4 + MARGIN_X + strlen(ITEMS_NAME[9]) + 4 + MARGIN_X + 1;

    for (int i = 0; i < len_board + len_items; ++i) {
        printf("%c", i % 2 ? '-' : '=');
    }
    printf("\n");
}


void display_opening_credits() {
    clear_console();
    printf("Casse briques...");
}

void display_ending_credits() {
    clear_console();
    printf("Merci d'avoir jouer");
}




void display_loading(Loading *loading, int loading_index) {
    loading->loading_item[loading_index]->item = 1;
    clear_console();
    for (int i = 0; i < loading_len; ++i) {
        printf("[%s] %s\n", loading->loading_item[i]->item ? "OK" : "..", loading->loading_item[i]->name);
    }
}