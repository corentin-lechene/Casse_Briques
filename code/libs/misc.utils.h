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

#define GAME_MODE_HOST 0
#define GAME_MODE_CLIENT 1
#define GAME_MODE_LOCAL 2

#define BUFLEN 255
#define PORT 27015
#define RESPONSE_SUCCESS "response:success"
#define RESPONSE_FAILURE "response:failure"
#define RESPONSE_PLAY "response:play"
#define RESPONSE_WIN "response:win"
#define RESPONSE_DEAD "response:dead"
#define RESPONSE_EXIT "response:exit"

#define RESPONSE_SUCCESS_LEN strlen(RESPONSE_SUCCESS)
#define RESPONSE_FAILURE_LEN strlen(RESPONSE_FAILURE)
#define RESPONSE_PLAY_LEN strlen(RESPONSE_PLAY)
#define RESPONSE_WIN_LEN strlen(RESPONSE_WIN)
#define RESPONSE_DEAD_LEN strlen(RESPONSE_DEAD)
#define RESPONSE_EXIT_LEN strlen(RESPONSE_EXIT)


enum colors_index {
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
    colors_len,
};

/* ---===  MENUS  ===--- */
typedef enum {
    menu_leave = 0,
    menu_home,
    menu_options,
    menu_languages,
    menu_set_languages,
    menu_game_mode,
    menu_solo,
    menu_players,
    menu_maps,
    menu_online,
    menu_host,
    menu_client,
    menu_wait_players,
    menu_reset_game,
    menu_restart_game,
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
        "menu_set_languages",
        "menu_game_mode",
        "menu_solo",
        "menu_players",
        "menu_maps",
        "menu_online",
        "menu_host",
        "menu_client",
        "menu_wait_players",
        "menu_reset_game",
        "menu_restart_game",
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
    choice_yes,
    choice_no,
    choice_continue,
    choice_restart,
    choice_back,
    choice_languages,
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
        "choice_yes",
        "choice_no",
        "choice_continue",
        "choice_restart",
        "choice_back",
        "choice_languages",
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

typedef enum {
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
    item_bomb_push,
    item_invincibility,
    item_heart,
    item_life,
    items_len
}items_index;

typedef enum {
    blue_flame = item_blue_flame,
    yellow_flame = item_yellow_flame,
    bomb_up = item_bomb_up,
    bomb_down = item_bomb_down,
    items_len_rare = 4
}items_rarity;
typedef enum  {
    bomb_passes = item_bomb_passes,
    bomb_kick = item_bomb_kick,
    invincibility = item_invincibility,
    heart = item_heart,
    items_len_epic = 4
}items_rarity_epic;
typedef enum {
    life = item_life,
    red_flame = item_red_flame,
    bomb_destroy = item_bomb_destroy,
    items_len_leg = 3

}items_rarity_legendary;


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
        "item_bomb_push",
        "item_invincibility",
        "item_heart",
        "item_life",
};


typedef struct {
    unsigned short x;
    unsigned short y;
    double distance;
} Coord;


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
    unsigned int nb_turn;
    unsigned int x;
    unsigned int y;
    Data_item *data;
    int range;
} Bomb;

typedef struct {
    unsigned short id;
    unsigned short rows;
    unsigned short columns;

    unsigned short player_max;
    unsigned short bomb_default;
    unsigned short nb_bomb;
    unsigned short heart;

    char **body;
    Bomb **bombs;
} Map;


typedef struct {
    char *name;
    int duration;
    short rarity;
    short is_used;
    unsigned int type;

    Data_item *data;
} Item;

typedef struct {
    char *title;
    menus_index next_menu;
    unsigned short nb_choice;
} Menu;

typedef struct {
    char *name;
    char id;
    enum colors_index color;
    unsigned short direction;
    unsigned short x;
    unsigned short y;
    //char *direction;

    unsigned short heart;
    unsigned short nb_bomb;
    unsigned short nb_item;
    unsigned short bomb_range;
    unsigned short bomb_type;

    Item **items;

    unsigned short score;
    unsigned short is_bot;
} Player;

typedef struct {
    int res;
    int res_len;
    int res_send;
    int res_send_len;
    char recv_buf[BUFLEN];
    char send_buf[BUFLEN];
    SOCKET client_socket;
    SOCKET server_socket;
    SOCKADDR_IN client_socket_addr;
    char ip[16];
    char port[5];
} Server;


typedef struct {
    char send_buf[BUFLEN];
    char recv_buf[BUFLEN];
    SOCKET client_socket;
    char ip[16];
    char port[5];
} Client;


typedef struct {
    Map **default_maps;
    Player **players;
    Config *config;
    Lang **lang;
    Item **items;
    Menu **menus;

    Map **maps;
    Player *winner;
    
    Server *server;
    Client *client;

    unsigned short nb_map;
    unsigned short nb_selected_map;
    unsigned short nb_player;

    unsigned short bo;
    unsigned short current_menu;
    unsigned short previous_menu;
    unsigned short current_choice;
    unsigned short current_map;
    unsigned short player_turn;
    short *selected_maps;
    short game_mode;
} Board;

const char *CONFIG_DIR = "../app.config";
const char *LANGUAGE_DIR = "../configs/languages/";
const char *ITEM_DIR = "../configs/items";
const char *MAP_DIR = "../configs/maps";
const char *PATCH_NOTES_DIR = "../configs/patch_notes/";
const char *CREDITS_DIR = "../configs/credits/";

const short COLOR_DEFAULT = color_light_gray;
const short COLOR_BG_DEFAULT = color_black;
char *PLAYER_NAMES[] = {
        "Simon",
        "Lola",
        "Nicolas",
        "Yasmine",
        "haribo",
        "Anais",
        "Gabriel",
        "Kessy",
        "Emir",
        "Elena",
        "Julien",
        "Melissa",
        "Florian"
};
