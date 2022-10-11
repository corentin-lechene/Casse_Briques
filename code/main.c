#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "libs/game.utils.h"
#include "libs/display.utils.h"
#include "libs/misc.utils.h"
#include "libs/config.utils.h"


int main() {

    //Board configuration

    //debut program


    display_start_menu();

    //fin program




    /*Board *board = calloc(1, sizeof(Board));
    board->lang = calloc(1, sizeof(Language));

    FILE *file = fopen("../app.config", "r");
    char *line = malloc(sizeof(char) * 255);

    if(file != NULL) {
        char *attribute, *value;
        while (fgets(line, 255, file) != NULL) {
            attribute = _get_attribute(line);
            value = _get_value(line);
            printf("[%s] = [%s]\n", attribute, value);

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

    return 0;
}
