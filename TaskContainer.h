
#ifndef CONSOLETASKMANAGER_TASKCONTAINER_H
#define CONSOLETASKMANAGER_TASKCONTAINER_H

#include "vector"
#include "unordered_map"
#include "map"

#include "Task.h"
#include "TaskLE.h"

//Класс - для хранения объектов - задач
class TaskContainer {

public:

    TaskContainer();
    TaskContainer(std::unordered_map <std::string, Task> taskContainer);

    //Вернуть вектор с задачами, поля которых делают логическое выражению истинным
    std::vector<Task> getTasks(TaskLE);

    void addTask(Task);
    void removeTask(std::string);

    bool checkTaskAvailability(std::string);

    void markTaskDone(const std::string&);

    //vector<Task> findSatisfyingTasks( ConditionContainer );

    const std::unordered_map<std::string,Task>& getRefToTasks();

    void changeTask();

private:

    std::unordered_map<std::string,Task> taskContainer;
};

#endif //CONSOLETASKMANAGER_TASKCONTAINER_H
