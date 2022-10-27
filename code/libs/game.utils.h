Board *generate_board();

void run_game(Board *board);
void run_menu(Board *board);

void menu_events(Board *board, int event);



void run_game(Board *board) {
    display_map(board->selected_maps[board->selected_map]);
}

void run_menu(Board *board) {
//    int event = getch();
    int event = 0;
    menu_events(board, event);

    display_menus(board);

    if(board->selected_menu == IN_PLAYERS) {
//        board->players = get_players(board->maps);
    } else if(board->selected_menu == IN_MAPS) {
//        board->selected_maps = get_selected_maps();
    } else if(board->selected_menu == IN_PAUSE) {
//        board->players = get_players();
    }
}

void menu_events(Board *board, int event) {
    switch (event) {
        case CROSS_TOP:
        case KEY_z:
            if (board->selected_choice - 1 >= 0) {
                board->selected_choice -= 1;
            }
            break;
        case CROSS_BOTTOM:
        case KEY_s:
            board->selected_choice += 1;
            break;
        case KEY_ENTER:
            if(board->selected_menu == 1 && board->selected_choice == 2){
                board->selected_menu = 0;
            } else if ((board->selected_menu == 2 && board->selected_choice == 3) ||
                       (board->selected_menu == 3 && board->selected_choice == 3)) {
                board->selected_menu -= 1;
            } else if (board->selected_menu == 4 && board->selected_choice == 2) {
                board->selected_menu = 2;
            } else if (board->selected_menu == 2 && board->selected_choice == 2) {
                board->selected_menu = 4;
            } else {
                if (board->selected_menu + 1 < 5) {
                    board->selected_menu += 1;
                }
            }
            break;
        default:
            break;
    }
}

Board *generate_board() {
    Loading *loading = get_loading();
    display_loading(loading, loading_init);

    Board *board = malloc(sizeof(Board));

    board->bo = 3;
    board->selected_menu = 10;
    board->selected_choice = 0;
    board->selected_map = 0;

    board->winner = malloc(sizeof(Player));
    board->player_turn = malloc(sizeof(Player));

    board->config = get_config(loading);
    board->lang = get_langs(loading);
    board->items = get_items(loading);
    board->maps = get_maps(loading);

    return board;
}