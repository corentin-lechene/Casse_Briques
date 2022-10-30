
Board *generate_board();

Loading *get_loading();
Config *get_config(Loading *loading);

Lang **get_langs(Config *config, Loading *loading);
Item **get_items(Config *config, Loading *loading);
Map **get_maps(Config *config, Loading *loading);


Item *_get_item(char *item_att);
Map *_get_map(const char *filename);


/* GENERATE BOARD */

Board *generate_board() {
    Loading *loading = get_loading();
    display_loading(loading, loading_init);

    Board *board = malloc(sizeof(Board));

    board->winner = malloc(sizeof(Player));
    board->player_turn = malloc(sizeof(Player));

    board->config = get_config(loading);
    board->lang = get_langs(board->config, loading);
    board->items = get_items(board->config, loading);
    board->default_maps = get_maps(board->config, loading);
    board->maps = malloc(sizeof(Map));

//    board->nb_map = get_nb_map(board->maps);
    board->nb_map = 1;
    board->current_map = 0;
    board->nb_selected_map = 1;

    board->bo = 3;
    board->selected_menu = 1;
    board->selected_choice = 0;

    return board;
}



Loading *get_loading() {
    Loading *loading = malloc(sizeof(Loading));
    loading->loading_item = malloc(sizeof(Loading_item) * loading_len);

    char *value = file_get_value("language", CONFIG_DIR);
    char *lang_dir = str_cat(LANGUAGE_DIR, value);

    for (int i = 0; i < loading_len; ++i) {
        loading->loading_item[i] = malloc(sizeof(Loading_item));
        loading->loading_item[i]->item = 0;
        loading->loading_item[i]->name = file_get_value(LOADING_NAME[i], lang_dir);
    }
    free(lang_dir);
    free(value);
    return loading;
}
Config *get_config(Loading *loading) {
    Config *config = malloc(sizeof(Config));
    config->language = file_get_value("language", CONFIG_DIR);
    config->lang_dir = str_cat("language", LANGUAGE_DIR);
    //et le reste de la config

    if(config->language == NULL) {
        exit_error("language est à NULL");
    } else if(config->lang_dir == NULL) {
        exit_error("lang_dir est à NULL");
    }

    display_loading(loading, loading_config);
    return config;
}

Lang **get_langs(Config *config, Loading *loading) {
    Lang **lang = malloc(sizeof(Lang) * language_len);
    char *lang_value = file_get_value("language", CONFIG_DIR);
    char *lang_dir = str_cat(LANGUAGE_DIR, lang_value);

    char *value;
    for (int i = 0; i < language_len; ++i) {
        lang[i] = malloc(sizeof(Lang));
        value = file_get_value(LANGUAGES_NAME[i], lang_dir);
        if(value == NULL) {
            warningf(str_cat(LANGUAGES_NAME[i], " est a NULL. Existe-il ?"));
            value = set_value("null");
        }
        lang[i]->str = value;
        lang[i]->str_len = strlen(value);
    }
    free(value);
    display_loading(loading, loading_language);
    return lang;
}
Item **get_items(Config *config, Loading *loading) {
    Item **items = malloc(sizeof(Item) * items_len);

    for (int i = 0; i < items_len; ++i) {
        items[i] = _get_item(ITEMS_NAME[i]);
        if(items[i] == NULL) {
            exit_error("items[i] = NULL");
        }
    }
    display_loading(loading, loading_items);
    return items;
}
Map **get_maps(Config *config, Loading *loading) { // tableau de map
    Map **maps = malloc(sizeof(Map));
    struct dirent *dir;
    DIR *d = opendir(MAP_DIR);
    char *path;

    if (d != NULL) { // a verifier doc
        int i = 0;
        while ((dir = readdir(d)) != NULL) {
            if(isalpha(dir->d_name[0])) {
                path = str_cat(MAP_DIR, dir->d_name);
                maps = realloc(maps, sizeof(Map) * (i + 1)); // a voir sur le github ou prendre push
                maps[i] = _get_map(path);

                if(maps[i] == NULL) {
                    warningf("maps[i] = NULL\n");
                }
                i++;
                free(path);
            }
        }
        closedir(d);
        display_loading(loading, loading_maps);
        return maps;
    }
    exit_error("--== Dossier introuvable ==--");
}



Item *_get_item(char *item_att) {
    Item *item = malloc(sizeof(Item));
    char *values = file_get_value(item_att, ITEM_DIR);

    if(values != NULL) {
        item->data = malloc(sizeof(Data_item));
        sscanf(values, "%d %c", &item->data->_int, &item->data->_char);
        free(values);
        return item;
    }
    return NULL;
}
Map *_get_map(const char *filename) {
    Map *map = malloc(sizeof(Map));
    int index = 0;
    int numberPlayers = 0;

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return NULL;
    }
    fseek(f, 0, SEEK_SET); // replace le curseur au début du fichier
    while (!feof(f)) {
        int c = fgetc(f);
        if (index == 0) {
            map->bomb_default = c - 48; // index 0 49 - 48 = 1
        }
        if (index == 2) {
            map->columns = c - 48;    // index 2
        } else if (index == 4) {
            map->rows = c - 48;     // index 4
            map->body = malloc(sizeof(char *) * map->rows);
            for (int i = 0; i < map->rows; ++i) {
                map->body[i] = malloc(sizeof(char) * (map->columns + 1));
            }
        }
        if (index > 4) {
            for (int i = 0; i < map->rows; ++i) {
                for (int indexY = 0; indexY < map->columns + 1; ++indexY) {
                    int tmp = fgetc(f);
                    if (tmp == 'p') {
                        numberPlayers++;
                    }
                    map->body[i][indexY] = (char) tmp;
                }
            }
        }
        index++;
    }
    map->player_max = numberPlayers;
    fclose(f);
    return map;
}


