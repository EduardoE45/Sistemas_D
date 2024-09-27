// ClienteTexto.c
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Vincular la librería Ws2_32.lib en Windows
#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    int iResult;
    
    // Inicializar Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup falló: %d\n", iResult);
        return 1;
    }

    // Crear el socket
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Error al crear el socket: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5001);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Asociar el socket al puerto
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("Error en bind: %ld\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Escuchar conexiones
    if (listen(sockfd, 5) == SOCKET_ERROR) {
        printf("Error en listen: %ld\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    printf("Esperando conexiones en el puerto 5001...\n");

    struct sockaddr_in client_addr;
    int addr_size = sizeof(client_addr);
    SOCKET new_sock = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);
    if (new_sock == INVALID_SOCKET) {
        printf("Error en accept: %ld\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Ciclo para recibir números
    int numero;
    while (1) {
        int recvResult = recv(new_sock, (char*)&numero, sizeof(int), 0);
        if (recvResult <= 0) {
            printf("Error al recibir datos o conexión cerrada.\n");
            break;
        }

        printf("Número recibido: %d\n", numero);

        if (numero == 0) {
            printf("Terminando conexión.\n");
            break;
        }

        numero++; // Incrementar el número
        send(new_sock, (char*)&numero, sizeof(int), 0); // Enviar el número incrementado
    }

    // Cerrar el socket
    closesocket(new_sock);
    closesocket(sockfd);

    // Limpiar Winsock
    WSACleanup();

    return 0;
}

