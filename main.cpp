#include <iostream>

#include "InputHandler.h"
#include "TaskScanner.h"

int main() {

    InputHandler inputHandler;

    //Путь к файлу с задачами
    const std::string defaultPath = "./tasklist.csv";

    inputHandler.setTaskContainer( TaskScanner::scanTasks(defaultPath) );

    inputHandler.startInputScan();

    TaskScanner::writeTasksToFile( inputHandler.getTaskContainer(), defaultPath );
}
