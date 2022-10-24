#define IN_EXIT 0
#define MENU_START 1
#define MENU_MODE_GAME 2
#define MENU_NUMBER_PLAYER 3
#define MENU_SELECT_MAPS 5
#define MENU_ONLINE 4
#define IN_GAME 8
#define IN_PLAYERS 6
#define IN_MAPS 6
#define IN_CONFIG 7

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

#define BLACK "\033[;30m"
#define RED "\033[;31m"
#define GREEN "\033[;32m"
#define YELLOW "\033[;33m"
#define BLUE "\033[;34m"
#define PURPLE "\033[;35m"
#define CYAN "\033[;36m"
#define WHITE "\033[;37m"




static char *LANGUAGE_DIR = "../configs/LANGUAGES/";
static char *LANGUAGE_ATTRIBUTES[] = {
        "EXIT",
        "START",
        "CONFIGURATION",
        "TITLE_MENU_START",
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
    char *configuration;
    char *title_menu_start;
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

    Player *winner;
    Player *players_turn;
    Map **selected_maps;

    unsigned short nb_map;
    unsigned short nb_player;

    unsigned short bo;
    unsigned short selected_menu;
    unsigned short selected_choice;
    unsigned short selected_map;
    //unsigned short *selected_maps;
} Board;
