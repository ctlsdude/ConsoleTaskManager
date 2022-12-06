#include "CommandBuilder.h"

std::unique_ptr<Command> CommandBuilder::makeCommand(const std::string& commandName) {

    if(commandName == "add" ||  commandName == "Add")   {

        std::unique_ptr<Command> command = std::make_unique<AddCommand>();
        std::string namePattern = "\\\"[\\w\\d]{0,}\\\"";
        std::string datePattern = "\\\"[0-9]{4}-(1[0-2]|0[1-9])-(3[0-1]|[0-2][0-9]) (2[0-3]|[0-1][0-9]){1}:[0-5][0-9]\\\"";
        std::string descriptionPattern = "\\\"[\\w\\d ]{0,}\\\"";
        std::string categoryPattern = "\\\"[\\w\\d]{0,}\\\"";
        std::string parametersPattern = namePattern + "[ ]{1,}" + descriptionPattern + "[ ]{1,}" + datePattern + "[ ]{1,}" + categoryPattern;
        command->setValidator( Validator(parametersPattern) );

        return command;
    }

    if(commandName == "done" || commandName == "Done")  {

        std::unique_ptr<Command> command = std::make_unique<DoneCommand>();
        command->setValidator( Validator("[\\w\\d]{0,}\\s{0,}") );

        return command;
    }

    if(commandName == "update" || commandName == "Update")  {

        std::unique_ptr<Command> command = std::make_unique<UpdateCommand>();
        command->setValidator( Validator("[\\w\\d]{0,}\\s{0,}") );

        return command;
    }

    if(commandName == "delete" || commandName == "Delete")  {

        std::unique_ptr<Command> command = std::make_unique<DeleteCommand>();
        command->setValidator( Validator("[\\w\\d]{0,}\\s{0,}") );

        return command;
    }

    if(commandName == "select" || commandName == "Select")  {

        std::unique_ptr<Command> command = std::make_unique<SelectCommand>();
        std::string asteriskPattern = "\\s{0,}\\*\\s{0,}";
        std::string wherePattern = "\\s{0,}where\\s{1,}";
        std::string dateConditionPattern = "date[ ]{0,1}(<|>){0,1}={0,1}[ ]{0,1}\\\"[0-9]{4}-(1[0-2]|0[1-9])-(3[0-1]|[0-2][0-9]) (2[0-3]|[0-1][0-9]){1}:[0-5][0-9]\\\"";
        std::string categoryConditionPattern = "category=\\\"[\\w\\d]{0,}\\\"";
        std::string descriptionConditionPattern = "description(=| like )\\\"[\\w\\d ]{0,}\\\"";
        std::string statusConditionPattern = "status=\\\"(on|off)\\\"";
        std::string aggregatedConditionPattern = "(" + dateConditionPattern +
                                                "|" + categoryConditionPattern +
                                                "|" + descriptionConditionPattern +
                                                "|" + statusConditionPattern + ")";

        std::string selectParamettersPattern = asteriskPattern +
                + "(" + wherePattern + aggregatedConditionPattern + "{0,1}" + "(\\s{0,}and\\s{0,}" + aggregatedConditionPattern + "){0,}){0,1}";

        //command->setValidator( Validator("\\s{0,}\\*\\s{0,}") );
        command->setValidator( selectParamettersPattern );
        return command;
    }

    return nullptr;
}
