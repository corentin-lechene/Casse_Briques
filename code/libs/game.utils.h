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
    Bomb bomb;
    Item *item;

    unsigned int placed_bomb;
    unsigned short is_bot;
} Player;

typedef struct {
    Map *map;
    Player **players;
    Config config;

    Player winner;
    Player players_turn;

    unsigned short bo;
    unsigned short cursor;
} Board;
