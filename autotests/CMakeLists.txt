set(graphtest_SRCS graphtest.cpp)

add_executable( graphtest ${graphtest_SRCS})

target_link_libraries(graphtest
    hadwiger
    Qt5::Core
    Qt5::Test
)

add_test(graphtest graphtest)
