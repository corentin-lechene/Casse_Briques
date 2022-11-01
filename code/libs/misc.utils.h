#define IN_EXIT 0
#define MENU_START 1
#define MENU_MODE_GAME 2
#define MENU_NUMBER_PLAYER 3
#define MENU_SELECT_MAPS 5
#define MENU_ONLINE 4
#define IN_GAME 7
#define IN_PREP_GAME 10
#define IN_PLAYERS 6
//#define IN_MAPS 6
#define IN_CONFIG 9

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
    item_destructible_wall = 0,
    item_indestructible_wall,
    item_bomb_up,
    item_bomb_down,
    item_yellow_flame,
    item_blue_flame,
    item_red_flame,
    item_bomb,
    item_bomb_destroy,
    item_bomb_kick,
    item_bomb_passes,
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
        "item_destructible_wall",
        "item_indestructible_wall",
        "item_bomb_up",
        "item_bomb_down",
        "item_yellow_flame",
        "item_blue_flame",
        "item_red_flame",
        "item_bomb",
        "item_bomb_destroy",
        "item_bomb_kick",
        "item_bomb_passes",
        "item_invincibility",
        "item_heart",
        "item_life",
        "items_len"
};

const char *MAP_DIR = "../configs/maps/";
const char *CONFIG_DIR = "../app.config";
const char *LANGUAGE_DIR = "../configs/languages/";
const char *ITEM_DIR = "../configs/items";


typedef struct {
    char *str;
    unsigned int str_len;
} Lang;

typedef struct {
    unsigned short port;
    char *language;
} Config;

typedef struct {
    int _int;
    char _char;
} Data_item;

typedef struct {
    char player_id;
    Data_item *data;
} Bomb;

typedef struct {
    unsigned short id;
    unsigned short rows;
    unsigned short columns;

    unsigned short player_max;
    unsigned short bomb_default;

    unsigned short heart;

    char **body;
    Bomb **Bombs;
} Map;


typedef struct {
    char *name;
    int duration;
    short rarity;
    short is_used;

    Data_item *data;
} Item;

typedef struct {
    char *name;
    char id;
    char *color;
    unsigned short direction;
    int x;
    int y;

    unsigned short heart;
    unsigned short nb_bomb;
    unsigned short bomb_range;
    unsigned short bomb_type;

    Item **items;
    Bomb **bombs;

    unsigned short score;
    unsigned short is_bot;
} Player;

typedef struct {
    Map **default_maps;
    Player **players;
    Config *config;
    Lang **lang;
    Item **items;

    Map **maps;
    Player *winner;
    Player *player_turn;

    unsigned short nb_map;
    unsigned short nb_selected_map;
    unsigned short nb_player;

    unsigned short bo;
    unsigned short selected_menu;
    unsigned short selected_choice;
    unsigned short current_map;
    unsigned short *selected_maps;
} Board;

typedef struct {
    unsigned short item;
    char *name;
} Loading_item;

typedef struct {
  Loading_item **loading_item;
  unsigned short load_ended;
} Loading;