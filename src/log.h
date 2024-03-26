#pragma once
#include <iostream>

enum LogLevel {
    ERROR = 31,
    INFO,
    WARNING
};

void Log(LogLevel e, const char* msg);
