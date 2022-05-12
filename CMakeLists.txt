cmake_minimum_required(VERSION 3.0.0)
project(navigator)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(search_lib)

message("SEARCH_LIB_INCLUDE_DIRS = ${SEARCH_LIB_INCLUDE_DIRS}")
message("SEARCH_LIB_LIBRARIES = ${SEARCH_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SEARCH_LIB_LIBRARIES})

add_subdirectory(tests)