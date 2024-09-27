// ServidorNumeros.c
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>

int main() {
    int sockfd, new_sock;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t addr_size;
    int numero;

    // Crear el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error creando el socket.\n");
        return 1;
    }

    // Configuración del servidor
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5001);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Asociar el socket al puerto
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error al asociar el socket.\n");
        return 1;
    }

    // Escuchar conexiones
    listen(sockfd, 5);
    printf("Esperando conexiones en el puerto 5001...\n");

    addr_size = sizeof(client_addr);
    new_sock = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
    if (new_sock < 0) {
        printf("Error al aceptar la conexión.\n");
        return 1;
    }

    // Ciclo para recibir números
    while (1) {
        recv(new_sock, &numero, sizeof(numero), 0);
        printf("Número recibido: %d\n", numero);

        if (numero == 0) {
            printf("Terminando conexión.\n");
            break;
        }

        numero++; // Incrementar el número
        send(new_sock, &numero, sizeof(numero), 0); // Enviar el número incrementado
    }

    // Cerrar el socket
    close(new_sock);
    close(sockfd);

    return 0;
}

