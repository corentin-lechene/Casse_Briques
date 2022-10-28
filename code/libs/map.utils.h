int startsWith(const char * a, const char * b) {
    if (strncmp(a, b, strlen(b)) == 0) return 1;
    return 0;
}



void display_map(Map *map) {
    clear_console();
    for (int i = 0; i < map->rows; ++i) {
        for (int j = 0; j < map->columns; ++j) {
//            printf("%c", _get_char_ascii(test[i][j]));
            printf("%c", map->body[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Map *get_map(const char *filename) {
    Map *map = malloc(sizeof(Map));
    int index = 0;
    int numberPlayers = 0;

    FILE *f = fopen(filename, "r");
    if (f == NULL){
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
                map->body[i] = malloc(sizeof(char) * (map->columns +1));
            }
        }
        if (index > 4) {
            for (int i = 0; i < map->rows; ++i) {
                for (int indexY = 0; indexY < map->columns+1; ++indexY) {
                    int tmp = fgetc(f);
                    if (tmp == 'p'){
                        numberPlayers++;
                    }
                    //printf("%c", (char) tmp);
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

Map ** get_maps() { // tableau de map
    Map **maps = malloc(sizeof(Map));
    struct dirent * dir;
    DIR * d;
    d = opendir(MAP_DIR);
    char *path;
    if (d != NULL) { // a verifier doc
        int i = 0;
        while ((dir = readdir(d)) != NULL) {
            if (startsWith(dir -> d_name, "map") == 1) {
                path = str_cat(MAP_DIR, dir->d_name);
                printf("%s\n", path);    // ../configs/maps/map1   ../configs/maps/map2...
                maps = realloc(maps, sizeof(Map) * i); // a voir sur le github ou prendre push

                maps[i-1] = get_map(path);
                //display_map(maps[i]);


                i++;
                free(path);
            }
        }
        closedir(d);
    }
    return maps;
}