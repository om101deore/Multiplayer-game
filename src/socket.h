#pragma once

#include "log.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <glm/glm.hpp>
#include <unistd.h>

class Socket {
public:
    // destructor
    virtual void onCleanup()
    {
        close(socket_desc);
        isConnected = false;
    }
    // return 0 on success else negative
    virtual int onLoad(int port, char* ip_addr = NULL)
    {
        Log(LogLevel::INFO, "INSIDE ON LOAD IN SOCKET CLASS");
        return 0;
    }

    // send message
    int send_message(glm::vec3 pos)
    {

        std::string msg = std::to_string(pos.x);
        msg += " " + std::to_string(pos.y);
        msg += " " + std::to_string(pos.z);

        if (send(socket_desc, msg.c_str(), msg.size(), 0) < 0) {
            Log(LogLevel::ERROR, "FAILED TO SEND MESSAGE");
            return -1;
        }

        return 0;
    }

    // recv message and write to this glm::vec3
    int recv_message(glm::vec3& pos)
    {
        char reply[100];
        if (recv(socket_desc, reply, 100, 0) < 0) {
            Log(LogLevel::ERROR, "FAILED TO RECV MESSAGE");
            return -1;
        }
        // todo: turn message into pos
        pos = strToVec3(reply);

        return 0;
    }

private:
    glm::vec3 strToVec3(const char reply[])
    {
        std::string arr[3];
        for (int i = 0, j = 0; reply[i] != '\0'; i++) {
            if (reply[i] == ' ') {
                j++;
                continue;
            }
            arr[j] += reply[i];
        }

        glm::vec3 pos;
        pos.x = std::stof(arr[0]);
        pos.y = std::stof(arr[1]);
        pos.z = std::stof(arr[2]);

        return pos;
    }

public:
    bool isHost;

    bool isConnected;
    int  socket_desc;
    // addr of opponent
    sockaddr_in connect_addr;

};
