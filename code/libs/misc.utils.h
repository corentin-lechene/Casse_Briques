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

#define MARGIN_X 4
#define MARGIN_Y 1

/********************/
/**      enums     **/
/********************/
enum loading_index {
    loading_init = 0,
    loading_config,
    loading_language,
    loading_items,
    loading_maps,
    loading_len
};

enum language_index {
    language_start = 0,
    language_back,
    language_exit,
    language_len
};

enum items_index {
    item_bomb = 0,
    item_destructible_wall,
    item_indestructible_wall,
    item_bomb_Up,
    item_bomb_Down,
    item_yellow_Flame,
    item_blue_Flame,
    item_red_Flame,
    item_bomb_Passes,
    item_bomb_Kick,
    item_invincibility,
    item_heart,
    item_life,
    items_len
};


/********************/
/**  const names   **/
/********************/

static char *LOADING_NAME[] = {
        "loading_init",
        "loading_config",
        "loading_language",
        "loading_items",
        "loading_maps",
};

static char *LANGUAGES_NAME[] = {
        "language_start",
        "language_back",
        "language_exit",
};


static char *ITEMS_NAME[] = {
        "item_bomb",
        "item_destructible_wall",
        "item_indestructible_wall",
        "item_bomb_Up",
        "item_bomb_Down",
        "item_yellow_Flame",
        "item_blue_Flame",
        "item_red_Flame",
        "item_bomb_Passes",
        "item_bomb_Kick",
        "item_invincibility",
        "item_heart",
        "item_life",
};


static char *CONFIG_DIR = "../app.config";
static char *LANGUAGE_DIR = "../configs/languages/";
static char *ITEM_DIR = "../configs/items";


typedef struct {
    char *str;
    unsigned int str_len;
} Lang;

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
    char *name;
    int duration;
    short rarity;
    short is_used;

    int _int;
    char _char;
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
    Item **items;

    unsigned int placed_bomb;
    unsigned short is_bot;
} Player;

typedef struct {
    Map **maps;
    Player **players;
    Config *config;
    Lang **lang;
    Item **items;

    Map **selected_maps;
    Player *winner;
    Player *player_turn;

    unsigned short nb_map;
    unsigned short nb_player;
    unsigned short nb_items;

    unsigned short bo;
    unsigned short selected_menu;
    unsigned short selected_choice;
    unsigned short selected_map;
} Board;

typedef struct {
    unsigned short item;
    char *name;
} Loading_item;

typedef struct {
  Loading_item **loading_item;
  unsigned short load_ended;
} Loading;