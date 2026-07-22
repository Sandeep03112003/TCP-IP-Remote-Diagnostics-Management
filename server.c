#include "common.h"

int main()
{
    // Create a TCP/IP socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket");
        return FAILURE;
    }
    printf("Socket Created Successfully\n");

    // Configure server IP address and port number
    struct sockaddr_in server_info;
    memset(&server_info, 0, sizeof(server_info));

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(5000);
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the socket to the configured IP and port
    if (bind(server_fd, (struct sockaddr *)&server_info, sizeof(server_info)) == -1)
    {
        perror("bind");
        close(server_fd);
        return FAILURE;
    }

    printf("Bind Successful\n");

    // Put the server socket into listening state
    if (listen(server_fd, BACKLOG) == -1)
    {
        perror("listen");
        close(server_fd);
        return FAILURE;
    }

    printf("Listening....\n");
    printf("Waiting for Client...\n");

    // Accept an incoming client connection
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1)
    {
        perror("accept");
        close(server_fd);
        return FAILURE;
    }

    printf("Client Connected\n");

    // Continuously process client requests
    while (1)
    {
        char buffer[1024] = {'\0'};

        // Receive command from client
        int n = recv(client_fd, buffer, sizeof(buffer), 0);

        if (n == -1)
        {
            perror("recv");
            break;
        }
        else if (n == 0)
        {
            printf("Client Disconnected\n");
            break;
        }

        buffer[n] = '\0';

        char command[100] = {'\0'};

        // Map client request to corresponding Linux command
        if (strcmp(buffer, "memory") == 0)
        {
            strcpy(command, "free -h");
        }
        else if (strcmp(buffer, "cpu") == 0)
        {
            strcpy(command, "top -bn1 | head -5");
        }
        else if (strcmp(buffer, "disk") == 0)
        {
            strcpy(command, "df -h");
        }
        else if (strcmp(buffer, "system") == 0)
        {
            strcpy(command, "uname -a");
        }
        else if (strcmp(buffer, "processes") == 0)
        {
            strcpy(command, "ps -ef");
        }
        // Extract PID and prepare kill command
        else if (strncmp(buffer, "kill", 4) == 0)
        {
            int pid;
            sscanf(buffer, "kill %d", &pid);

            printf("Command: Kill\n");
            printf("Pid = %d\n", pid);

            strcpy(command, buffer);
        }
        else
        {
            printf("Invalid Command Received\n");
            continue;
        }

        // Execute Linux command and capture its output
        FILE *ptr = popen(command, "r");
        if (ptr == NULL)
        {
            perror("popen");
            continue;
        }

        char response[MAX_RESPONSE_SIZE] = {'\0'};
        char line_buffer[1024];

        int total_size = 0;

        // Read complete command output into response buffer
        while (fgets(line_buffer, sizeof(line_buffer), ptr) != NULL)
        {
            strcat(response, line_buffer);
            total_size += strlen(line_buffer);
        }

        printf("Total size = %d\n", total_size);

        // Send total response size to the client first
        send(client_fd, &total_size, sizeof(total_size), 0);

        int iteration = 0;

        // Send the complete response until all bytes are transmitted
        while (iteration < total_size)
        {
            int bytes = send(client_fd,response + iteration,total_size - iteration,0);

            if (bytes <= 0)
            {
                break;
            }

            iteration += bytes;
        }

        // Close the command execution stream
        pclose(ptr);
    }

    // Release all socket resources
    close(client_fd);
    close(server_fd);

    return SUCCESS;
}
