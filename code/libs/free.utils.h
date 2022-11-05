
void free_board(Board **tf);

void free_config(Config **tf, int len_loading);
void free_loading(Loading **tf, int len);
void _free_loading_item_dim_arr(Loading_item ***tf, int len);
void _free_loading_item_array(Loading_item **tf, int len);

void free_lang_dim_arr(Lang ***tf, int len);
void _free_lang_array(Lang **tf, int len);

void free_bomb_dim_arr(Bomb ***tf, int len);
void _free_bomb_array(Bomb **tf, int len);

void free_item_dim_arr(Item ***tf, int len);
void _free_item_array(Item **tf, int len);

void free_menu_dim_arr(Menu ***tf, int len);
void _free_menu_array(Menu **tf, int len);

void free_map_dim_arr(Map ***tf, int len);
void _free_map_array(Map **tf, int len);

void free_player_dim_arr(Player ***tf, int len);
void _free_player_array(Player **tf, int len);

void free_char_dim_arr(char ***tf, int len);
void free_int_dim_arr(int ***tf, int len);
void free_short_dim_arr(short ***tf, int len);


void free_array(void **tf, int len);
void _free(void **tf);

/* ----------------------- */

void free_board(Board **tf) {
    if(*tf != NULL) {
        free_config(&(*tf)->config, loading_len);

//        free_lang_dim_arr(&(*tf)->lang, language_len);

        free_item_dim_arr(&(*tf)->items, items_len);
        free_menu_dim_arr(&(*tf)->menus, menus_len);

        free_map_dim_arr(&(*tf)->default_maps, (*tf)->nb_map);
//        free_map_dim_arr(&(*tf)->maps, (*tf)->nb_selected_map);

//        free_player_dim_arr(&(*tf)->players, (*tf)->nb_player);
//        _free((void *) (*tf)->winner);

//        _free_array((void **) &(*tf)->selected_maps, (*tf)->nb_selected_map);
        *tf = NULL;
    }
}

void free_config(Config **tf, int len_loading) {
    if(*tf != NULL) {
        free_loading(&(*tf)->loading, len_loading);
        _free((void **) &(*tf)->lang_dir);
        _free((void **) &(*tf)->language);
        *tf = NULL;
    }
}
void free_loading(Loading **tf, int len) {
    if(*tf != NULL) {
        _free_loading_item_dim_arr(&(*tf)->loading_item, len);
        _free((void *) *tf);
        *tf = NULL;
    }
}
void _free_loading_item_dim_arr(Loading_item ***tf, int len) {
    if(*tf != NULL) {
        _free_loading_item_array(*tf, len);
        *tf = NULL;
    }
}
void _free_loading_item_array(Loading_item **tf, int len) {
    for (int i = 0; i < len; ++i) {
        if(tf[i] != NULL) {
            _free((void **) &tf[i]->name);
            free(tf[i]);
            tf[i] = NULL;
        }
    }
}

void free_lang_dim_arr(Lang ***tf, int len) {
    if(*tf != NULL) {
        _free_lang_array(*tf, len);
        *tf = NULL;
    }
}
void _free_lang_array(Lang **tf, int len) {
    for (int i = 0; i < len; ++i) {
        if(tf[i] != NULL) {
            _free((void **) &tf[i]->str);
            free(tf[i]);
            tf[i] = NULL;
        }
    }
}

void free_bomb_dim_arr(Bomb ***tf, int len) {
    if(*tf != NULL) {
        _free_bomb_array(*tf, len);
        *tf = NULL;
    }
}
void _free_bomb_array(Bomb **tf, int len) {
    printf("[%c]", tf[0]->player_id);
//    for (int i = 0; i < len; ++i) {
//        if(tf[i] != NULL) {
//            _free((void **) &tf[i]->data);
//            free(tf[i]);
//            tf[i] = NULL;
//        }
//    }
}

void free_item_dim_arr(Item ***tf, int len) {
    if(*tf != NULL) {
        _free_item_array(*tf, len);
        *tf = NULL;
    }
}
void _free_item_array(Item **tf, int len) {
    for (int i = 0; i < len; ++i) {
        if(tf[i] != NULL) {
//            _free((void **) &tf[i]->data);
            free(tf[i]->data);
            free(tf[i]->name);
            free(tf[i]);
            tf[i] = NULL;
        }
    }
}

void free_menu_dim_arr(Menu ***tf, int len) {
    if(*tf != NULL) {
        _free_menu_array(*tf, len);
        *tf = NULL;
    }
}
void _free_menu_array(Menu **tf, int len) {
    for (int i = 0; i < len; ++i) {
        if(tf[i] != NULL) {
            _free((void **) &tf[i]->title);
            _free((void **) tf[i]);
        }
    }
}

void free_map_dim_arr(Map ***tf, int len) {
    if(*tf != NULL) {
        _free_map_array(*tf, len);
        *tf = NULL;
    }
}
void _free_map_array(Map **tf, int len) {
    for (int i = 0; i < len; ++i) {
        if(tf[i] != NULL) {
            _free_bomb_array(tf[i]->bombs, tf[i]->nb_bomb);
            free_array((void **) tf[i]->body, tf[i]->rows);
            free(tf[i]);
            tf[i] = NULL;
        }
    }
}

void free_player_dim_arr(Player ***tf, int len) {
    if(*tf != NULL) {
        _free_player_array(*tf, len);
        *tf = NULL;
    }
}
void _free_player_array(Player **tf, int len) {
    for (int i = 0; i < len; ++i) {
        if(tf[i] != NULL) {
            _free_bomb_array(tf[i]->bombs, tf[i]->nb_bomb);
            _free_item_array(tf[i]->items, tf[i]->nb_item);
            _free((void **) &tf[i]->name);
            free(tf[i]);
            tf[i] = NULL;
        }
    }
}

void free_char_dim_arr(char ***tf, int len) {
    if(*tf != NULL) {
        free_array((void **) *tf, len);
        *tf = NULL;
    }
}
void free_int_dim_arr(int ***tf, int len) {
    if(*tf != NULL) {
        free_array((void **) *tf, len);
        *tf = NULL;
    }
}
void free_short_dim_arr(short ***tf, int len) {
    if(*tf != NULL) {
        free_array((void **) *tf, len);
        *tf = NULL;
    }
}


void free_array(void **tf, int len) {
    for (int i = 0; i < len; ++i) {
        if(tf[i] != NULL) {
            free(tf[i]);
            tf[i] = NULL;
        }
    }
}
void _free(void **tf) {
    if(*tf != NULL) {
        free(*tf);
        *tf = NULL;
    }
}