cmake_minimum_required(VERSION 3.14)
project(test_search)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_LIB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${DB_LIB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${ENTITIES_LIB_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SEARCH_LIB_LIBRARIES} ${DB_LIB_LIBRARIES} ${ENTITIES_LIB_LIBRARIES} GTest::GTest gtest_main)