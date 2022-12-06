#include "TaskLE.h"

#include <utility>


//Получить результат составного логического выражение о полях задачи.
//Пока между простыми логическими суждениями возможено только И
bool TaskLE::compute() {

    bool result = true;
    for( int i = 0; i < dateLJ_Container.size(); i++) result = result * dateLJ_Container[i]->compute();
    for( int i = 0; i < statusLJ_Container.size(); i++) result = result * statusLJ_Container[i]->compute();
    for( int i = 0; i < categoryLJ_Container.size(); i++) result = result * categoryLJ_Container[i]->compute();
    for( int i = 0; i < descriptionLJ_Container.size(); i++) result = result * descriptionLJ_Container[i]->compute();

    if( dateLJ_Container.empty() &&
        statusLJ_Container.empty() &&
        categoryLJ_Container.empty() &&
        descriptionLJ_Container.empty() ) {  result = false; }

    return result;
}

void TaskLE::setFirstOperands(  std::tm     date,
                                TaskStatus  status,
                                std::string category,
                                std::string description)    {

    setFirstOperandForDate(date);
    setFirstOperandForStatus(status);
    setFirstOperandsForDescription( std::move(description) );
    setFirstOperandForCategory( std::move(category) );
}

void TaskLE::setFirstOperandForDate(std::tm operand)    {

    for(auto i = 0; i < dateLJ_Container.size(); i++) {

        dateLJ_Container[i]->setOperand1(operand);
    }
}

void TaskLE::setFirstOperandForStatus(TaskStatus status)   {

    for(auto i = 0; i < statusLJ_Container.size(); i++) {

        if( status == DONE) statusLJ_Container[i]->setMainString("on");
        else  statusLJ_Container[i]->setMainString("off");
    }
}

void TaskLE::setFirstOperandForCategory(std::string mainString) {

    for(auto i = 0; i < categoryLJ_Container.size(); i++) {

        categoryLJ_Container[i]->setMainString(mainString);
    }
}

void TaskLE::setFirstOperandsForDescription(std::string mainString) {

    for(auto i = 0; i < descriptionLJ_Container.size(); i++) {

        descriptionLJ_Container[i]->setMainString(mainString);
    }
}
