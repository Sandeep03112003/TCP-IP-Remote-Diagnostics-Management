#include "common.h"

int main()
{
    // Create a TCP/IP socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        perror("socket");
        return FAILURE;
    }

    // Configure server IP address and port number
    struct sockaddr_in server_info;
    memset(&server_info, 0, sizeof(server_info));

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(5000);
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Establish connection with the server
    if (connect(client_fd, (struct sockaddr *)&server_info, sizeof(server_info)) == -1)
    {
        perror("connect");
        close(client_fd);
        return FAILURE;
    }

    printf("Connected to server Successfully\n");

    int main_choice, choice;
    int monitoring_done = 0;

    // Display main menu continuously until user exits
    while (1)
    {
        printf("\n==============================\n");
        printf("      REMOTE MANAGEMENT\n");
        printf("==============================\n");
        printf("1. Monitoring\n");
        printf("2. Process Management\n");
        printf("3. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &main_choice);

        switch (main_choice)
        {
        case 1:

            // Monitoring submenu
            while (1)
            {
                printf("\n========== Monitoring ==========\n");
                printf("1. Memory Usage\n");
                printf("2. CPU Usage\n");
                printf("3. Disk Usage\n");
                printf("4. System Information\n");
                printf("5. Back\n");
                printf("Enter your choice : ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:

                    // Request memory usage information
                    send(client_fd, "memory", 6, 0);
                    receive_server_response(client_fd);
                    monitoring_done = 1;
                    break;

                case 2:

                    // Request CPU usage information
                    send(client_fd, "cpu", 3, 0);
                    receive_server_response(client_fd);
                    monitoring_done = 1;
                    break;

                case 3:

                    // Request disk usage information
                    send(client_fd, "disk", 4, 0);
                    receive_server_response(client_fd);
                    monitoring_done = 1;
                    break;

                case 4:

                    // Request system information
                    send(client_fd, "system", 6, 0);
                    receive_server_response(client_fd);
                    monitoring_done = 1;
                    break;

                case 5:
                    break;

                default:
                    printf("Invalid Choice\n");
                }

                if (choice == 5)
                    break;
            }

            break;

        case 2:

            // Allow process management only after monitoring
            if (!monitoring_done)
            {
                printf("\n=============================================\n");
                printf(" Please perform Monitoring first.\n");
                printf(" Monitoring helps identify the system issue.\n");
                printf("=============================================\n");
                break;
            }

            // Process management submenu
            while (1)
            {
                printf("\n====== Process Management ======\n");
                printf("1. Show Running Processes\n");
                printf("2. Kill Process\n");
                printf("3. Back\n");
                printf("Enter your choice : ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:

                    // Request list of running processes
                    send(client_fd, "processes", 9, 0);
                    receive_server_response(client_fd);
                    break;

                case 2:

                    // Read PID from user and send kill request
                    int pid;
                    printf("Enter the PID: ");
                    scanf("%d", &pid);

                    char kill_buffer[100];
                    sprintf(kill_buffer, "kill %d", pid);

                    send(client_fd, kill_buffer, strlen(kill_buffer), 0);
                    receive_server_response(client_fd);
                    break;

                case 3:
                    break;

                default:
                    printf("Invalid Choice\n");
                }

                if (choice == 3)
                    break;
            }

            break;

        case 3:

            // Close connection and terminate client
            close(client_fd);
            return SUCCESS;

        default:
            printf("Invalid Choice\n");
        }
    }

    // Release socket resource
    close(client_fd);
    return SUCCESS;
}

// Receive complete response from server
void receive_server_response(int client_fd)
{
    int total_size;

    // Receive total size of server response
    int n = recv(client_fd, &total_size, sizeof(total_size), 0);
    if (n == -1)
    {
        perror("recv");
        return;
    }

    printf("\nReceived total size = %d\n\n", total_size);

    char response[MAX_RESPONSE_SIZE] = {'\0'};
    int size = 0;
    char line_buffer[1025] = {'\0'};

    // Receive complete response until expected size is reached
    while (size < total_size)
    {
        int bytes = recv(client_fd, line_buffer,(total_size - size) < 1024 ? (total_size - size) : 1024,0);

        if (bytes > 0)
        {
            line_buffer[bytes] = '\0';
            strcat(response, line_buffer);
            size += bytes;
        }
        else
        {
            break;
        }
    }

    // Display server response
    printf("%s\n", response);
}
