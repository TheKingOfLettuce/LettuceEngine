#include "LettuceEngine/Logging/Log.h"

void Log::CustomRayLibLog(int msgType, const char* text, va_list args) {
    switch (msgType)
    {
        case 3: printf("[INFO] "); break;
        case 5: printf("[ERROR] "); break;
        case 4: printf("[WARN] "); break;
        case 2: printf("[DEBUG] "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}

void Log::Info(std::string message) {
    message.insert(0, "[INFO] ");
    Raw(message);
}

void Log::Warning(std::string message) {
    message.insert(0, "[WARN] ");
    Raw(message);
}

void Log::Error(std::string message) {
    message.insert(0, "[ERROR] ");
    Raw(message);
}

void Log::Debug(std::string message) {
    message.insert(0, "[DEBUG] ");
    Raw(message);
}

void Log::Raw(std::string message) {
    message.append("\n");
    std::cout << message.c_str();
}