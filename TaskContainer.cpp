//
// Created by Roman on 25.11.2022.
//

#include "TaskContainer.h"

#include <utility>
TaskContainer::TaskContainer() {

    taskContainer = {};
}

TaskContainer::TaskContainer(std::unordered_map<std::string, Task> taskContainer) : taskContainer(std::move(taskContainer)) {

}

void TaskContainer::addTask(Task task) {

   taskContainer.try_emplace( task.getName(), std::move(task) );
}

void TaskContainer::removeTask(std::string taskName) {

    taskContainer.erase( taskName );
}

bool TaskContainer::checkTaskAvailability(std::string taskName) {

    bool isAvailable = taskContainer.count(taskName);
    return isAvailable;
}

void TaskContainer::changeTask() {

}

void TaskContainer::markTaskDone(const std::string& taskName)   {

    taskContainer[taskName].setStatus(DONE);
}

const std::unordered_map<std::string, Task> &TaskContainer::getRefToTasks() {

    return taskContainer;
}

std::vector<Task> TaskContainer::getTasks(TaskLE logicalExpression) {

    std::vector<Task> tasksSatisfyingConditions = {};

    //Проходим по всем имеющимся задачам
    for(auto & it : taskContainer)   {

        logicalExpression.setFirstOperands( it.second.getCreateDate(),
                                            it.second.getStatus(),
                                            it.second.getCategory(),
                                            it.second.getDescription() );


        if( logicalExpression.compute() ) {

            tasksSatisfyingConditions.push_back( it.second );
        }
    }
    return tasksSatisfyingConditions;
}


