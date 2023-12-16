#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "server.h"
#include <unistd.h>

int bind_socket(int port)
{
    int sockfd;
    struct sockaddr_in server_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the specified port
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Socket opened on port %d\n", port);

    return sockfd;
}

void listen_on_socket(int sockfd)
{
    // Listen for incoming connections
    if (listen(sockfd, 5) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
}

int accept_client_conn(int sockfd)
{
    // Accept incoming connection
    int client_sockfd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sockfd < 0)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    return client_sockfd;
}

void read_from_socket(int client_sockfd, char *buffer, int buffer_size)
{
    // Read data from the socket
    int bytes_read = recv(client_sockfd, buffer, buffer_size, 0);
    if (bytes_read < 0)
    {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }
}

void send_to_socket(int client_sockfd, char *response)
{
    // Send the HTML response back
    int bytes_sent = send(client_sockfd, response, strlen(response), 0);
    if (bytes_sent < 0)
    {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }
}

int listen_and_serve_http()
{
    int sockfd = bind_socket(8080);
    listen_on_socket(sockfd);
    char buffer[1024];
    while (1)
    {
        int client_sockfd = accept_client_conn(sockfd);
        read_from_socket(client_sockfd, buffer, sizeof(buffer));

        // if the request body contains ?query=stop then stop the server
        if (strstr(buffer, "?query=stop") != NULL)
        {
            printf("Stopping server\n");
            char *response = "HTTP/1.1 200 GOING_AWAY\r\nContent-Type: text/html\r\n\r\nGOING AWAY";
            send_to_socket(client_sockfd, response);
            close(client_sockfd);
            break;
        }

        // Prepare the HTML response
        char response[2048];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", buffer);
        send_to_socket(client_sockfd, response);
        printf("Sent Mirror\n");
        close(client_sockfd);
    }
    close(sockfd);
    return 0;
}
