#define IN_EXIT 0
#define IN_GAME 10
#define IN_PLAYERS 6
#define IN_MAPS 7
#define IN_PAUSE 11

#define CROSS_TOP 72
#define CROSS_BOTTOM 80
#define CROSS_LEFT 75
#define CROSS_RIGHT 77

#define KEY_z 122
#define KEY_s 115
#define KEY_d 100
#define KEY_q 113
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_SPACE 32

#define ITEM_MI 219
#define ITEM_MD 176
#define ITEM_SP 32
#define ITEM_TP 126
#define ITEM_BB 162
#define ITEM_BU 43
#define ITEM_BD 45
#define ITEM_BP 157
#define ITEM_BK 15
#define ITEM_FJ 24
#define ITEM_FB 25
#define ITEM_FR 5
#define ITEM_IN 42
#define ITEM_CO 254
#define ITEM_VI 3


#define MARGIN_X 4
#define MARGIN_Y 1

static char *ITEMS_NAME[] = {
        "Bombe",
        "Bombe Up",
        "Bombe down",
        "Bombe Kick",
        "Passe-Bombes",
        "Flamme Jaune",
        "Flamme Bleue",
        "Flamme Rouge",
        "Invincibilité",
        "Coeur",
        "Vie",
};

static char *ITEMS_STRING[] = {
        "Ó",
        "+",
        "-",
        "☼",
        "Ø",
        "↑",
        "↓",
        "♣",
        "*",
        "■",
        "♥",
};

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
    Map **maps;
    Player **players;
    Config *config;
    Language *lang;

    Map **selected_maps;
    Player *winner;
    Player *players_turn;

    unsigned short nb_map;
    unsigned short nb_player;

    unsigned short bo;
    unsigned short selected_menu;
    unsigned short selected_choice;
    unsigned short selected_map;
} Board;
