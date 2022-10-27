
char *_get_value_of_file(const char *attribute, const char *dir);
char *_get_attribute(char *line);
char *_get_value(char *line);

void _set_lang_attribute(Language *lang, char *attribute, char *value);

Config *get_config(Loading *loading);
Language *get_lang(Loading *loading);
Item **get_items(Loading *loading);
Map **get_maps(Loading *loading);



Config *get_config(Loading *loading) {
    Config *config = malloc(sizeof(Config));
    config->language = _get_value_of_file("language", CONFIG_DIR);
    //et le reste de la config

    if(config->language == NULL) {
        printf("Erreur dans la config");
        exit(0);
    }
    display_loading(loading, loading_config);
    return config;
}

Language *get_lang(Loading *loading) {
    Language *lang = malloc(sizeof(Language));
    char *lang_value = _get_value_of_file("language", CONFIG_DIR);
    char *lang_dir = str_cat(LANGUAGE_DIR, lang_value);

    FILE *file_lang = fopen(lang_dir, "r");
    char *line = malloc(sizeof(char) * 255);
    char *attribute, *value;

    if(file_lang != NULL) {
        while (fgets(line, 255, file_lang) != NULL) {
            attribute = _get_attribute(line);
            value = _get_value(line);
            ///fixme erreur
            if(value == NULL || attribute == NULL) {
                printf("Erreur dans les langues");
                exit(0);
            }
            _set_lang_attribute(lang, attribute, value);
        }
        fclose(file_lang);
        free(attribute);
        free(value);
        display_loading(loading, loading_language);
        return lang;
    }
    return NULL;
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
        } else if(strcmp(attribute, "OPTIONS") == 0) {
            if(value == NULL) {
                printf("*Warning: value is NULL at %s\n", attribute);
                return;
            }
            lang->options = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(lang->options, value);
            return;
        }
    }
///    printf("*Warning: attribute [%s] does not exist\n", attribute);
}


Item *_get_item(char *item_att) {
    Item *item = malloc(sizeof(Item));
    char *values = _get_value_of_file(item_att, ITEM_DIR);

    if(values != NULL) {
        sscanf(values, "%d %c", &item->_int, &item->_char);
        free(values);
        return item;
    }
    return NULL;
}

Item **get_items(Loading *loading) {
    Item **items = malloc(sizeof(Item) * items_len);

    for (int i = 0; i < items_len; ++i) {
        items[i] = _get_item(ITEMS_NAME[i]);
        if(items[i] == NULL) {
            printf("Erreur dans get_item()");
            exit(0);
        }
    }
    display_loading(loading, loading_items);
    return items;
}

Map **get_maps(Loading *loading) {
    Map **maps = malloc(sizeof(Map));
    display_loading(loading, loading_maps);
    return maps;
}

Loading *get_loading() {
    Loading *loading = malloc(sizeof(Loading));
    loading->loading_item = malloc(sizeof(Loading_item) * loading_len);
    loading->load_ended = 0;

    char *value = _get_value_of_file("language", CONFIG_DIR);
    char *lang_dir = str_cat(LANGUAGE_DIR, value);

    for (int i = 0; i < loading_len; ++i) {
        loading->loading_item[i] = malloc(sizeof(Loading_item));
        loading->loading_item[i]->item = 0;
        loading->loading_item[i]->name = _get_value_of_file(LOADING_NAME[i], lang_dir);
    }
    free(lang_dir);
    free(value);
    return loading;
}


char *_get_value_of_file(const char *attribute, const char *dir) {
    FILE *f = fopen(dir, "r");

    if(f != NULL) {
        char *line = malloc(sizeof(char) * 255);
        char *file_att, *file_value;

        while (fgets(line, 255, f) != NULL) {
            if(strcmp(line, "\n") == 0) {
                continue;
            }
            file_att = _get_attribute(line);
            file_value = _get_value(line);
            if(strcmp(attribute, file_att) == 0) {
                fclose(f);
                free(file_att);
                return file_value;
            }
        }
    }
    printf("-= FILE NOT FOUND =-\n");
    return NULL;
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

