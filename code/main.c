#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "libs/game.utils.h"
#include "libs/display.utils.h"
#include "libs/misc.utils.h"
#include "libs/config.utils.h"


char *get_value(char *line) {
    if(strlen(line) <= 0) {
        return NULL;
    }

    char *temp = malloc(sizeof(char) * 255);
    for (int i = 0; i < strlen(line); ++i) {
        if(line[i] == '=') {
            i++;
            int index = 0;
            while (line[i] != '\n' && line[i] != '\0') {
                temp[index] = line[i];
                index++;
                i++;
            }
            temp[index] = '\0';
            break;
        }
    }
    return str_trim(temp);
}


int main() {

    FILE *file = fopen("../app.config", "r");
    char *line = malloc(sizeof(char) * 255);

    if(file != NULL) {
        char *attribute, *value;
        while (fgets(line, 255, file) != NULL) {
            attribute = _get_attribute(line);
            value = get_value(line);
            //printf("[%s] = [%s]\n", attribute, value);

            if(strcmp(attribute, "LANGUAGE") == 0) {
                const char *dir_lang = "../languages/";
                unsigned int len_lang = (strlen(dir_lang) + strlen(value));
                char *file_lang_name = malloc(sizeof(char) * (len_lang + 1));

                strcat(strcat(file_lang_name, dir_lang), value);

                Language lang = {NULL, NULL, NULL};
                FILE *file_lang = fopen(file_lang_name, "r");

                if(file_lang != NULL) {
                    while (fgets(line, 255, file_lang) != NULL) {
                        attribute = _get_attribute(line);
                        value = get_value(line);

                        //set
                        for (int i = 0; i < LANGUAGE_LENGTH; ++i) {
                            if(strcmp(attribute, "EXIT") == 0) {
                                lang.exit = malloc(sizeof(char) * strlen(value) + 1);
                                strcpy(lang.exit, value);
                                break;
                            } else if(strcmp(attribute, "START") == 0) {
                                lang.start = malloc(sizeof(char) * strlen(value) + 1);
                                strcpy(lang.start, value);
                                break;
                            } else if(strcmp(attribute, "OPTIONS") == 0) {
                                lang.options = malloc(sizeof(char) * strlen(value) + 1);
                                strcpy(lang.options, value);
                                break;
                            }
                        }
                    }
                    fclose(file_lang);
                    printf("%s %s %s", lang.exit, lang.start, lang.options);

                    //setdefault if not found
                    FILE *file_lang_default = fopen(LANGUAGE_DEFAULT, "r");

                    if(file_lang_default != NULL) {
                        while (fgets(line, 255, file_lang) != NULL) {
                            attribute = _get_attribute(line);
                            value = get_value(line);

                            //set
                            for (int i = 0; i < LANGUAGE_LENGTH; ++i) {
                                if(strcmp(attribute, "OPTIONS") == 0 && lang.options == NULL) {
                                    lang.options = malloc(sizeof(char) * strlen(value) + 1);
                                    strcpy(lang.options, value);
                                    break;
                                }
                            }
                        }
                        fclose(file_lang_default);

                        printf("%s %s %s", lang.exit, lang.start, lang.options);
                    }

                }
            }
        }

        fclose(file);
    }

    return 0;
}
