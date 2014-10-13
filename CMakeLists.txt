cmake_minimum_required(VERSION 2.8.11)

project(Elsock)

set(PROJECT_VERSION 0.0.1)

set(LIB_NAME "${PROJECT_NAME}")
set(APP_NAME "${PROJECT_NAME}Controller")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


file(GLOB_RECURSE APP_SRC "src/app/*.cpp")
file(GLOB_RECURSE APP_HDR "include/app/*.h")
file(GLOB_RECURSE APP_UI "ui/*.ui")
file(GLOB_RECURSE LIB_SRC "src/api/*.cpp")
file(GLOB_RECURSE LIB_HDR "include/api/*.h")

include_directories("${PROJECT_SOURCE_DIR}/include")


find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

qt5_wrap_ui(UI_HDR ${APP_UI})

add_definitions(-DELSOCK_VERSION="${PROJECT_VERSION}")
add_definitions(-Wall -Wextra -pedantic)


add_library(${LIB_NAME} STATIC ${LIB_SRC} ${LIB_HDR})
add_executable(${APP_NAME} ${APP_SRC} ${APP_UI} ${APP_HDR})

target_link_libraries(${APP_NAME} ${LIB_NAME})
qt5_use_modules(${LIB_NAME} Network)
qt5_use_modules(${APP_NAME} Widgets)
