CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(test
    unit_tests/unit_tests.cpp
    src/Base.cpp
    src/RShell.cpp
    src/Command.cpp
    src/Parser.cpp
    src/Connector.cpp
    src/OrConnector.cpp
    src/AndConnector.cpp
    src/SemicolonConnector.cpp
    src/SingleInputRedirection.cpp
    src/SingleOutputRedirection.cpp
    src/DoubleOutputRedirection.cpp
    src/Pipe.cpp
)

ADD_EXECUTABLE(rshell
    src/main.cpp
    src/Base.cpp
    src/RShell.cpp
    src/Command.cpp
    src/Parser.cpp
    src/Connector.cpp
    src/OrConnector.cpp
    src/AndConnector.cpp
    src/SemicolonConnector.cpp
    src/SingleInputRedirection.cpp
    src/SingleOutputRedirection.cpp
    src/DoubleOutputRedirection.cpp
    src/Pipe.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
