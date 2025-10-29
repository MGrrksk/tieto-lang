add_executable(tietoc src/main.cpp src/lexer.cpp)
target_include_directories(tietoc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tietoc PRIVATE common)