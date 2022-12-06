#include "LogicalJudment.h"
#include "Task.h"

#include <memory>
#include <vector>


#ifndef CONSOLETASKMANAGER_TASKLE_H
#define CONSOLETASKMANAGER_TASKLE_H

//Класс - логическое выражение, которое можно применить к задаче для её полей
class TaskLE {

public:

    TaskLE( std::vector<std::shared_ptr<DateLJ>>     dateJudments,
            std::vector<std::shared_ptr<StringLJ>>   statusJudments,
            std::vector<std::shared_ptr<StringLJ>>   categoryJudments,
            std::vector<std::shared_ptr<StringLJ>>   descriptionJudments)
            :   dateLJ_Container( std::move(dateJudments) ),
                statusLJ_Container( std::move(statusJudments) ),
                categoryLJ_Container( std::move(categoryJudments) ),
                descriptionLJ_Container( std::move(descriptionJudments) ) {}

    void setFirstOperands(std::tm, TaskStatus, std::string , std::string);
    void setFirstOperandForDate(std::tm operand);
    void setFirstOperandForStatus(TaskStatus mainString);
    void setFirstOperandForCategory(std::string mainString);
    void setFirstOperandsForDescription(std::string mainString);

    bool compute();

private:

    std::vector<std::shared_ptr<DateLJ>>     dateLJ_Container          =   {};
    std::vector<std::shared_ptr<StringLJ>>   statusLJ_Container        =   {};
    std::vector<std::shared_ptr<StringLJ>>   categoryLJ_Container      =   {};
    std::vector<std::shared_ptr<StringLJ>>   descriptionLJ_Container   =   {};
};


#endif //CONSOLETASKMANAGER_TASKLE_H
