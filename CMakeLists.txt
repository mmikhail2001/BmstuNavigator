
cmake_minimum_required(VERSION 2.8.4)
project(main)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(search_lib)
add_subdirectory(tgbot_lib)
add_subdirectory(db_lib)
add_subdirectory(entities_lib)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(Boost_USE_MULTITHREADED ON)

# include_directories(include)

# set(TGBOT_LIB  ${PROJECT_SOURCE_DIR}/include/tg_bot.h ${PROJECT_SOURCE_DIR}/lib/tg_bot.cpp)
# add_library(TGBOT_LIB STATIC ${TGBOT_LIB})
# target_include_directories(TGBOT_LIB PUBLIC ${PROJECT_SOURCE_DIR}/include)

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

# target_link_libraries(tgbot_lib PRIVATE ${SEARCH_LIB_LIBRARIES})
# target_link_libraries(${TGBOT_LIB_LIBRARIES} PRIVATE ${SEARCH_LIB_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${TGBOT_LIB_INCLUDE_DIRS})
# target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_LIB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${DB_LIB_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${TGBOT_LIB_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PRIVATE /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${DB_LIB_LIBRARIES} ${SEARCH_LIB_LIBRARIES} ${ENTITIES_LIB_LIBRARIES})



add_subdirectory(tests)

# ------
# find_package(GTest REQUIRED)
# ------

# find_package(GMock REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# ------
# set(GMOCK_INCLUDE_DIRS /usr/include/gmock)

# set(GMOCK_BOTH_LIBRARIES /usr/local/lib/libgmock.a /usr/local/lib/libgmock_main.a /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)
# ------


# usr\home\mikhail\googletest\googlemock\include\gmock\gmock.h
# home/mikhail/googletest/build/lib
# set(GMOCK_INCLUDE_DIRS usr/home/mikhail/googletest/googlemock/include/gmock)
# set(GTEST_INCLUDE_DIRS usr/home/mikhail/googletest/googletest/include/gtest)
# set(GMOCK_BOTH_LIBRARIES /usr/home/mikhail/googletest/build/lib/libgmock.a 
# /usr/home/mikhail/googletest/build/lib/libgmock_main.a
#  /usr/home/mikhail/googletest/build/lib/libgtest.a 
#  /usr/home/mikhail/googletest/build/lib/libgtest_main.a)

# ------
# include_directories(${GMOCK_INCLUDE_DIRS})
# include_directories(${GTEST_INCLUDE_DIRS})
# add_executable(tests tests/gtests.cpp)
# target_link_libraries(tests ${GMOCK_BOTH_LIBRARIES} TGBOT_LIB GTest::GTest gtest_main)
# ------





# target_link_libraries(tests ${GMOCK_LIBRARIES} TGBOT_LIB GTest::GTest gtest_main)
# target_link_libraries(tests gmock)
