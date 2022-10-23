
char *_get_attribute(char *line);
char *_get_value(char *line);

void _set_lang_attribute(Language *lang, char *attribute, char *value);
Language *get_lang(char *language);

Map **get_maps();


Language *get_lang(char *language) {
    Language *lang = malloc(sizeof(Language));
    unsigned int len_lang = (strlen(LANGUAGE_DIR) + strlen(language));
    char file_lang_name[len_lang + 1];

    strcat(strcpy(file_lang_name, LANGUAGE_DIR), language);

    FILE *file_lang = fopen(file_lang_name, "r");
    char *line = malloc(sizeof(char) * 255);
    char *attribute, *value;

    if(file_lang != NULL) {
        while (fgets(line, 255, file_lang) != NULL) {
            attribute = _get_attribute(line);
            value = _get_value(line);

            _set_lang_attribute(lang, attribute, value);
        }
        fclose(file_lang);
        free(attribute);
        free(value);
    }
    return lang;
}
void _set_lang_attribute(Language *lang, char *attribute, char *value) {
    if(attribute == NULL) {
        return;
    }

    for (int i = 0; i < tab_length(LANGUAGE_ATTRIBUTES); ++i) {
        //func("EXIT", attribute);
        if(strcmp(attribute, "EXIT") == 0) {
            if(value == NULL) {
                printf("*Warning: value is NULL at %s\n", attribute);
                return;
            }
            lang->exit = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(lang->exit, value);
            return;
        } else if(strcmp(attribute, "START") == 0) {
            if(value == NULL) {
                printf("*Warning: value is NULL at %s\n", attribute);
                return;
            }
            lang->start = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(lang->start, value);
            return;
        } else if(strcmp(attribute, "CONFIGURATION") == 0) {
            if(value == NULL) {
                printf("*Warning: value is NULL at %s\n", attribute);
                return;
            }
            lang->configuration = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(lang->configuration, value);
            return;
        } else if(strcmp(attribute, "TITLE_MENU_START") == 0) {
            if (value == NULL) {
                printf("*Warning: value is NULL at %s\n", attribute);
                return;
            }
            lang->title_menu_start = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(lang->title_menu_start, value);
            return;
        }
    }
    printf("*Warning: attribute [%s] does not exist\n", attribute);
}

Map **get_maps() {
    Map **maps = malloc(sizeof(Map));
    return maps;
}


char *_get_attribute(char *line) {
    if(strlen(line) <= 0) {
        return NULL;
    }

    char *temp = malloc(sizeof(char) * 255);
    int i = 0;
    while (line[i] != '=') {
        if(line[i] == '\0' || line[i] == '\n') {
            break;
        }
        temp[i] = line[i];
        i++;
    }
    temp[i] = '\0';
    return str_trim(temp);
}
char *_get_value(char *line) {
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

