cmake_minimum_required (VERSION 3.12)

project ("TheFoolEngine")
#set(CMAKE_CXX_FLAGS "/EHsc /W4 /D_DEBUG /MDd")
add_executable (TheFoolEngine "TheFoolEngine.cpp"  "Card.h" "CardSet.h" "Card.cpp" "Deck.h" "Deck.cpp"  "Player.h" "Player.cpp" "Table.h" "Table.cpp")

set_property(TARGET TheFoolEngine PROPERTY CXX_STANDARD 20)
