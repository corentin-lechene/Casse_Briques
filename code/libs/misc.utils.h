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

#define KEY_z 122
#define KEY_s 115
#define KEY_d 100
#define KEY_q 113

#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_CROSS_TOP 72
#define KEY_CROSS_BOTTOM 80
#define KEY_CROSS_LEFT 75
#define KEY_CROSS_RIGHT 77

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

/* ---===  MENUS  ===--- */
typedef enum {
    menu_leave = 0,
    menu_home,
    menu_options,
    menu_languages,
    menu_game_mode,
    menu_players,
    menu_maps,
    menu_init_game,
    menu_game,
    menu_winner_summary,
    menu_resume,
    menu_patch_notes,
    menu_credits,
    menus_len
} menus_index;

const char *MENUS_NAME[] = {
        "menu_leave",
        "menu_home",
        "menu_options",
        "menu_languages",
        "menu_game_mode",
        "menu_players",
        "menu_maps",
        "menu_init_game",
        "menu_game",
        "menu_winner_summary",
        "menu_resume",
        "menu_patch_notes",
        "menu_credits",
};

/* ---===  CHOICES  ===--- */
typedef enum {
    choice_play,
    choice_options,
    choice_patch_notes,
    choice_credits,
    choice_leave,
    choice_back,
    choice_solo,
    choice_local,
    choice_online,
    choice_join_server,
    choice_create_server,
    choices_len,
} choices_index;

const char *CHOICES_NAME[] = {
        "choice_play",
        "choice_options",
        "choice_patch_notes",
        "choice_credits",
        "choice_leave",
        "choice_back",
        "choice_solo",
        "choice_local",
        "choice_online",
        "choice_join_server",
        "choice_create_server",
};

/********************/
/**      enums     **/
/********************/

enum loading_index {
    loading_init = 0,
    loading_config,
    loading_language,
    loading_items,
    loading_menus,
    loading_maps,
    loading_len
};

enum language_index {
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
        "loading_menus",
        "loading_maps",
};

static char *LANGUAGES_NAME[] = {};



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



typedef struct {
    char *str;
    unsigned int str_len;
} Lang;

typedef struct {
    unsigned short item;
    char *name;
} Loading_item;

typedef struct {
    Loading_item **loading_item;
} Loading;

typedef struct {
    Loading *loading;
    char *language;
    char *lang_dir;
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
    char *title;
    menus_index next_menu;
    menus_index prev_menu;
    unsigned short nb_choice;
} Menu;

typedef struct {
    char *name;
    char id;
    char *color;
    unsigned short direction;

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
    Menu **menus;

    Map **maps;
    Player *winner;
    Player *player_turn;

    unsigned short nb_map;
    unsigned short nb_selected_map;
    unsigned short nb_player;

    unsigned short bo;
    unsigned short current_menu;
    unsigned short previous_menu;
    unsigned short current_choice;
    unsigned short current_map;
    unsigned short *selected_maps;
} Board;

const char *CONFIG_DIR = "../app.config";
const char *LANGUAGE_DIR = "../configs/languages/";
const char *ITEM_DIR = "../configs/items";
const char *MAP_DIR = "../configs/maps/";
const char *PATCH_NOTES_DIR = "../configs/patch_notes/";
const char *CREDITS_DIR = "../configs/credits/";

enum colors {
    color_black = 0,
    color_blue,
    color_green,
    color_cyan,
    color_red,
    color_magenta,
    color_brown,
    color_light_gray,
    color_dark_gray,
    color_light_blue,
    color_light_green,
    color_light_cyan,
    color_light_red,
    color_light_magenta,
    color_yellow,
    color_white,
};

const short COLOR_DEFAULT = color_light_gray;
