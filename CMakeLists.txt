cmake_minimum_required(VERSION 3.5)
project(IUT_ClientServeur_MiniProjet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(COMMON_FILES src/common/cause.cpp src/common/socket.cpp src/common/util.cpp)
set(SOURCE_FILES_SERVER src/server/pool.cpp src/server/server.cpp)
set(SOURCE_FILES_CLIENT src/client/client.cpp)

add_executable(server.bin ${SOURCE_FILES_SERVER} ${COMMON_FILES})
add_executable(client.bin ${SOURCE_FILES_CLIENT} ${COMMON_FILES})