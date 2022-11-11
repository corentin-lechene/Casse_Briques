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
#define PORT 27015

int main() {
    int c;
    scanf("%d", &c);
    if(c == 0) {
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
        
        char recvbuf[DEFAULT_BUFLEN];
        int iResult, iSendResult;
        int recvbuflen = DEFAULT_BUFLEN;

        // Receive until the peer shuts down the connection
        do {

            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            if (iResult > 0) {
                printf("Bytes received: %d\n", iResult);
                recvbuf[iResult] = '\0';

                // Echo the buffer back to the sender
                iSendResult = send(ClientSocket, recvbuf, iResult, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf("Bytes sent: %d (%s)\n", iSendResult, recvbuf);
                
                if(strcmp(recvbuf, "end") == 0) {
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
            } else if (iResult == 0)
                printf("Connection closing...\n");
            else {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

        } while (iResult > 0);
        closesocket(sock);
        WSACleanup();
        return 0;
    } else {
        WSADATA WSAData;
        SOCKET sock;
        SOCKADDR_IN sin;
        char buffer[255];
        char sendBuffer[255];
        WSAStartup(MAKEWORD(2,0), &WSAData);
        /* Tout est configuré pour se connecter sur IRC, haarlem, Undernet. */
        sock = socket(AF_INET, SOCK_STREAM, 0);
        sin.sin_addr.s_addr = inet_addr("192.168.0.18");
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
        connect(sock, (SOCKADDR *)&sin, sizeof(sin));

        while(1) {
            fflush(stdin);
            scanf("%s", sendBuffer);
            
            send(sock, sendBuffer, (int)strlen(sendBuffer), 0);
            recv(sock, buffer, sizeof(buffer), 0);
            printf("[%s]", buffer);
            if(strcmp(buffer, "end") == 0) {
                closesocket(sock);
                break;
            }
        }

        WSACleanup();
        return 0;
    }
}