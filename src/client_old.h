#include <cstring>
#include <glm/fwd.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <glm/glm.hpp>

class Client {
public:

    Client(std::string ip_address, int port_no)
    {
        // AF_INET - address family ipv4
        // SOCK_STREAM - TCP
        // 0 [ or IPPROTO_IP This is IP protocol]

        std::cout << "before socket" << std::endl;

        socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_desc < 0) {
            std::cout << "could not create socket" << std::endl;
            //  exit(-1);
        }
        std::cout << "after socket" << std::endl;

        // sockaddr_in
        // IPv4 AF_INET sockets:
        // struct sockaddr_in {
        //     short            sin_family;   // e.g. AF_INET, AF_INET6
        //     unsigned short   sin_port;     // e.g. htons(3490)
        //     struct in_addr   sin_addr;     // see struct in_addr, below
        //     char             sin_zero[8];  // zero this if you want to
        // };

        // struct in_addr {
        //     unsigned long s_addr;          // load with inet_pton()
        // };

        // struct sockaddr {
        //     unsigned short    sa_family;    // address family, AF_xxx
        //     char              sa_data[14];  // 14 bytes of protocol address
        // };

        // address of server where we want to connect
        server_addr.sin_addr.s_addr = inet_addr(ip_address.c_str());
        server_addr.sin_family      = AF_INET;
        server_addr.sin_port        = htons(port_no);

    }

    int connect_serv()
    {

        if (connect(socket_desc, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            return -1;
        }

        return 0;
    }

    int send_msg(glm::vec3 pos)
    {
        std::string msg = std::to_string(pos.x);
        msg += " " + std::to_string(pos.y);
        msg += " " + std::to_string(pos.z);


        // send data
        if (send(socket_desc, msg.c_str(), msg.size(), 0) < 0) {
            return -1;
        }

        return 0;
    }

    int recv_msg()
    {
        char reply[2000];
        server_reply.clear();
        if (recv(socket_desc, reply, sizeof(reply), 0) < 0) {
            return -1;
        }


        std::cout<<reply<<std::endl;
        server_reply = reply;


        return 0;
    }

    void print_reply()
    {
        std::cout << server_reply << std::endl;
    }


private:
    // fd of socket on this device
    int socket_desc;

    // info of server where we want to connect
    sockaddr_in server_addr;

    // reply will be stored here
    std::string server_reply;
};
