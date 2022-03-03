# Install script for directory: /home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/json/allocator.h;/json/assertions.h;/json/config.h;/json/forwards.h;/json/json.h;/json/json_features.h;/json/reader.h;/json/value.h;/json/version.h;/json/writer.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/json" TYPE FILE FILES
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/allocator.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/assertions.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/config.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/forwards.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/json.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/json_features.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/reader.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/value.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/version.h"
    "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/json/writer.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/parallels/Stan/xforg/CodingCPlusPlus/Coding/JsonCppUsing/include/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
