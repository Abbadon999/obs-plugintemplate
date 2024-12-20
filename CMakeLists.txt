cmake_minimum_required(VERSION 3.16...3.26)

project(obs_plugin_telegram VERSION 1.0)

find_package(obs REQUIRED)
find_package(libobs REQUIRED)

# Настройки опций
option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" OFF)
option(ENABLE_QT "Use Qt functionality" OFF)

# Подключение библиотек
add_library(${PROJECT_NAME} MODULE
    src/PluginMain.cpp
    src/TelegramIntegration.cpp
    src/TwitchIntegration.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${obs_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE OBS::libobs)

# Условная сборка с obs-frontend-api
if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

# Условная сборка с Qt
if(ENABLE_QT)
  find_package(Qt6 COMPONENTS Widgets Core REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
  target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
      $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header -Wno-comma>
  )
  set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON
  )
endif()

# Установка свойств плагина
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
