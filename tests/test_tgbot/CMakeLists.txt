cmake_minimum_required(VERSION 3.14)
project(test_tgbot)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${TGBOT_LIB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_LIB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${DB_LIB_INCLUDE_DIRS})

# gmock
target_include_directories(${PROJECT_NAME} PUBLIC ${GMOCK_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${TGBOT_LIB_LIBRARIES} ${SEARCH_LIB_LIBRARIES} ${DB_LIB_LIBRARIES} ${GMOCK_BOTH_LIBRARIES} GTest::GTest gtest_main)

target_link_libraries(${PROJECT_NAME} PRIVATE /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})