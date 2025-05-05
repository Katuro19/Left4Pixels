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
    ./Entity
    ./Player
    ./Weapon
    ./Projectiles
    ./MapLoader
    ./Menus
)


# Create a source list, where you add every files you want to use
set(SOURCES
    main.cpp

    ./Window/MainWindow.cpp
    ./Window/MainWindow.h

    
    ./Scene/Scene.cpp
    ./Scene/Scene.h


    ./Entity/Entity.h
    ./Entity/Entity.cpp

    ./Player/Player.cpp
    ./Player/Player.h

    ./Weapon/Weapon.cpp
    ./Weapon/Weapon.h

    ./Projectiles/Projectiles.cpp
    ./Projectiles/Projectiles.h

    ./MapLoader/MapLoader.cpp
    ./MapLoader/MapLoader.h

    ./Menus/MenuButton.cpp
    ./Menus/MenuButton.h
    ./Menus/Menus.cpp
    ./Menus/Menus.h

)



add_executable(
l4px
${SOURCES}
)

target_link_libraries(l4px PRIVATE Qt6::Widgets)