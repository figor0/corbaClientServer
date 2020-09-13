cmake_minimum_required(VERSION 3.5)

project(qtWithCorba_sample LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -g")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Sql REQUIRED)

add_subdirectory(lib/clientSide)
include_directories(${clientSide_INCLUDE})
add_subdirectory(lib/serverSide)
include_directories(${serverSide_INCLUDE})

include_directories( inc )
include_directories(/usr/include/omniORB4 /usr/include/omnithread)

set(CLIENT_HEADERS
    inc/EntriesModel.h
    inc/ModelManager.h
    inc/CorbaLoader.h
    inc/PhoneGeneral.h
)
set(CLIENT_SOURCES
    src/CorbaLoader.cpp
    src/EntriesModel.cpp
    src/ModelManager.cpp
)
set(SERVER_HEADERS
    inc/Server.h
    inc/DBManager.h
    inc/generate.h
)
set(SERVER_SOURCES
    src/DBManager.cpp
    src/Server.cpp
    src/generate.cpp
)

add_executable(Corba_Client
        client.cpp
        qml.qrc
        ${OMNIDLFILES}
        ${CLIENT_HEADERS}
        ${CLIENT_SOURCES}
)

target_link_libraries(Corba_Client
  PRIVATE Qt5::Core Qt5::Quick Qt5::Sql clientSide pthread omniORB4 omnithread
)


add_executable(Corba_Server
    server.cpp
    ${OMNIDLFILES}
    ${SERVER_HEADERS}
    ${SERVER_SOURCES}
)

target_link_libraries(Corba_Server
    PRIVATE Qt5::Core Qt5::Sql serverSide pthread omniORB4 omnithread)
