Board *generate_board();

void run_game(Board *board);
void run_menu(Board *board);

void menu_events(Board *board, int event);



void run_game(Board *board) {
    printf("RUN GAME");
}

void run_menu(Board *board) {
    int event = getch();
    menu_events(board, event);

    display_menus(board);

    if(board->selected_menu == IN_PLAYERS) {
//        board->players = get_players();
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

    Board *board = malloc(sizeof(Board));
    Config *config = malloc(sizeof(Config));

    config->language = malloc(sizeof(char) * 3);
    config->language = "FR";

    board->config = config;
    board->lang = get_lang(config->language);
    board->winner = malloc(sizeof(Player));
    board->players_turn = malloc(sizeof(Player));

    //    board->maps = get_maps();
    //    board->nb_map = get_nb_map(board->maps);

    //    unsigned short nb_map;          //le nombre de carte
    //    unsigned short nb_player;       //le nombre de joueur

    board->bo = 3;
    board->selected_menu = 1;
    board->selected_choice = 0;
    board->selected_map = 0;

    return board;
}