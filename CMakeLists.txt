cmake_minimum_required(VERSION 3.16...3.26)

# Включение файла инициализации
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)

# Установка проекта
project(${_name} VERSION ${_version})

# Опции
option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" ON)
option(ENABLE_QT "Use Qt functionality" ON)

# Включение базовых настроек
include(compilerconfig)
include(defaults)
include(helpers)

# Создание плагина
add_library(${CMAKE_PROJECT_NAME} MODULE)

# Подключение libobs
find_package(libobs REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

# Подключение obs-frontend-api
if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

# Подключение Qt
if(ENABLE_QT)
  find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
  
  # Настройка для автоматической обработки .ui, .moc и .qrc
  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON)

  # Подключение Qt библиотек
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)

  # Установка дополнительных опций компиляции
  target_compile_options(
    ${CMAKE_PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header
                                  -Wno-comma>)
endif()

# Указание исходников
target_sources(${CMAKE_PROJECT_NAME} PRIVATE 
    src/plugin-main.c           # Основной файл плагина
    src/PluginMain.cpp          # Код логики
    src/TelegramIntegration.cpp # Логика Telegram
    src/TwitchIntegration.cpp   # Логика Twitch
    src/interface.ui            # UI-файл для интерфейса
)

# Установка свойств плагина
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${_name})
