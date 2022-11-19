
int create_server(Board *board);
int join_server(char *port, Board *board);

int is_player_join(Board *board);
int is_player_start_game(Board *board); //todo

int send_leave(Board *board); //todo
int send_play(Board *board); //todo
int send_failure(Board *board); //todo
int send_win(Board *board); //todo
int send_dead(Board *board); //todo
int send_player_leave(Board *board); //todo
int send_start_game(Board *board); //todo
int send_end_game(Player *player, Board *board); //todo
char *get_player_event(Board *board); //todo

char *set_encoded_map(Map *map);
int send_message(char *msg, Board *board);
char *set_attribute(int value, char *name);
char *get_response(char *response);


/* ----------------------------------- */


int create_server(Board *board) {
    board->server = malloc(sizeof(Server));
    Server *server = board->server;
    
    server->client_socket = INVALID_SOCKET;
    server->server_socket = INVALID_SOCKET;

    WSADATA WSAData;
    SOCKADDR_IN server_socket_addr;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_socket_addr.sin_addr.s_addr = INADDR_ANY;
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = htons(PORT);

    bind(server->server_socket, (SOCKADDR *)&server_socket_addr, sizeof(server_socket_addr));
    listen(server->server_socket, 0);
    
    return 1;
}

int join_server(char *port, Board *board) {
    board->client = malloc(sizeof(Client));
    Client *client = board->client;

    client->client_socket = INVALID_SOCKET;

    WSADATA WSAData;
    SOCKADDR_IN server_socket_addr;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    
    client->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_socket_addr.sin_addr.s_addr = inet_addr("172.20.10.7"); // 172.20.10.7
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = htons(atol(port));

    return connect(client->client_socket, (SOCKADDR *)&server_socket_addr, sizeof(server_socket_addr));
}

int is_player_join(Board *board) {
    Server *server = board->server;
    int size_ser_sock_addr = sizeof(server->client_socket_addr);
    server->client_socket = accept(server->server_socket, (SOCKADDR *)&server->client_socket_addr, &size_ser_sock_addr);
    return 1;
}

int send_start_game(Board *board) {
    Server *server = board->server;

    char *encoded_map = set_encoded_map(board->maps[board->current_map]);

    char *message = str_cat(RESPONSE_START, encoded_map);
    server->res = send(server->client_socket, message, strlen(message)+1, 0);
    if(server->res == SOCKET_ERROR) {
        closesocket(server->client_socket);
        closesocket(server->server_socket);
        WSACleanup();
        return 0;
    }
    return 1;
}


char *get_response(char *response){
    printf("%s", response);
    pause();

    printf("%c", response[5]);
    pause();
    int i =0;
    while(response[i] != '\0' ){





    }







}


int send_play(Board *board){
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_PLAY,encoded_map), board);
}

int send_leave(Board *board){
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_EXIT,encoded_map), board);
}

int send_failure(Board *board){
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_FAILURE,encoded_map), board);
}

int send_win(Board *board){
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_WIN,encoded_map), board);
}

int send_dead(Board *board){
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_DEAD,encoded_map), board);
}

int send_message(char *msg, Board *board){
    if(board->game_mode == GAME_MODE_HOST) {
        return send(board->server->client_socket, msg, strlen(msg) + 1, 0);
    }
    return send(board->client->client_socket, msg, strlen(msg) + 1, 0);
}

char *set_attribute(int value, char *name){
    char *buf = malloc(sizeof (char) * 3);
    itoa(value, buf, 10);
    return str_cat(name, str_cat(buf,";"));
}

char *set_encoded_map(Map *map){
    char *info_rows = set_attribute(map->rows, "Rows:");
    char *info_columns = set_attribute(map->columns, "Columns:");
    char *info_map = strcat(info_rows, info_columns);

    char *encoded_map = malloc(sizeof (char)*(map->rows*map->columns));
    int index = 0;
    for(int i = 0; i<map->rows; i++){
        for(int j = 0; j<map->columns; j++){
            encoded_map[index] = map->body[i][j];
            index += 1;
        }
    }
    encoded_map = str_cat(info_map, str_cat(encoded_map, ";"));
    return encoded_map;
}


int game_is_started(Board *board) {
    Client *client = board->client;

    do {
        client->res = recv(client->client_socket, client->recv_buf, sizeof(BUFLEN), 0);
        if(client->res <= 0) {
            continue;
        }
        client->recv_buf[client->res] = '\0';
    } while(strcmp(client->recv_buf, "start") != 1);
    return 1;
}

