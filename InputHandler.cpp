
#include <iostream>
#include <string>
#include <utility>

#include "InputHandler.h"
#include "Command.h"
#include "CommandBuilder.h"

//Считываем строки в бесконечном цикле
//Если пользователь ввел q или quit - выходим, иначе - воспринимаем строку как команду с параметрами и пытаемся обработать
void InputHandler::startInputScan() {

    std::string input;
    bool exitFlag = false;

    while(!exitFlag) {

        std::getline(std::cin, input);

        if(input == "quit" || input == "q") {

            exitFlag = true;
        }
        else  proccessInput(input);
    }
}

void InputHandler::proccessInput(std::string input) {

    //Получаем имя команды
    std::string commandName = getFirstWord(input);

    //Создаем объект команды, объект класса соответсвующего имени команды
    //Command* command = CommandBuilder::makeCommand(commandName);
    std::unique_ptr<Command> command = CommandBuilder::makeCommand(commandName);

    //Получаем параметры из остатка строки и пытаемся выполнить команду, если объект комманды был создан
    if(command == nullptr) { std::cout << "unknown command!\n"; }
    else {

        std::size_t parametersPos = input.find_first_of(commandName);
        std::string parameters = input.substr(parametersPos + commandName.length());
        std::size_t  noSpaceSymbolPos = parameters.find_first_not_of(" ");
        if( noSpaceSymbolPos != std::string::npos ) {

            parameters = parameters.substr(noSpaceSymbolPos);
        }

        command->execute(parameters, tasks);
    }
}

std::string InputHandler::getFirstWord(std::string str) {

    std::size_t  noSpaceSymbolPos = str.find_first_not_of(' ');
    if(noSpaceSymbolPos == std::string::npos)    {
        //!!!
        return "no command";
    }
    str = str.substr(noSpaceSymbolPos);

    size_t  spacePos = str.find_first_of(' ');
    if( spacePos == std::string::npos )   {
        //!!!
        return "no params";
    }
    return str.substr(0, spacePos);
}

void InputHandler::setTaskContainer(TaskContainer container) {

    tasks = std::move(container);
}

std::string InputHandler::scanUntilValidate(Validator& validator) {

    std::string result;
    std::string input;

    bool exitFlag = false;
    while( !exitFlag )  {

        std::getline(std::cin, input);

        if(input == "quit" || input == "q") {

            exitFlag = true;
            result = "";
        }

        if( validator.validateString(input) ) {

            result = input;
            exitFlag = true;

        }
        else {

            std::cout << "invalid parameter value\n";
        }
    }

    return result;
}

const TaskContainer &InputHandler::getTaskContainer() {

    return tasks;
}

