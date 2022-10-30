int startsWith(const char *a, const char *b) {
    if (strncmp(a, b, strlen(b)) == 0) return 1;
    return 0;
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