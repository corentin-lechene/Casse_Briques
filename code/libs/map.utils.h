int startsWith(const char *a, const char *b) {
    if (strncmp(a, b, strlen(b)) == 0) return 1;
    return 0;
}


Map *_get_map(const char *filename) {
    Map *map = malloc(sizeof(Map));
    int index = 0;
    int numberPlayers = 0;

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur dans l'ouverture du fichier");
        exit(1);
    }
    fseek(f, 0, SEEK_SET); // replace le curseur au début du fichier
    while (!feof(f)) {
        int c = fgetc(f);
        if (index == 0) {
            map->bomb_max = c - 48; // index 0 49 - 48 = 1
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


Map **get_maps(Loading *loading) { // tableau de map
    Map **maps = malloc(sizeof(Map));
    struct dirent *dir;
    DIR *d = opendir(MAP_DIR);
    char *path;

    if (d != NULL) { // a verifier doc
        int i = 0;
        while ((dir = readdir(d)) != NULL) {
            if (startsWith(dir->d_name, "map") == 1) {
                path = str_cat(MAP_DIR, dir->d_name);
                maps = realloc(maps, sizeof(Map) * (i + 1)); // a voir sur le github ou prendre push

                maps[i] = _get_map(path);
                i++;
                free(path);
            }
        }
        closedir(d);
    }
    display_loading(loading, loading_maps);
    return maps;
}

char **_copy_body(Map *src) {
    char **body = malloc(sizeof(char *) * src->rows);

    for (int i = 0; i < src->rows; ++i) {
        body[i] = malloc(sizeof(char) * src->columns);
    }

    for (int i = 0; i < src->rows; ++i) {
        for (int j = 0; j < src->columns; ++j) {
            body[i][j] = src->body[i][j];
        }
    }
    return body;
}

void copy_maps(Board *board) {
//    free(board->maps[0]->body);
    free(board->maps);

    board->maps = malloc(sizeof(Map) * board->nb_selected_map);
    board->selected_maps = malloc(sizeof(short));
    board->selected_maps[0] = 0;

    for (int i = 0; i < board->nb_selected_map; ++i) {
        board->maps[i] = malloc(sizeof(Map));
        unsigned short select_map = board->selected_maps[i];

//        board->maps[i]->id = board->default_maps[select_map]->id;
        board->maps[i]->rows = board->default_maps[select_map]->rows;
        board->maps[i]->columns = board->default_maps[select_map]->columns;
//        board->maps[i]->bomb_max = board->default_maps[select_map]->bomb_max;
//        board->maps[i]->player_max = board->default_maps[select_map]->player_max;
        board->maps[i]->body = _copy_body(board->default_maps[select_map]);
    }
//    display_map(board->maps[0]);
}