#pragma once

#include "log.h"
#include "socket.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

class Client : public Socket {
public:
    // return < 0 if error
    int onLoad(int port, char* ip_addr) override
    {

        isHost = false;

        socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_desc < 0) {
            Log(LogLevel::ERROR, "FAILED TO CREATE SOCKET");
            return -1;
        }

        Log(LogLevel::INFO, "CLIENT SOCKET CREATED SUCCESSFULLY");

        connect_addr.sin_addr.s_addr = inet_addr(ip_addr);
        connect_addr.sin_family      = AF_INET;
        connect_addr.sin_port        = htons(port);

        if (connect(socket_desc, (sockaddr*)&connect_addr, sizeof(connect_addr)) < 0) {
            Log(LogLevel::ERROR, "FAILED TO CONNECT");
            return -1;
        }

        Log(LogLevel::INFO, "CONNECTION ESTABLISHED");
        isConnected = true;
        return 0;
    }

};
