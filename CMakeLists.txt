set(PROJECT_NAME RaidMyDungeon)

cmake_minimum_required(VERSION 3.9)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp Config.cpp Config.h State.cpp State.h States/IntroState.cpp States/IntroState.h App.cpp App.h StateMachine.cpp StateMachine.h States/MainMenuState.cpp States/MainMenuState.h Map.cpp Map.h MapLayer.cpp MapLayer.h States/PlayState.cpp States/PlayState.h GameObject.cpp GameObject.h)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} jsoncpp sfml-graphics sfml-window sfml-system sfml-audio)