cmake_minimum_required(VERSION 3.5)

project(qtWithCorba_sample LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -g")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Sql REQUIRED)

include_directories( inc )
include_directories(/usr/include/omniORB4 /usr/include/omnithread)

set(OMNIDLFILES
    inc/object.hh
    src/objectSK.cc
    inc/cpp2idlEntry.h
    src/cpp2idlEntry.cpp
)
set(CLIENT_HEADERS
    inc/EntriesModel.h
    inc/ModelManager.h
    inc/CorbaLoader.h
    )
set(CLIENT_SOURCES
    src/CorbaLoader.cpp
    src/EntriesModel.cpp
    src/ModelManager.cpp
    )
set(SERVER_HEADERS
    inc/Server.h
    inc/DBManager.h
    inc/Action.h
    inc/Servant.h
    )
set(SERVER_SOURCES
    src/DBManager.cpp
    src/Server.cpp
    src/Action.cpp
    src/Servant.cpp
    )
set(HEADERS
    inc/generate.h
    inc/Entry.h
    )
set(SOURCES
    src/generate.cpp
    src/Entry.cpp
    )

add_executable(Corba_Client
        client.cpp
        qml.qrc
        ${HEADERS}
        ${SOURCES}
        ${OMNIDLFILES}
        ${CLIENT_HEADERS}
        ${CLIENT_SOURCES}
)

target_link_libraries(Corba_Client
  PRIVATE Qt5::Core Qt5::Quick Qt5::Sql pthread omniORB4 omnithread
)


add_executable(Corba_Server
    server.cpp
    ${HEADERS}
    ${SOURCES}
    ${OMNIDLFILES}
    ${SERVER_HEADERS}
    ${SERVER_SOURCES}
)

target_link_libraries(Corba_Server
    PRIVATE Qt5::Core Qt5::Sql pthread omniORB4 omnithread)
