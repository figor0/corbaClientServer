cmake_minimum_required(VERSION 3.5)

project(clientSide LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories( inc )

set(HEADERS
    inc/object.hh
)
set(SOURCES
    src/objectSK.cc
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set(${PROJECT_NAME}_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/inc PARENT_SCOPE)
