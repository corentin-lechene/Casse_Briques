
void clear_console();
void display_opening_credits();
void display_ending_credits();

void display_menus(Board *board);
void display_menu_header(char *title);
void display_menu(unsigned short *cursor, ...);

void display_board(Board *board);

void _display_border(Board *board);
void _display_margin_y(Board *board);
void _display_margin_x();
void _display_content(Board *board);
void _display_items(int item_index);
int _get_char_ascii(char c);



void display_menus(Board *board) {
    switch (board->selected_menu) {
        case 1 :
            display_menu(&board->selected_choice,"MENU PRINCIPAL","Jouer","Configuration","Quitter", NULL);
            break;
        case 2 :
            display_menu(&board->selected_choice,"MODE DE JEU","Jouer contre l'ordinateur","Jouer en Local","Jouer en Ligne","Retour", NULL);
            break;
        case 3 :
            display_menu(&board->selected_choice, "CARTES"," "," "," ","Retour", NULL);
            break;
        case 4 :
            display_menu(&board->selected_choice, "EN LIGNE","Demarrer un serveur","Rejoindre un serveur","Retour", NULL);
            break;
        case 11 :
            display_menu(&board->selected_choice, "Reprendre", "Quitter", NULL);
            break;
        default:
            break;
    }
}

void display_menu_header(char *title) {
    printf("----------------------------------\n\n");
    printf("\t%s\n", title);
    printf("\n----------------------------------\n\n");
}

void display_menu(unsigned short *cursor, ...) {
    clear_console();
    va_list ap, temp;
    va_start(ap, cursor);
    temp = ap;
    int i = 0;
    while (va_arg(ap, char* ) != NULL) {
        i++;
    }
    va_end(ap);
    if(*cursor >= i-1) {
        *cursor = i-2;
    }

    va_start(temp, cursor);
    char *arg = va_arg(temp, char* );
    display_menu_header(arg);
    arg = va_arg(temp, char*);
    for (int j = 0; j < i-1; ++j) {
        printf("[%c] %s\n\n", j == *cursor ? 'X' : ' ', arg);
        arg = va_arg(temp, char*);
    }
    va_end(temp);

}

char test[5][8] = {
        "xxxxxxxx",
        "xp xmmmx",
        "x xmmx x",
        "xmmmx px",
        "xxxxxxxx",
};

char test2[5][15] = {
        "xxxxxxxxxxxxxxx",
        "xp xmmmx m xxxx",
        "x xmmx mm xxxxx",
        "xmmmx pxmmmxxxx",
        "xxxxxxxxxxxxxxx",
};

void display_board(Board *board){
    clear_console();
    //header
//    unsigned short selected_map = board->selected_map;
//    for (int i = 0; i < board->maps[selected_map]->rows; ++i) {
//        for (int j = 0; j < board->maps[selected_map]->columns; ++j) {
//            printf("%c", _get_char_ascii(board->maps[selected_map]->body[i][j]));
//        }
//        printf("\n");
//    }


//    _display_border(board);
//    _display_margin_y(board);
//
//    _display_content(board);
//
//    _display_margin_y(board);
//    _display_border(board);


    //border top
    for (int i = 0; i < 8 + 10 + strlen("  Bombe █  |") - 2; ++i) {
        printf("%c", i % 2 ? '-' : '=');
    }
    printf("\n");

    //margin top
    printf("|");
    for (int i = 0; i < 8 + 10 - 2; ++i) {
        printf(" ");
    }
    printf("|");
    for (int i = 0; i < strlen("  Bombe █  |") - 3; ++i) {
        printf(" ");
    }
    printf("|");
    printf("\n");


    //content
    for (int i = 0; i < 5; ++i) {
        printf("|    ");
        for (int j = 0; j < 8; ++j) {
            printf("%c", test[i][j]);
        }
        printf("    |");
        printf("  Bombe █  |");
        printf("\n");
    }


    //margin top
    printf("|");
    for (int i = 0; i < 8 + 10 - 2; ++i) {
        printf(" ");
    }
    printf("|");
    for (int i = 0; i < strlen("  Bombe █  |") - 3; ++i) {
        printf(" ");
    }
    printf("|");
    printf("\n");


    //border top
    for (int i = 0; i < 8 + 10 + strlen("  Bombe █  |") - 2; ++i) {
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

void clear_console() {
    system("cls");
//    printf("\033[2J\033[1;1H");
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

void _display_content(Board *board) {
    int item_index = 0;
    for (int i = 0; i < board->selected_maps[board->selected_map]->rows; ++i) {
        printf("|");
        _display_margin_x();
        for (int j = 0; j < board->selected_maps[board->selected_map]->columns; ++j) {
            printf("%c", _get_char_ascii(test[i][j]));
        }
        _display_margin_x();
        printf("|");
        _display_margin_x();
        _display_items(item_index++);
        _display_margin_x();
        printf("|\n");
    }
}

void _display_items(int item_index) {
    if(item_index <= 10) {
        printf("%s : %s", ITEMS_NAME[item_index], ITEMS_STRING[item_index]);
    }
}

void _display_margin_y(Board *board) {
    unsigned short len_board = board->selected_maps[board->selected_map]->columns + (MARGIN_X * 2);
    unsigned short len_items = (MARGIN_X * 2) + strlen(ITEMS_NAME[8]);
    for (int j = 0; j < MARGIN_Y; ++j) {
        printf("|");
        for (int i = 0; i < len_board - 1; ++i) {
            printf(" ");
        }
        printf("|");

        for (int i = 0; i < len_items - 1; ++i) {
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
    unsigned short len = board->selected_maps[board->selected_map]->columns + (MARGIN_X * 4) + strlen(ITEMS_NAME[8]) + 2;
    printf("\n");
    for (int i = 0; i < len; ++i) {
        printf("%c", i % 2 ? '-' : '=');
    }
    printf("\n");
}