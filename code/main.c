#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <dirent.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include "libs/misc.utils.h"
#include "libs/free.utils.h"
#include "libs/functions.utils.h"
#include "libs/display.utils.h"
#include "libs/item.utils.h"
#include "libs/bomb.utils.h"
#include "libs/item.utils.h"
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
//    Bomb *bomb = malloc(sizeof(Bomb));
//    bomb->y = 1;
//    int i = 2;
//    printf("[%u][%d][%d][%d]", bomb->y - i, (bomb->y - i) >= 0,  bomb->y < 7, (bomb->y - i) >= 0 && bomb->y < 7);
//    die();
    text_color_default();
    Board *board = generate_board();
    display_opening_credits();
    display_menus(board);
    while (board->current_menu >= 1) {
        run_program(board);
    }
    display_ending_credits();
    return 0;
}