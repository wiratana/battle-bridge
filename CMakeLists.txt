cmake_minimum_required(VERSION 3.10)

project(BattleBridge    VERSION 0.1.0 
                        DESCRIPTION "Defend Your Motherland"
                        LANGUAGES C)

set(BIN_NAME battle_bridge)

file(GLOB SRC src/*c)

add_executable(BattleBridge ${SRC})
