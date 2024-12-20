#pragma once
#include <string>

class TelegramIntegration {
public:
    static bool initialize(const std::string& botToken);
    static void shutdown();
};
