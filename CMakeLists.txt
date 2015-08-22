cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(yagraphprogram)

set(QT_MIN_VERSION "5.3.0")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS -std=c++11 ${CMAKE_CXX_FLAGS})

set_property(GLOBAL PROPERTY CXX_STANDARD 11)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Test)

target_link_libraries(yagraphprogram
    Qt5::Core
    libhadwiger
)

install(TARGETS yagraphprogram RUNTIME DESTINATION bin)

add_subdirectory(libhadwiger)
add_subdirectory(autotests)
