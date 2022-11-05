
Board *generate_board();

Loading *init_loading(Config *config);
Config *get_config();

Lang **get_langs(Config *config);
Item **get_items(Config *config);
Map **get_maps(Config *config);
Menu **get_menus(Config *config);


Item *_get_item(char *item_att, Config *config);
Map *_get_map(const char *filename);
Menu *_get_menu(const char *menu_name, Config *config);


/* GENERATE BOARD */

Board *generate_board() {
    Board *board = malloc(sizeof(Board));

    board->winner = NULL;

    board->nb_map = file_get_nb(MAP_DIR);
    board->nb_player = 0;

    if(board->nb_map == 0) {
        exit_error("0 map detected");
    }

    board->config = get_config();
    board->lang = get_langs(board->config);
    board->items = get_items(board->config);
    board->menus = get_menus(board->config);
    board->default_maps = get_maps(board->config);
    board->maps = NULL;
    board->players = NULL;

    board->current_map = board->nb_map;
    board->nb_selected_map = 0;

    board->bo = 3;
    board->current_menu = menu_home;
    board->current_choice = 0;
    board->player_turn = board->nb_player;
    board->selected_maps = NULL;

    return board;
}



Loading *init_loading(Config *config) {
    Loading *loading = malloc(sizeof(Loading));
    loading->loading_item = malloc(sizeof(Loading_item) * loading_len);

    for (int i = 0; i < loading_len; ++i) {
        loading->loading_item[i] = malloc(sizeof(Loading_item));
        loading->loading_item[i]->item = 0;
        loading->loading_item[i]->name = file_get_value(LOADING_NAME[i], config->lang_dir);
    }

    display_loading(loading, loading_init);
    return loading;
}
Config *get_config() {
    Config *config = malloc(sizeof(Config));

    config->language = file_get_value("language", CONFIG_DIR);
    if(config->language == NULL) {
        exit_error("config err, language = NULL");
    }

    config->lang_dir = str_cat(LANGUAGE_DIR, config->language);

    config->loading = init_loading(config);
    //et le reste de la config

    display_loading(config->loading, loading_config);
    return config;
}

Lang **get_langs(Config *config) {
    Lang **lang = malloc(sizeof(Lang *) * language_len);

    char *value;
    for (int i = 0; i < language_len; ++i) {
        lang[i] = malloc(sizeof(Lang));
        value = file_get_value(LANGUAGES_NAME[i], config->lang_dir);
        if(value == NULL) {
            warningf(str_cat(LANGUAGES_NAME[i], " est a NULL. Existe-il ?"));
            value = set_value("null");
        }
        lang[i]->str = value;
        lang[i]->str_len = strlen(value);
    }
    display_loading(config->loading, loading_language);
    return lang;
}
Item **get_items(Config *config) {
    Item **items = malloc(sizeof(Item *) * items_len);

    for (int i = 0; i < items_len; ++i) {
        items[i] = _get_item(ITEMS_NAME[i], config);
        if(items[i] == NULL) {
            exit_error("items[i] = NULL");
        }
    }
    display_loading(config->loading, loading_items);
    return items;
}
Map **get_maps(Config *config) { // tableau de map
    Map **maps = malloc(sizeof(Map *) * file_get_nb(MAP_DIR));

    DIR *d = opendir(MAP_DIR);
    if(d != NULL) {
        struct dirent *dir;
        char *path = NULL;

        int i = 1;
        while ((dir = readdir(d)) != NULL) {
            if(dir->d_name[0] != '.') {
                path = str_cat(MAP_DIR, str_cat("/", dir->d_name));
                maps[i - 1] = _get_map(path);

                if(maps[i - 1] == NULL) {
                    warningf("maps[i] = NULL\n");
                    continue;
                }
                i++;
            }
        }
        if(path != NULL) {
            free(path);
        }
        display_loading(config->loading, loading_menus);
        closedir(d);
        return maps;
    }
    exit_error("--== Dossier introuvable ==--");
}
Menu **get_menus(Config *config) {
    Menu **menus = malloc(sizeof(Menu *) * menus_len);

    for (int i = 0; i < menus_len; ++i) {
        menus[i] = _get_menu(MENUS_NAME[i], config);
        if(menus[i] == NULL) {
            exit_error("Menu[i] = NULL");
        }
    }
    menus[1]->next_menu = menu_game_mode;
    display_loading(config->loading, loading_menus);
    return menus;

}


