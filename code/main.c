#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <dirent.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include "libs/misc.utils.h"
#include "libs/free.utils.h"
#include "libs/functions.utils.h"
#include "libs/display.utils.h"
#include "libs/server.utils.h"
#include "libs/item.utils.h"
#include "libs/bomb.utils.h"
#include "libs/player.utils.h"
#include "libs/map.utils.h"
#include "libs/menu.utils.h"
#include "libs/game.utils.h"
#include "libs/config.utils.h"


void run_program(Board *board) {
    if(board->current_menu == menu_game) {
        run_game(board);
    } else if(board->current_menu == menu_init_game) {
        init_game(board);
    } else {
        run_menu(board);
    }
}



int main() {
    int wait = 1;

    srand( time( NULL ) );
    text_color_default();

//    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) display_opening_credits, &wait, 0, NULL);
    Board *board = generate_board();

//    while (wait) {}
//    clear_console();

    display_menus(board);
    while (board->current_menu >= 1) {
        run_program(board);
    }
    display_ending_credits();
    return 0;
}