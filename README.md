# TCP/IP Based Remote Diagnostics & Management Solution

## Overview

This project is a Linux-based client-server application developed in **C** using **TCP/IP Socket Programming**. It demonstrates how remote diagnostics and basic process management can be performed over a network.

The project was developed as part of my **Advanced Embedded Systems Training at Emertxe Information Technologies** to gain hands-on experience with Linux system programming, socket programming, and client-server communication.

---

## Features

- Monitor Memory Usage
- Monitor CPU Usage
- Monitor Disk Usage
- Retrieve System Information
- Display Running Processes
- Terminate a Process Remotely using PID

---

## Technologies Used

- C Programming
- Linux System Programming
- TCP/IP Socket Programming
- Linux System Calls
- Process Management

---

## Project Structure

```
TCP-IP-Remote-Diagnostics-Management/
│
├── client.c
├── server.c
├── common.h
└── README.md
```

---

## How It Works

1. The server creates a TCP socket and waits for client connections.
2. The client connects to the server over the network.
3. The client sends a request for monitoring or process management.
4. The server executes the corresponding Linux command.
5. The server sends the command output back to the client.
6. The client displays the received information.

---

## Compilation

Compile the server:

```bash
gcc server.c -o server
```

Compile the client:

```bash
gcc client.c -o client
```

---

## Execution

Start the server:

```bash
./server
```

Run the client in another terminal:

```bash
./client
```

---

## Learning Outcomes

This project helped me gain practical experience in:

- Client-Server Architecture
- TCP/IP Socket Programming
- Linux System Calls
- Remote Command Execution
- Process Management
- Linux System Programming

---

## Future Enhancements

- Multi-client support
- Secure authentication
- Graphical user interface (GUI)

---

## Author

**Sandeep Gowd Matta**

B.Tech (Electrical & Electronics Engineering)

Advanced Embedded Systems Trainee

Emertxe Information Technologies
