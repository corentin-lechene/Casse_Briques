
void clear_console();
void display_intro();

void display_menus(Board *board);
void display_menu_header(char *title);
void display_menu(unsigned short *cursor, ...);

void display_board(Board *board);


void display_opening_credits() {
    clear_console();
    printf("Casse briques...");
}

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

void display_board(Board *board){
    clear_console();
    //header
    unsigned short selected_map = board->selected_map;
    for (int i = 0; i < board->maps[selected_map]->rows; ++i) {
        for (int j = 0; j < board->maps[selected_map]->columns; ++j) {
            printf("%c", board->maps[selected_map]->body[i][j]);
        }
        printf("\n");
    }
    //footer
}

void display_intro() {
    printf("Bienvenu\n");
}

void clear_console() {
    system("cls");
}