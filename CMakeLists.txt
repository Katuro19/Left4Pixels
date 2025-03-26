cmake_minimum_required(VERSION 3.18)
project(l4px LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


#Add directories here :
include_directories(
    .
    ./Window
    ./Scene
)


# Create a source list, where you add every files you want to use
set(SOURCES
    main.cpp

    ./Window/MainWindow.h
    ./Window/MainWindow.cpp
    
    ./Scene/Scene.h
    ./Scene/Scene.cpp

)



add_executable(
l4px
${SOURCES}
)

target_link_libraries(l4px PRIVATE Qt6::Widgets)