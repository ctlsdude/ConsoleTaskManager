
#include "iomanip"

#include "Task.h"

//-------Setters
void Task::setCategory(std::string newCat) {

    category = std::move(newCat);
}

void Task::setCreateDate(std::tm newCreateDate) {

    createDate = newCreateDate;
}

void Task::setDesription(std::string newDesc) {

    description = std::move(newDesc);
}

void Task::setStatus(TaskStatus newStatus) {

    status = newStatus;
}

//------Getters
std::string Task::getName() const {

    return name;
}

std::tm Task::getCreateDate() const {

    return createDate;
}

std::string Task::getDescription() const {

    return description;
}

std::string Task::getCategory() const {

    return category;
}

TaskStatus Task::getStatus() const {

    return status;
}

std::string Task::getAllAboutTask() const {

    std::stringstream time;
    time <<  std::put_time(&createDate, "%Y-%m-%d %H:%M");

    std::string statusString;
    if(status == UNDONE) statusString = "ON";
    else statusString = "OFF";

    std::string result =    name + ","
                            + description + ","
                            + time.str() + ","
                            + category + ","
                            + statusString;

    return result;
}

