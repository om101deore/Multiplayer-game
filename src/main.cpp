#include "game.h"
#include "log.h"
#include "server.h"
#include "client.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

int main(int argc, char** argv)
{
    Game* g;

    if (argc < 2) {
        Log(LogLevel::ERROR, "SPECIFY TYPE OF APPLICATION (SERVER or CLIENT)");
        return -1;
    }

    if (strcmp(argv[1], "server") == 0) {
        g = new Game("server");

        if (argc != 3) {

            Log(LogLevel::ERROR, "INCORRECT ARGUMENTS FOR SERVER");
            return -1;
        }
        
        // socket is server
        g->gSocket = new Server();
        g->gSocket->onLoad(atoi(argv[2]));

    } else if (strcmp(argv[1], "client") == 0) {

        g = new Game("client");

        if (argc != 4) {
            Log(LogLevel::ERROR, "INCORRECT ARGUMENTS FOR CLIENT");
            return -1;
        }

        // socket is client
        g->gSocket = new Client();
        g->gSocket->onLoad(atoi(argv[2]), argv[3]);

    } else {
        Log(LogLevel::ERROR, "NOT ENOUGHT ARGUMENTS, READ README.md FOR HELP");
        return -1;
    }

    Log(LogLevel::INFO, "CONNECTION ESTABLISHED");

    g->onLoad();
    g->onLoop();
}
