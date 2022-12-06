cmake_minimum_required(VERSION 3.16)
project(ConsoleTaskManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConsoleTaskManager main.cpp Task.cpp Task.h TaskContainer.cpp TaskContainer.h InputHandler.cpp InputHandler.h Command.cpp Command.h Validator.cpp Validator.h TaskScanner.cpp TaskScanner.h CommandBuilder.cpp CommandBuilder.h LogicalJudment.h TaskLE.cpp TaskLE.h)