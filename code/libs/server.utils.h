
int create_server(Board *board);

int join_server(char *ip, char *port, Board *board);

int is_player_join(Board *board);

int is_player_start_game(Board *board); //todo

int send_leave(Board *board);

int send_play(Board *board);

int send_failure(Board *board);

int send_win(Board *board);

int send_dead(Board *board);

int send_player_leave(Board *board); //todo
int send_start_game(Board *board);

char *get_player_event(Board *board); //todo

char *set_encoded_map(Map *map);

int send_message(char *msg, Board *board);

char *set_attribute(int value, char *name);

char *get_response(const char *message);

Map *get_decoded_map(char *message);

void set_map(char *token, Map *map);


/* ----------------------------------- */


int create_server(Board *board) {
    struct hostent *localHost;

    board->server = malloc(sizeof(Server));
    Server *server = board->server;

    server->client_socket = INVALID_SOCKET;
    server->server_socket = INVALID_SOCKET;

    WSADATA WSAData;
    SOCKADDR_IN server_socket_addr;
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);

    localHost = gethostbyname("");
    server->ip = inet_ntoa(*(struct in_addr *) *localHost->h_addr_list);

    server_socket_addr.sin_addr.s_addr = inet_addr(server->ip);
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = htons(PORT);

    bind(server->server_socket, (SOCKADDR *) &server_socket_addr, sizeof(server_socket_addr));
    listen(server->server_socket, 0);

    return 1;
}

int join_server(char *ip, char *port, Board *board) {
    board->client = malloc(sizeof(Client));
    Client *client = board->client;

    client->client_socket = INVALID_SOCKET;

    WSADATA WSAData;
    SOCKADDR_IN server_socket_addr;
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    client->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_socket_addr.sin_addr.s_addr = inet_addr("192.168.201.1"); // 172.20.10.7
//    server_socket_addr.sin_addr.s_addr = inet_addr(ip); // 172.20.10.7
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = htons(atol("27015"));

    return connect(client->client_socket, (SOCKADDR *) &server_socket_addr, sizeof(server_socket_addr));
}

int is_player_join(Board *board) {
    Server *server = board->server;
    int size_ser_sock_addr = sizeof(server->client_socket_addr);
    server->client_socket = accept(server->server_socket, (SOCKADDR *) &server->client_socket_addr,
                                   &size_ser_sock_addr);
    return 1;
}

int send_start_game(Board *board) {
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    char *message = str_cat(RESPONSE_START, encoded_map);
    return send_message(message, board);
}


char *get_response(const char *message) {
    int nb_char = 1;
    char *response = malloc(sizeof(char) * nb_char);
    int i = 0;
    int j = 0;
    while (message[i] != '\0') {
        i++;
        if (message[i - 1] == ':') {
            do {
                response[j] = message[i];
                if (message[i + 1] == ';') {
                    response[j + 1] = '\0'; 
                    printf("-> response: [%s]\n", response);
                    return response;
                }
                i++;
                j++;
                nb_char++;
                response = realloc(response, sizeof(char) * (nb_char + 1));
            } while (message[i] != ';');
        }
    }
}


Map *get_decoded_map(char *message) {
    const char *separators = ";";
    Map *map = malloc(sizeof(Map));
    
    char *strToken = strtok ( message, separators );
    while ( strToken != NULL ) {
        char *left = str_get_left(strToken, ':');
        char *right = str_get_right(strToken, ':');
        
        if(strcmp(left, "Columns") == 0) {
            map->columns = (unsigned short) atoll(right);
        } else if(strcmp(left, "Rows") == 0) {
            map->rows = (unsigned short) atoll(right);
        } else if(strcmp(left, "Map") == 0) {
            map->body = malloc(sizeof(char *) * map->rows);
            for (int i = 0; i < map->rows; ++i) {
                map->body[i] = malloc(sizeof(char) * map->columns);
            }

            int index = 0;
            for (int i = 0; i < map->rows; ++i) {
                for (int j = 0; j < map->columns; ++j) {
                    map->body[i][j] = right[index++];
                }
            }
        }
        strToken = strtok ( NULL, separators );
    }
//    printf("get_decoded_map: rows: [%hu] columns: [%hu]\n", map->rows, map->columns);
//    printf("map: [%s]\n", map->body[1]);
    return map;
}


int send_play(Board *board) {
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_PLAY, encoded_map), board);
}

int send_leave(Board *board) {
    return send_message(str_cat(RESPONSE_EXIT, "map:"), board);
}

int send_failure(Board *board) {
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_FAILURE, encoded_map), board);
}

int send_win(Board *board) {
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_WIN, encoded_map), board);
}

int send_dead(Board *board) {
    char *encoded_map = set_encoded_map(board->maps[board->current_map]);
    return send_message(str_cat(RESPONSE_DEAD, encoded_map), board);
}

int send_message(char *msg, Board *board) {
    printf("send_message: [%s]\n", msg);
    if (board->game_mode == GAME_MODE_HOST) {
        return send(board->server->client_socket, msg, strlen(msg) + 1, 0);
    }
    return send(board->client->client_socket, msg, strlen(msg) + 1, 0);
}

char *set_attribute(int value, char *name) {
    char *buf = malloc(sizeof(char) * 4);
    itoa(value, buf, 10);
    buf[3] = '\0';
    return str_cat(name, str_cat(buf, ";"));
}

char *set_encoded_map(Map *map) {
    char *info_rows = set_attribute(map->rows, "Rows:");
    char *info_columns = set_attribute(map->columns, "Columns:");
    char *info_map = str_cat(info_rows, info_columns);

    char *encoded_map = malloc(sizeof(char) * (map->rows * map->columns + 1));
    int index = 0;
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->columns; j++) {
            encoded_map[index] = map->body[i][j];
            index += 1;
        }
    }
    encoded_map[index] = '\0';
    
    char *res_encoded_map = str_cat("Map:", encoded_map);
    
    encoded_map = str_cat(info_map, str_cat(res_encoded_map, ";"));
    free(info_columns);
    free(info_rows);
    free(info_map);
    return encoded_map;
}


int await_response(Board *board) {
    if (board->game_mode == GAME_MODE_HOST) {
        Server *server = board->server;
        do {
            server->res = recv(server->client_socket, server->recv_buf, sizeof(BUFLEN), 0);
            if (server->res > 0) {
                server->recv_buf[server->res] = '\0';
                printf("recv server: [%s]\n", server->recv_buf);
                break;
            }
        } while (1);
        return 1;
    } else {
        Client *client = board->client;
        do {
            client->res = recv(client->client_socket, client->recv_buf, BUFLEN, 0);
            if (client->res == SOCKET_ERROR) {
                printf("send failed: %d\n", WSAGetLastError());
                closesocket(client->client_socket);
                WSACleanup();
                pause();
                return 0;
            }
            if (client->res > 0) {
                client->recv_buf[client->res] = '\0';
                printf("recv client: [%s]\n", client->recv_buf);
                break;
            }
        } while (1);
        return 1;
    }
    return 0;
}

int game_is_started(Board *board) {
    while (1) {
        if (await_response(board)) {
            if (strcmp(get_response(board->client->recv_buf), "exit") == 0) {
                closesocket(board->client->client_socket);
                WSACleanup();
                return 0;
            }
            if (strcmp(get_response(board->client->recv_buf), "start") == 0) {
                return 1;
            }
        }
    }
}

