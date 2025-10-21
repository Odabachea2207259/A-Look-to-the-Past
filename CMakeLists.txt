cmake_minimum_required(VERSION 3.20)
project(CimaEngine3v LANGUAGES CXX)

set(BIN "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN}/${CMAKE_BUILD_TYPE}")

add_compile_definitions(ASSETS="${CMAKE_SOURCE_DIR}/assets")
#bandera para DEBUG O RELEASE
add_compile_definitions("DEBUG=$<CONFIG:Debug>")

#Descargar las dependencias (IMGUI y SFML)
message("Descargando SFML")
include(FetchContent)
if(WIN32)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY http://github.com/SFML/SFML.git
    GIT_TAG 3.0.x)
FetchContent_MakeAvailable(SFML)
else()
    find_package(SFML 3 COMPONENTS System Window Graphics Audio REQUIRED)
endif()
message("Descargando IMGUI")

FetchContent_Declare(
    imgui
    GIT_REPOSITORY http://github.com/ocornut/imgui.git
    GIT_TAG v1.91.1-docking)
FetchContent_MakeAvailable(imgui)

message("Descargando ImguiSFML")

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY http://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0)

message("Descargando JSON")

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

#target_link_libraries(foo PRIVATE nlohmann_json::nlohmann_json)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui-sfml)
#incluir los headers
include_directories(${SFML_INCLUDE_DIRS})
include_directories(${IMGUI_DIR})
#include_directories(${S_INCLUDE_DIRS})

#incluir los folders
add_subdirectory(src)


#ligar las librerias
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    SFML::System SFML::Window SFML::Graphics SFML::Audio
    ImGui-SFML::ImGui-SFML nlohmann_json::nlohmann_json
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("debug")
    add_compile_options((-ggdb -Wall -g -Wextra))
else()
    add_compile_options(-O2)
endif()

#asignar el estandar
target_compile_features(CimaEngine3v PUBLIC cxx_std_17)
