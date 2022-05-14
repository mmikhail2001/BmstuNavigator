cmake_minimum_required(VERSION 2.8.4)
project(tgbot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(Boost_USE_MULTITHREADED ON)

include_directories(include)

set(TGBOT_LIB  ${PROJECT_SOURCE_DIR}/include/tg_bot.h ${PROJECT_SOURCE_DIR}/lib/tg_bot.cpp)
add_library(TGBOT_LIB STATIC ${TGBOT_LIB})
target_include_directories(TGBOT_LIB PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(tgbot main.cpp)

target_link_libraries(tgbot PRIVATE TGBOT_LIB)
target_link_libraries(tgbot /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

find_package(GTest REQUIRED)

set(GMOCK_INCLUDE_DIRS /usr/include/gmock)

set(GMOCK_BOTH_LIBRARIES /usr/local/lib/libgmock.a /usr/local/lib/libgmock_main.a /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)



include_directories(${GMOCK_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests tests/gtests.cpp)
target_link_libraries(tests ${GMOCK_BOTH_LIBRARIES} TGBOT_LIB GTest::GTest gtest_main)
