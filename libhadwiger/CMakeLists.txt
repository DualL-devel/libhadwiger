set(hadwiger_SRCS graph.h graph.cpp)

add_library(hadwiger SHARED ${hadwiger_SRCS})
target_link_libraries(hadwiger 
    Qt5::Core
)

target_include_directories(hadwiger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
