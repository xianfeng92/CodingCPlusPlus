project(jsondemo)
cmake_minimum_required(VERSION 2.8)
# this is required
SET(CMAKE_SYSTEM_NAME Linux)
add_definitions(-DWIN_INTERFACE_CUSTOM)
add_definitions(-DDEBUG)


 SET(CMAKE_CXX_COMPILER  "g++")


if (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release")
endif ()

option(BUILD_LOCAL "Compile with local header files or resources" OFF)

# warning 重构代码需要把这些 warn 处理下
set(NO_WARN "-Wno-sign-compare -Wno-write-strings -Wno-unused-result -Wno-unused-function -Wno-unused-variable -Wno-deprecated-declarations -Wno-unused-but-set-variable")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NO_WARN}")

if (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "None")
    MESSAGE(STATUS "CMAKE_BUILD_TYPE is Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -pthread -O0  -fpermissive -fPIC -O0 -Wall -g2 -ggdb")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    MESSAGE(STATUS "CMAKE_BUILD_TYPE is Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O3 -fPIC -fpermissive")
elseif (CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
    MESSAGE(STATUS "CMAKE_BUILD_TYPE is MinSizeRel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O3 -fPIC -fpermissive")
else ()
    MESSAGE(STATUS "unknown CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -fPIC -O0 -pthread -Wall -g2 -ggdb")
endif ()

include_directories(
        ${PROJECT_SOURCE_DIR}/include/json
        ${PROJECT_SOURCE_DIR}/lib
)

link_directories(
        ${PROJECT_SOURCE_DIR}/include/json
        ${PROJECT_SOURCE_DIR}/lib
)

file(GLOB_RECURSE SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

message(STATUS "source file:${SOURCE_FILES}")

add_executable(jsondemo ${SOURCE_FILES})

target_link_libraries(jsondemo dl jsoncpp)