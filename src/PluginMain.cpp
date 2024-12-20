// PluginMain.cpp - основной файл плагина
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <iostream>
#include <string>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs_plugin_telegram", "en-US")

// Прототипы функций
void create_ui_elements();
void on_button_pressed();

bool obs_module_load() {
    blog(LOG_INFO, "OBS Telegram Plugin loaded!");

    if (!obs_frontend_api_initialized()) {
        blog(LOG_ERROR, "Frontend API is not initialized!");
        return false;
    }

    // Создаем UI элементы
    create_ui_elements();

    return true;
}

void obs_module_unload() {
    blog(LOG_INFO, "OBS Telegram Plugin unloaded!");
}

// Функция для создания UI элементов
void create_ui_elements() {
    obs_frontend_push_ui_translation(obs_module_get_string);

    // Добавляем кнопку на панель инструментов
    obs_frontend_add_tools_menu_button(
        "Send Telegram Message", // Текст кнопки
        [](void *data) { on_button_pressed(); } // Обработчик события нажатия
    );

    obs_frontend_pop_ui_translation();
}

// Обработчик нажатия кнопки
void on_button_pressed() {
    blog(LOG_INFO, "Button clicked! Sending a message to Telegram...");

    // TODO: Реализовать отправку сообщения в Telegram
}
