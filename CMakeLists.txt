cmake_minimum_required(VERSION 3.5)

project(qtWithCorba_sample LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Sql REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories( inc ${Boost_INCLUDE_DIRS})
include_directories(/usr/include/omniORB4 /usr/include/omnithread)

set(OMNIDFILES
    inc/object.hh
    src/objectSK.cc
)
set(HEADERS
    inc/ModelManager.h
    inc/EntriesModel.h
    inc/generate.h
    inc/DBManager.h
    inc/Entry.h
    inc/Client.h
    inc/Server.h)
set(SOURCES
    src/ModelManager.cpp
    src/EntriesModel.cpp
    src/generate.cpp
    src/DBManager.cpp
    src/Entry.cpp
    src/Client.cpp
    src/Server.cpp)

add_executable(Corba_Client
        client.cpp
        qml.qrc
        ${HEADERS}
        ${SOURCES}
        ${OMNIDFILES}
)

target_link_libraries(Corba_Client
  PRIVATE Qt5::Core Qt5::Quick Qt5::Sql pthread omniORB4 omnithread
)


add_executable(Corba_Server
    server.cpp
    ${HEADERS}
    ${SOURCES}
    ${OMNIDFILES}
)

target_link_libraries(Corba_Server
    PRIVATE Qt5::Core Qt5::Sql pthread omniORB4 omnithread)

add_executable(tests
    test/all_unit_tests.cpp
    ${HEADERS}
    ${SOURCES}
    ${OMNIDFILES}
)

target_link_libraries(tests
    PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Sql
    ${Boost_LIBRARIES} pthread omniORB4 omnithread)

enable_testing()

add_test(NAME Tests COMMAND tests)
