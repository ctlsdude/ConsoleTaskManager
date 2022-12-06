#ifndef CONSOLETASKMANAGER_INPUTHANDLER_H
#define CONSOLETASKMANAGER_INPUTHANDLER_H

#include <string>
#include "TaskContainer.h"
#include "Validator.h"

//Класс овечающий за обработку ввода пользователя
class InputHandler {

public:

    InputHandler() {}

    void startInputScan();

    const TaskContainer& getTaskContainer();
    void setTaskContainer(TaskContainer);

    static std::string scanUntilValidate(Validator&);

private:

    std::string getFirstWord(std::string);
    void proccessInput(std::string);

    TaskContainer tasks;

};


#endif //CONSOLETASKMANAGER_INPUTHANDLER_H
