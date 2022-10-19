#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/game.utils.h"
#include "libs/display.utils.h"
#include "libs/misc.utils.h"
#include "libs/config.utils.h"

int main() {

    /*int tmp = 1;
    int cursor = 0;
    int selected_menu = 1;
    int has_move = 1;
    display_header();
    while(tmp != 0){
        tmp = display(&cursor, &selected_menu, &has_move);
    }*/

    int nb_real_player = 2;
    int nb_max = 4;
    int nb_added_player = 0;
    Board *board = calloc(1, sizeof(Board));
    board->players = malloc(sizeof (Player *)*nb_max);

    for(int i =0; i<nb_max; i++){
        push(board, create_player(&nb_added_player, &nb_real_player,&i), i);
    }

    for(int i =0; i<nb_max; i++){
        printf("\nPseudo => %s", board->players[i]->name);
        printf(" IsBot => %d", board->players[i]->is_bot);
        printf(" ID => %d", board->players[i]->id);
    }
    free(board->players);
    free(board);
    return 0;

/*Board *board = calloc(1, sizeof(Board));
board->lang = calloc(1, sizeof(Language));

FILE *file = fopen("../app.config", "r");
char *line = malloc(sizeof(char) * 255);

if(file != NULL) {
    char *attribute, *value;
    while (fgets(line, 255, file) != NULL) {
        attribute = _get_attribute(line);
        value = _get_value(line);
        //printf("[%s] = [%s]\n", attribute, value);

        if(strcmp(attribute, "LANGUAGE") == 0) {
            get_lang(board->lang, value);
        }
    }
    fclose(file);
    free(attribute);
    free(value);
}

printf("[%s] [%s] [%s]", board->lang->start, board->lang->bonjour, board->lang->options);
//fin du programme
free(line);
free(board->lang);
free(board);*/


}
