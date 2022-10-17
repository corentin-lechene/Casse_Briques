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




Player *create_player(){
    //Board *board = malloc(sizeof(Board));
    //Création du joueur
    Player *player = malloc(sizeof(Player));
    printf("Entrez votre pseudo : ");
    scanf("%s", player->name);


    //board->players[0] = player;

    return player;

}

void push(Board *dest, Player *source){

}