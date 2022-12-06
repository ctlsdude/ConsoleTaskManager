
#ifndef CONSOLETASKMANAGER_COMMAND_H
#define CONSOLETASKMANAGER_COMMAND_H

#include "string"

#include "TaskContainer.h"
#include "Validator.h"

//Абстрактный класс, в наследниках которого в методе execute реализована логика выполнения опредленной комманды
class Command {

public:

    virtual ~Command() = default;

    virtual void execute(std::string parameters, TaskContainer& tasks) = 0;
    virtual void setParameters(std::string parameters);

    void setValidator(Validator);

protected:

    std::string name;
    std::string parameters;
    Validator validator;
};

class AddCommand : public Command   {

public:
    void execute(std::string parameters, TaskContainer& tasks) override;
};

class DoneCommand : public Command   {

public:
    void execute(std::string parameters, TaskContainer& tasks) override;
};

class UpdateCommand : public Command   {

public:
    void execute(std::string parameters, TaskContainer& tasks) override;

};

class DeleteCommand : public Command    {

public:
    void execute(std::string parameters, TaskContainer& tasks) override;
};

class SelectCommand : public Command    {

public:
    void execute(std::string parameters, TaskContainer& tasks) override;
};

#endif //CONSOLETASKMANAGER_COMMAND_H
