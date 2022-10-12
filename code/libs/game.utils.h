static char *LANGUAGE_DIR = "../configs/LANGUAGES/";
static char *LANGUAGE_ATTRIBUTES[] = {
        "EXIT",
        "START",
        "OPTIONS",
        NULL
};

/* MAPS */
char MAP[5][5] = {
        219, 219,219,219,219,
        219, 219,219,219,219,
        219, 219,219,219,219,
        219, 219,219,219,219,
        219, 219,219,219,219
};


typedef struct {
    char *exit;
    char *start;
    char *options;
} Language;

typedef struct {
    unsigned short port;
    char *language;
} Config;

typedef struct {
    unsigned short id;
    unsigned short rows;
    unsigned short columns;

    char **body;

    unsigned short player_max;
    unsigned short bomb_max;
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
} Player;;

typedef struct {
    Map **map;
    Player **players;
    Config *config;
    Language *lang;

    Player *winner;
    Player *players_turn;

    unsigned short nb_map;
    unsigned short nb_player;

    unsigned short bo;
    unsigned short selected_menu;
    unsigned short selected_choice;
    unsigned short selected_map;
} Board;
