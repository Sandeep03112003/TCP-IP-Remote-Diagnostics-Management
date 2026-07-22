#ifndef COMMON_H
#define COMMON_H

/* Standard Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Socket Header Files */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

/* Macros */
#define MAX_BUFFER_SIZE    8192
#define MAX_CMD_SIZE       100

#define SUCCESS            0
#define FAILURE           -1

#define BACKLOG            5
#define MAX_RESPONSE_SIZE 8192

void receive_server_response(int client_fd);

#endif
