cmake_minimum_required(VERSION 3.0.0)
project(db_lib)

set(CMAKE_CXX_STANDARD 17)
set(DB_LIB_LIBRARIES)
set(DB_LIB_INCLUDE_DIRS)

file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/mysql) 
target_link_libraries(${PROJECT_NAME} PUBLIC mysqlclient)

set(DB_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(DB_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)