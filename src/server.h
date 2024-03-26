#pragma once

#include "log.h"
#include "socket.h"
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Server : public Socket {
public:
    void onClean(){
        isConnected = false;
        close(socket_desc);
        close(serv_socket_desc);

    }
    int onLoad(int port, char* ip_addr) override
    {
        isHost = true;

        serv_socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        if (serv_socket_desc < 0) {
            Log(LogLevel::ERROR, "FAILED TO CREATE SERVER SOCKET");
            return -1;
        }
        Log(LogLevel::INFO, "SUCCESSFUL SERVER SOCKET CREATED");

        serv_addr.sin_family      = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port        = htons(port);

        // binding port
        if (bind(serv_socket_desc, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            Log(LogLevel::ERROR, "FAILED TO BIND SOCKET");
            return -1;
        }

        Log(LogLevel::INFO, "BIND SUCCESSFUL");

        // listen server
        if (listen(serv_socket_desc, 1) < 0) {
            Log(LogLevel::ERROR, "FAILED ON LISTEN");
            return -1;
        }

        int c = sizeof(sockaddr_in);

        socket_desc = accept(serv_socket_desc, (sockaddr*)&connect_addr, (socklen_t*)&c);

        if (socket_desc < 0) {
            Log(LogLevel::ERROR, "");
            perror("FAILED TO ACCEPT");
            return -1;
        }
        Log(LogLevel::INFO, "CONNECTED TO CLIENT");

        isConnected = true;

        return 0;
    }

private:
    sockaddr_in serv_addr;
    int         serv_socket_desc;
};
