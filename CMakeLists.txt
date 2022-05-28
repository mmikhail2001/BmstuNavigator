
cmake_minimum_required(VERSION 2.8.4)
project(main)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(search_lib)
add_subdirectory(tgbot_lib)
add_subdirectory(db_lib)
add_subdirectory(entities_lib)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(Boost_USE_MULTITHREADED ON)


find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(tgbot_lib PUBLIC ${DB_LIB_INCLUDE_DIRS})
target_include_directories(tgbot_lib PUBLIC ${SEARCH_LIB_INCLUDE_DIRS})
target_include_directories(tgbot_lib PUBLIC ${ENTITIES_LIB_INCLUDE_DIRS})

target_include_directories(search_lib PUBLIC ${DB_LIB_INCLUDE_DIRS})
target_include_directories(search_lib PUBLIC ${ENTITIES_LIB_INCLUDE_DIRS})

target_include_directories(db_lib PUBLIC ${ENTITIES_LIB_INCLUDE_DIRS})


target_include_directories(${PROJECT_NAME} PUBLIC ${TGBOT_LIB_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${DB_LIB_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${TGBOT_LIB_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PRIVATE /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${DB_LIB_LIBRARIES} ${SEARCH_LIB_LIBRARIES} ${ENTITIES_LIB_LIBRARIES})



add_subdirectory(tests)
