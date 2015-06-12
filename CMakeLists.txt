cmake_minimum_required(VERSION 2.6)
project(yagraphprogram)
cmake_policy(SET CMP0028 OLD)
find_package(Qt5 REQUIRED COMPONENTS Core)

include_directories(${Qt5Core_INCLUDE_DIRS})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(YaGraphProgram_SRCS main.cpp graph.cpp)

add_executable(yagraphprogram ${YaGraphProgram_SRCS})
target_link_libraries(yagraphprogram Qt5::Core)

install(TARGETS yagraphprogram RUNTIME DESTINATION bin)
