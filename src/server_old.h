#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <glm/glm.hpp>

class Server {
public:
    Server(int port)
        : port_no(port)
    {

        // create socket
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_desc == -1) {
            std::cout << "failed to create socket" << std::endl;
        }
        std::cout << "socket done" << std::endl;

        server_addr.sin_family      = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port        = htons(port);
    }

    int bind_port()
    {
        if (bind(socket_desc, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            return -1;
        }
        return 0;
    }

    void listen_server()
    {
        std::cout << "listening" << std::endl;
        listen(socket_desc, 1);
    }

    int accept_request()
    {
        int c           = sizeof(sockaddr_in);
        cli_socket_desc = accept(socket_desc, (sockaddr*)&client_addr, (socklen_t*)&c);

        if (cli_socket_desc < 0) {
            perror("failed to accept");
            return -1;
        }
        char* ip = inet_ntoa(client_addr.sin_addr);

        std::cout << ip << std::endl;

        std::cout << "connection accepted" << std::endl;

        return 0;
    }

    int send_message(glm::vec3 pos)
    {
        std::string msg = std::to_string(pos.x);
        msg += " " + std::to_string(pos.y);
        msg += " " + std::to_string(pos.z);

        send(cli_socket_desc, msg.c_str(), msg.size(), 0);
        return 0;
    }

    int recv_message()
    {
        char reply[200];
        client_message.clear();
        
        if (recv(cli_socket_desc, reply, 200, 0) < 0) {
            std::cout << "failed to recv" << std::endl;
            return -1;
        }
        client_message = reply;

        std::cout << "recv success" << std::endl;
        std::cout << client_message << std::endl;
        return 0;
    }

private:
    int port_no;

    int socket_desc;
    int cli_socket_desc;

    sockaddr_in server_addr;
    sockaddr_in client_addr;

    std::string client_message;
};
