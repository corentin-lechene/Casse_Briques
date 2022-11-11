#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int main() {
    int c;
    scanf("%d", &c);
    if(c == 0) {
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,0), &WSAData);
        
        int iResult;
        struct addrinfo *result = NULL, *ptr = NULL, hints;
        SOCKET ListenSocket = INVALID_SOCKET;
        SOCKET ClientSocket = INVALID_SOCKET;

        ZeroMemory(&hints, sizeof (hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the local address and port to be used by the server
        iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
        if (iResult != 0) {
            printf("getaddrinfo failed: %d\n", iResult);
            WSACleanup();
            return 1;
        }

        // Create a SOCKET for the server to listen for client connections
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        if (ListenSocket == INVALID_SOCKET) {
            printf("Error at socket(): %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }
        // Setup the TCP listening socket
        iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
            printf( "Listen failed with error: %ld\n", WSAGetLastError() );
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
        
        
        closesocket(ClientSocket);
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    } else {
//        WSADATA WSAData;
//        SOCKET sock;
//        SOCKADDR_IN sin;
//        char buffer[255];
//        char sendBuffer[255];
//        WSAStartup(MAKEWORD(2,0), &WSAData);
//        /* Tout est configuré pour se connecter sur IRC, haarlem, Undernet. */
//        sock = socket(AF_INET, SOCK_STREAM, 0);
//        sin.sin_addr.s_addr = inet_addr("192.168.0.18");
//        sin.sin_family = AF_INET;
//        sin.sin_port = htons(PORT);
//        connect(sock, (SOCKADDR *)&sin, sizeof(sin));
//
//        while(1) {
//            fflush(stdin);
//            scanf("%s", sendBuffer);
//            
//            send(sock, sendBuffer, (int)strlen(sendBuffer), 0);
//            recv(sock, buffer, sizeof(buffer), 0);
//            printf("[%s]", buffer);
//            if(strcmp(buffer, "end") == 0) {
//                closesocket(sock);
//                break;
//            }
//        }
//
//        WSACleanup();
        return 0;
    }
}