set(libGraph_SRCS graph.h graph.cpp)

add_library(libhadwiger SHARED ${libGraph_SRCS})
target_link_libraries(libhadwiger 
    Qt5::Core
)

target_include_directories(libhadwiger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
