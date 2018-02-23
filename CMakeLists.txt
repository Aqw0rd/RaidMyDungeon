set(PROJECT_NAME RaidMyDungeon)

cmake_minimum_required(VERSION 3.9)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp Config.cpp Config.h State.cpp State.h States/IntroState.cpp States/IntroState.h App.cpp App.h StateMachine.cpp StateMachine.h States/MainMenuState.cpp States/MainMenuState.h Map.cpp Map.h MapLayer.cpp MapLayer.h States/PlayState.cpp States/PlayState.h GameObject.cpp GameObject.h Objects/Player.cpp Objects/Player.h Ability.cpp Ability.h Abilities/Melee.cpp Abilities/Melee.h Abilities/Melee/NormalAttack.cpp Abilities/Melee/NormalAttack.h Items/Weapon.cpp Items/Weapon.h Items/Weapons/IronSword.cpp Items/Weapons/IronSword.h)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} jsoncpp sfml-graphics sfml-window sfml-system sfml-audio)