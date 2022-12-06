

#ifndef CONSOLETASKMANAGER_TASKSCANNER_H
#define CONSOLETASKMANAGER_TASKSCANNER_H

#include "TaskContainer.h"
#include "rapidcsv.h"

//Класс для считывания и записи задач
class TaskScanner {

public:

    static TaskContainer scanTasks(std::string pathToFile);

    static bool writeTasksToFile(TaskContainer tasks, std::string pathToFile);

};

#endif //CONSOLETASKMANAGER_TASKSCANNER_H
