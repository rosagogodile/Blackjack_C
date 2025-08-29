cmake_minimum_required(VERSION 3.28)
project(Game)

add_library(Cards cards.c cards.h)
add_library(LinkedList linked_list.c linked_list.h)
add_library(Player player.c player.h)

add_executable(Game game.c)

target_link_libraries(Game Cards LinkedList Player)