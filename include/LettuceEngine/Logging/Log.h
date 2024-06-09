#pragma once
#include <stdio.h>
#include <string>
#include <iostream>

class Log {
    public:
        static void CustomRayLibLog(int msgType, const char* text, va_list args);
        static void Info(std::string message);
        static void Warning(std::string message);
        static void Error(std::string message);
        static void Debug(std::string message);
    private:
        static void Raw(std::string message);
};