Item *_get_item(char *item_att, Config *config) {
    Item *item = malloc(sizeof(Item));
    char *values = file_get_value(item_att, ITEM_DIR);

    if(values != NULL) {
        item->name = set_value(file_get_value(item_att, config->lang_dir));
        item->data = malloc(sizeof(Data_item));
        sscanf(values, "%d %c", &item->data->_int, &item->data->_char);
        free(values);
        return item;
    }
    return NULL;
}
Map *_get_map(const char *filename) {
    Map *map = malloc(sizeof(Map));

    FILE *f = fopen(filename, "r");
    if(f != NULL) {
        char t[255];
        int temp;

        //prevent space and \n
        while(!isalnum(fgetc(f)));
        fseek(f, -1, SEEK_CUR);

        //get nb_bomb
        fgets(t, 255, f);
        if(sscanf(t, "%hu %d", &map->nb_bomb, &temp) != 1 || map->nb_bomb == 0) {
            fclose(f);
            errorf("Map unrecognized (first line)");
        }

        //prevent space and \n
        while(!isalnum(fgetc(f)));
        fseek(f, -1, SEEK_CUR);

        //get columns and rows
        fgets(t, 255, f);
        if(sscanf(t, "%hu %hu %d", &map->columns, &map->rows, &temp) != 2) {
            fclose(f);
            errorf("Map unrecognized (second line)");
        }

        //size map
        if(map->rows < 6 || map->columns < 6) {
            fclose(f);
            errorf("rows min > 6, columns min > 6 (second line)");
        }

        //prevent space and \n
        temp = fgetc(f);
        while(temp == ' ' || temp == '\n') {
            temp= fgetc(f);
        }

        if(feof(f)) {
            fclose(f);
            errorf("Map unrecognized (map empty)");
        }

        map->body = malloc(sizeof(char *) * map->rows);
        for (int i = 0; i < map->rows; ++i) {
            map->body[i] = malloc(sizeof(char) * map->columns);
        }

        fseek(f, -1, SEEK_CUR);

        int i;
        for (i = 0; i < map->rows; ++i) {
            fgets(t, 255, f);
            if(feof(f)) {
                if(i + 1 != map->rows) {
                    i--;
                    break;
                }
            }
            strncpy(map->body[i], t, map->columns);
        }

        if(i + 1 < map->rows) {
            fclose(f);
            errorf("Map unrecognized (row size)");
        }

        temp = fgetc(f);
        while(temp == ' ' || temp == '\n') {
            temp= fgetc(f);
        }

        if(!feof(f)) {
            fclose(f);
            errorf("Map unrecognized (row size)");
        }


        map->bombs = malloc(sizeof(Bomb *));
        map->nb_bomb = 0;
        map->player_max = 0;
        for (int i = 0; i < map->rows; ++i) {
            for (int j = 0; j < map->columns; ++j) {
                if(map->body[i][j] == 'p') {
                    map->player_max += 1;
                }
            }
        }

        fclose(f);
        return map;
    }
    warningf("cant open file");
    free(map);
    return NULL;
}
Menu *_get_menu(const char *menu_name, Config *config) {
    Menu *menu = malloc(sizeof(menu));
    char *value = file_get_value(menu_name, config->lang_dir);

    if(value != NULL) {
        menu->title = value;
        menu->nb_choice = 1;
        return menu;
    }
    return NULL;
}


