cmake_minimum_required(VERSION 3.22)
project(qt_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_PATH /usr/local/Cellar/libpq/15.2/include)
set(CMAKE_LIBRARY_PATH /usr/local/Cellar/libpq/15.2/lib)


find_package(Qt6 COMPONENTS
        Core
        Network
        Sql
        REQUIRED)

add_executable(qt_server src/main.cpp include/server.h src/server.cpp include/database.h src/database.cpp include/message.h src/message.cpp)
target_link_libraries(qt_server
        Qt6::Core
        Qt6::Network
        Qt6::Sql
        )

