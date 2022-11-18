
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
    server_socket_addr.sin_addr.s_addr = inet_addr("192.168.1.36"); // 172.20.10.7
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
    
//todo    char *message_encoded = get_message_encoded("", board); 
    char *message = "start";
    server->res = send(server->client_socket, message, strlen(message), 0);
    if(server->res == SOCKET_ERROR) {
        closesocket(server->client_socket);
        closesocket(server->server_socket);
        WSACleanup();
        return 0;
    }
    return 1;
}

int game_is_started(Board *board) {
    Client *client = board->client;

    do {
        client->res = recv(client->client_socket, client->recv_buf, BUFLEN, 0);
        if(client->res > 0) {
            continue;
        }
        client->recv_buf[client->res] = '\0';
    } while(strcmp(client->recv_buf, "start") != 1);
    return 1;
}