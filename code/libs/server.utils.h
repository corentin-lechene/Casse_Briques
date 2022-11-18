
int create_server(Board *board);
int join_server(char *port, Board *board);

int is_player_join(Board *board);
int is_player_start_game(Board *board); //todo

void send_leave(Board *board); //todo
void send_play(Board *board); //todo
void send_failure(Board *board); //todo
void send_win(Board *board); //todo
void send_dead(Board *board); //todo
void send_player_leave(Board *board); //todo
void get_player_event(Board *board); //todo
void send_start_game(Board *board); //todo
void send_end_game(Player *player, Board *board); //todo


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
    server_socket_addr.sin_addr.s_addr = inet_addr("172.20.10.7");
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = htons(atol(port));

    int res = connect(client->client_socket, (SOCKADDR *)&server_socket_addr, sizeof(server_socket_addr));
    if(res == SOCKET_ERROR) {
        closesocket(client->client_socket);
        WSACleanup();
        return 0;
    }
    return 1;
}

int is_player_join(Board *board) {
    Server *server = board->server;
    int size_ser_sock_addr = sizeof(server->client_socket_addr);
    server->client_socket = accept(server->server_socket, (SOCKADDR *)&server->client_socket_addr, &size_ser_sock_addr);
    return 1;
}

int is_player_start_game(Board *board) {
    
}