
add_executable(cexp
    "main.c"
    "exp_list.c")
target_include_directories(cexp PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
add_subdirectory(include)
add_subdirectory(sockets)
