#include <obs-module.h>
#include <iostream>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs_plugin_telegram", "en-US")

bool obs_module_load() {
    blog(LOG_INFO, "OBS Telegram Plugin loaded!");
    // Здесь можно добавить функционал Telegram API
    return true;
}

void obs_module_unload() {
    blog(LOG_INFO, "OBS Telegram Plugin unloaded!");
}
