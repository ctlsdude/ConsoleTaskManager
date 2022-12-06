#ifndef CONSOLETASKMANAGER_COMMANDBUILDER_H
#define CONSOLETASKMANAGER_COMMANDBUILDER_H

#include "Command.h"

//Класс отвечающий за создание объектов - наследников класса Command
class CommandBuilder {

public:

    static std::unique_ptr<Command> makeCommand(const std::string& commandName);
};


#endif //CONSOLETASKMANAGER_COMMANDBUILDER_H
