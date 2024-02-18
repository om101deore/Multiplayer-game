#include "game.h"
#include <iostream>

int main(){
    std::cout<<"started running"<<std::endl;
    Game g;
    std::cout<<"just started running"<<std::endl;
    g.onLoad();
    g.onLoop();
}
