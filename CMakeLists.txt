cmake_minimum_required (VERSION 3.13)

project ("TheFoolEngine" VERSION 0.1 LANGUAGES CXX)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

#add_executable (TheFoolEngine "src/TheFoolEngine.cpp"  "include/Card.h" "include/CardSet.h" "src/Card.cpp" "include/Deck.h" "src/Deck.cpp"  "include/Player.h" "src/Player.cpp" "include/Table.h" "src/Table.cpp")
add_executable (TheFoolEngine "TheFoolEngine.cpp")

set_property(TARGET TheFoolEngine PROPERTY CXX_STANDARD 20)

add_subdirectory(include)
add_subdirectory(src)



