#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // Include the <unistd.h> header file for the close() function
#include <string.h>

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the specified port
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Socket opened on port 8080\n");

    // Listen for incoming connections
    if (listen(sockfd, 5) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1)
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

        // Read data from the socket
        int bytes_read = recv(client_sockfd, buffer, sizeof(buffer), 0);
        if (bytes_read < 0)
        {
            perror("Read failed");
            exit(EXIT_FAILURE);
        }

        // if the request body contains ?query=stop then stop the server
        if (strstr(buffer, "?query=stop") != NULL)
        {
            printf("Stopping server\n");
            char *response = "HTTP/1.1 200 GOING_AWAY\r\nContent-Type: text/html\r\n\r\nGOING AWAY";
            int bytes_sent = send(client_sockfd, response, strlen(response), 0);
            if (bytes_sent < 0)
            {
                perror("Send failed");
                exit(EXIT_FAILURE);
            }
            close(sockfd);
            exit(EXIT_SUCCESS);
        }

        // Prepare the HTML response
        char response[2048];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", buffer);

        // Send the HTML response back
        int bytes_sent = send(client_sockfd, response, strlen(response), 0);
        if (bytes_sent < 0)
        {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        printf("Sent Mirror\n");

        // Close the client connection
        close(client_sockfd);
    }
    close(sockfd);

    return 0;
}
