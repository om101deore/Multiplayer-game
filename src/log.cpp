#include "log.h"

void Log(LogLevel e, const char* msg)
{
    std::string str = "\033[";
    str += std::to_string(e) + "m" ;

    switch (e) {
    case LogLevel::ERROR:
        str += "[ERROR]: ";
        break;

    case LogLevel::INFO:
        str += "[INFO]: ";
        break;

    case LogLevel::WARNING:
        str += "[WARNING]: ";
        break;
    }
    std::cout << str << msg << std::endl;
}
