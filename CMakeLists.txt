cmake_minimum_required(VERSION 3.10)
project(CPP_LAB_4_Word_Count)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
find_package(Threads REQUIRED)
find_package(LibArchive REQUIRED)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(one_thread_solution sources/one_thread_solution.cpp sources/helpers.cpp sources/word_count.cpp  headers/archive_functions.h sources/archive_functions.cpp)
add_executable(multi_thread_solution sources/multi_thread_solution.cpp sources/helpers.cpp sources/word_count.cpp headers/helpers.h headers/archive_functions.h sources/archive_functions.cpp)
target_link_libraries(one_thread_solution ${LibArchive_LIBRARIES})
target_link_libraries(multi_thread_solution ${LibArchive_LIBRARIES})

