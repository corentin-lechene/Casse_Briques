
void create_server(Board *board);


/* ----------------------------------- */


void create_server(Board *board) {
    SOCKET ClientSocket = INVALID_SOCKET;

    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN sin;
    SOCKADDR_IN csin;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    bind(sock, (SOCKADDR *)&sin, sizeof(sin));
    listen(sock, 0);

    // Accept a client socket
    int sinsize = sizeof(csin);
    ClientSocket = accept(sock, (SOCKADDR *)&csin, &sinsize);
}