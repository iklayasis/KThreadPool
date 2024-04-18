cmake_minimum_required(VERSION 3.5)

project(KThreadPool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(KThreadPool main.cpp
    KThreadPool.h)

include(GNUInstallDirs)
install(TARGETS KThreadPool
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
