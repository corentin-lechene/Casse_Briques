#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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
            printf("[%s] = [%s]\n", attribute, value);
        }

        fclose(file);
    }

    return 0;
}
