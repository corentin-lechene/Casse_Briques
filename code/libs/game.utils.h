static char *LANGUAGE_DIR = "../configs/LANGUAGES/";
static char *LANGUAGE_ATTRIBUTES[] = {
        "EXIT",
        "START",
        "OPTIONS",
        NULL
};


typedef struct {
    char *exit;
    char *start;
    char *options;
    char *bonjour;
} Language;

typedef struct {
    unsigned short port;
    unsigned short language;
} Config;

typedef struct {
    unsigned short id;
    unsigned short rows;
    unsigned short columns;

    unsigned char **body;

    unsigned short player_max;
    unsigned short bomb_max;

    unsigned short nb_map;
} Map;

typedef struct {
    char id;
    int range;
    short bomb_kick;
} Bomb;

typedef struct {
    char id;
    int duration;
    short rare;
    short is_used;
} Item;

typedef struct {
    char *name;
    char id;
    char *color;
    unsigned short direction;

    unsigned short score;
    unsigned short heart;
    unsigned short nb_bomb;
    Bomb *bomb;
    Item **item;

    unsigned int placed_bomb;
    unsigned short is_bot;

} Player;

typedef struct {
    Map **map;
    Player **players;
    Config *config;
    Language *lang;

    Player *winner;
    Player *players_turn;

    unsigned short bo;
    unsigned short cursor;
    unsigned short selected_map;
} Board;



/**
 * @features : create player
 * */
Player *create_player(int *nb_added_player, int *nb_real_player,int *index){
    Player *player = malloc(sizeof(Player));
    if(*nb_added_player != *nb_real_player){
        printf("Entrez votre pseudo : ");
        scanf("%s", player->name);
        player->is_bot = 0;
        player->id = *index;
        *nb_added_player += 1;
        return player;
    }else {
        player->name = "Toto";
        player->is_bot = 1;
        player->id = *index;
        return player;
    }

}

/**
 * @features : add player into player's tab
 * */
void push(Board *dest, Player *source, int index){
    dest->players[index] = source;
    //printf("%s", dest->players[0]->name);
}