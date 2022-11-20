void put_item(Board *board, int x,int y);
int is_item(Board *board, int x, int y);
void get_item(Board *board, int item);
int init_item(Item *item, Board *board);
int has_item(Board *board, int item);
int is_bomb(Board *board, int x,int y);
/**
 * @features : genere un objet avec les probabilités
 * */
void put_item(Board *board, int x, int y){
    Map *map = board->maps[board->current_map];
    items_rarity items_rarity[] = {blue_flame, yellow_flame, bomb_up, bomb_down};
    items_rarity_epic items_rarity_epic[] = {bomb_passes, bomb_kick, invincibility, heart};
    items_rarity_legendary items_rarity_legendary[] = {life, red_flame, bomb_destroy};

    char item;
    unsigned int item_rarity;
    unsigned int choice_item;
    int is_item = random_between(1,3);

    if(is_item == 1){
        item_rarity = random_between(1,100);

        if(item_rarity >= 50 && item_rarity <= 100){
            choice_item = random_between(0, items_len_rare-1);
            item = board->items[items_rarity[choice_item]]->data->_char;
        }else if(item_rarity >= 20 && item_rarity < 45){
            choice_item = random_between(0, items_len_epic-1);
            if(board->items[items_rarity_epic[choice_item]]->is_used == 0){
                item = board->items[items_rarity_epic[choice_item]]->data->_char;
            }
            if(choice_item == 3) board->items[heart]->is_used = 1;

        }else {
            choice_item = random_between(0, items_len_leg-1);
            if(board->items[items_rarity_epic[choice_item]]->is_used == 0){
                item = board->items[items_rarity_legendary[choice_item]]->data->_char;
            }
            if(choice_item == 2) board->items[2]->is_used = 1;
        }
        map->body[x][y] = item;
    }
}

int is_bomb(Board *board, int x, int y){
    Map *map = board->maps[board->current_map];

    for(int i =0; i<map->nb_bomb; i++){
        if(map->bombs[i]->x == x && map->bombs[i]->y == y){
            return 1;
        }
    }
    return 0;
}

/**
 * @features : verifie si il y a un item
 * */
int is_item(Board *board, int x, int y){
    Map *map = board->maps[board->current_map];
    items_index items_index[] = {item_bomb_up, item_bomb_down,item_yellow_flame,item_blue_flame,item_red_flame,item_bomb_destroy,item_bomb_kick,
                                 item_bomb_passes,item_invincibility,item_heart,item_life};

    if(is_bomb(board,x,y)== 1) return -1;

    for(int i = 0; i<items_len-4;i++){
        if(map->body[x][y] == board->items[items_index[i]]->data->_char){
            return items_index[i];
        }
    }
    return -1;
}
int has_item(Board *board, int item){
    Player *player = board->players[board->player_turn];
    for(int i = 0; i<player->nb_item; i++){
        if(player->items[i]->data->_int == board->items[item]->data->_int){
            return 1;
        }
    }
    return 0;
}




/**
 * @features : ajoute l'item au tab Item lié au joueur
 * */
void get_item(Board *board, int item){
    Player *player = board->players[board->player_turn];
    int is_storage = init_item(board->items[item], board);
    if(is_storage==1){
        player->nb_item +=1;
        player->items = realloc(player->items, sizeof(Item *) * player->nb_item);

        player->items[player->nb_item - 1] = malloc(sizeof (Item));
        player->items[player->nb_item - 1]->data = malloc(sizeof (Data_item));
        player->items[player->nb_item - 1]->name = malloc(sizeof (char) * (strlen(board->items[item]->name) + 1));

        strcpy(player->items[player->nb_item - 1]->name, board->items[item]->name);
        player->items[player->nb_item - 1]->type = board->items[item]->type;
        player->items[player->nb_item - 1]->data->_char = board->items[item]->data->_char;
        player->items[player->nb_item - 1]->data->_int = board->items[item]->data->_int;
    }
}

/**
 * @features : définit le comportement de l'item en fonction de son type
 * */
int init_item(Item *item, Board *board){
    Player *player = board->players[board->player_turn];
    Map *map = board->maps[board->current_map];
    switch (item->data->_char) {
        case item_bomb_up :
            player->nb_bomb += 1;
            break;
        case '-' :
            decrement_or_reset(&player->nb_bomb,0);
            break;
        case 'y' :
            player->bomb_range +=1;
            break;
        case 'b' :
            decrement_or_reset(&player->bomb_range, 0);
            break;
        case 'l' :
            player->heart += 1;
            break;
        case 'Q' :
            player->bomb_type = bomb_destroy;
            break;
        case 'r' :
            player->bomb_range = map->columns > map->rows ?  map->columns : map->rows;
            break;
        case '@' :
            player->bomb_type = bomb_kick;
            return 1;
        case '$':
        case '[':
        case 'i':
        case 'h':
            return 1;
    }

}