#include <obs-module.h>
#include "TelegramIntegration.h"
#include "TwitchIntegration.h"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs_plugin_telegram", "en-US")

bool obs_module_load() {
    blog(LOG_INFO, "OBS Telegram Plugin loaded!");

    // Инициализация Telegram
    if (!TelegramIntegration::initialize("TELEGRAM_BOT_TOKEN")) {
        blog(LOG_ERROR, "Failed to initialize Telegram integration!");
        return false;
    }

    // Инициализация Twitch OAuth
    if (!TwitchIntegration::initialize("TWITCH_CLIENT_ID", "TWITCH_CLIENT_SECRET")) {
        blog(LOG_ERROR, "Failed to initialize Twitch integration!");
        return false;
    }

    return true;
}

void obs_module_unload() {
    TelegramIntegration::shutdown();
    TwitchIntegration::shutdown();
    blog(LOG_INFO, "OBS Telegram Plugin unloaded!");
}
