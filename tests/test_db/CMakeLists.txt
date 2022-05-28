cmake_minimum_required(VERSION 3.14)
project(test_db)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${DB_LIB_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${DB_LIB_LIBRARIES} GTest::GTest gtest_main)