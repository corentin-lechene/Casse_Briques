
void clear_console();
void display_board(Board *board);


void display_board(Board *board){
    clear_console();
    //header
    unsigned short selected_map = board->selected_map;
    for (int i = 0; i < board->map[selected_map]->rows; ++i) {
        for (int j = 0; j < board->map[selected_map]->columns; ++j) {
            printf("%c", board->map[selected_map]->body[i][j]);
        }
        printf("\n");
    }
    //footer
}

void clear_console() {
    system("cls");
}