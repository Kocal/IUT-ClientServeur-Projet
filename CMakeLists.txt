cmake_minimum_required(VERSION 3.5)
project(IUT_ClientServeur_MiniProjet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(COMMON_FILES src/common/jsoncpp.cpp src/common/cause.cpp src/common/socket.cpp src/common/util.cpp src/common/User.cpp src/common/User.h src/common/protocol.h)
set(SOURCE_FILES_SERVER src/server/Pools.cpp src/server/server.cpp src/server/Pool.cpp src/server/Pool.h)
set(SOURCE_FILES_CLIENT src/client/client.cpp)

find_package(Threads)

add_executable(server.bin ${SOURCE_FILES_SERVER} ${COMMON_FILES})
add_executable(client.bin ${SOURCE_FILES_CLIENT} ${COMMON_FILES})

target_link_libraries(server.bin ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(client.bin ${CMAKE_THREAD_LIBS_INIT})
