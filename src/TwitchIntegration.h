#pragma once
#include <string>

class TwitchIntegration {
public:
    static bool initialize(const std::string& clientId, const std::string& clientSecret);
    static void shutdown();
};
