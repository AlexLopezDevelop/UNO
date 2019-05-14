cmake_minimum_required(VERSION 3.14)
project(UNO C)

set(CMAKE_C_STANDARD 99)

add_executable(UNO main.c cli.c cli.h plist.c plist.h bot.h card.h file.c node.h player.h stack.h file.h stats.c stats.h game.c game.h)