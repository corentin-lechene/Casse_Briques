#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "libs/game.utils.h"
#include "libs/display.utils.h"
#include "libs/misc.utils.h"
#include "libs/config.utils.h"


void set_lang_attribute(Language *lang, char *attribute, char *value) {
    for (int i = 0; i < LANGUAGE_LENGTH; ++i) {
        if(strcmp(attribute, "EXIT") == 0) {
            lang->exit = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(lang->exit, value);
            break;
        } else if(strcmp(attribute, "START") == 0) {
            lang->start = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(lang->start, value);
            break;
        } else if(strcmp(attribute, "OPTIONS") == 0) {
            lang->options = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(lang->options, value);
            break;
        }
    }
}

int main() {
    Board *board = calloc(1, sizeof(Board));
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
                unsigned int len_lang = (strlen(LANGUAGE_DIR) + strlen(value));
                char file_lang_name[len_lang + 1];

                strcat(strcpy(file_lang_name, LANGUAGE_DIR), value);

                FILE *file_lang = fopen(file_lang_name, "r");
                if(file_lang != NULL) {
                    while (fgets(line, 255, file_lang) != NULL) {
                        attribute = _get_attribute(line);
                        value = _get_value(line);

                        set_lang_attribute(board->lang, attribute, value);
                    }
                    fclose(file_lang);
                }
            }
        }
        free(attribute);
        free(value);
        fclose(file);
    }
    printf("%s %s %s", board->lang->exit, board->lang->start, board->lang->options);

    free(line);
    free(board->lang);
    free(board);

    return 0;
}
