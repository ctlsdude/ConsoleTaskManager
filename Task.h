
#ifndef CONSOLETASKMANAGER_TASK_H
#define CONSOLETASKMANAGER_TASK_H

#include <string>
#include <ctime>
#include <utility>

enum TaskStatus {UNDONE = 0, DONE = 1};

class Task {

public:

    Task() {};
    Task(   std::string argName,
            std::tm argDate,
            std::string argDesc,
            std::string argCat,
            TaskStatus argSt = UNDONE)
            :   name(std::move(argName)),
                createDate(argDate),
                description(std::move(argDesc)),
                category(std::move(argCat)),
                status(argSt) {}

    //-----getters----//
    std::string getName()           const;
    std::tm     getCreateDate()     const;
    std::string getDescription()    const;
    std::string getCategory()       const;
    TaskStatus  getStatus()         const;

    std::string getAllAboutTask()   const;

    //-----setters----//
    void setCreateDate(std::tm);
    void setDesription(std::string);
    void setCategory(std::string);
    void setStatus(TaskStatus);

private:

    std::string name        = "";
    std::tm     createDate  = {};
    std::string description = "";
    std::string category    = "";
    TaskStatus  status      = UNDONE;
};

#endif //CONSOLETASKMANAGER_TASK_H
