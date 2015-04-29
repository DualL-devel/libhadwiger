cmake_minimum_required(VERSION 2.6)
project(yagraphprogram)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(YaGraphProgram_SRCS YaGraphProgram.cpp main.cpp)

qt4_automoc(${YaGraphProgram_SRCS})
add_executable(yagraphprogram ${YaGraphProgram_SRCS})
target_link_libraries(yagraphprogram ${QT_QTCORE_LIBRARY})

install(TARGETS yagraphprogram RUNTIME DESTINATION bin)
