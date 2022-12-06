
#include <iostream>
#include <iomanip>
#include <memory>

#include "InputHandler.h"
#include "TaskLE.h"
#include "Command.h"
#include "Task.h"

//----class Command methods----//
void Command::setParameters(std::string newParameters) {

    parameters = std::move(newParameters);
}

void Command::setValidator(Validator newValidator) {

    validator = std::move(newValidator);
}

//----Command heirs methods----//
void AddCommand::execute(std::string parameters, TaskContainer &tasks) {

    if( !this->validator.validateString(parameters) )   {

        std::cout << "unacceptable parameters!\n";
    }
    else    {

        //Лямбда возвращающая текст в первых найденных кавычках ""
        auto getTextFromNextMarks = []( std::string& checkedString ) -> std::string {

            try {

                std::string tempStr = checkedString.substr( checkedString.find_first_of( "\"") + 1);
                std::string result = tempStr.substr(0, tempStr.find_first_of( "\"") );
                return result;
            }
            catch (const std::out_of_range& e) {

                return "";
            }
        };

        //Последовательно ввырезаем из строки с параметрами имя, описание, дату созданияя и категорию
        std::string name = getTextFromNextMarks( parameters );

        if( tasks.checkTaskAvailability(name) ) { std::cout << "Task with this name is already exist!\n"; }
        else    {

            //Description
            const int markAndSlash = 3;
            parameters = parameters.substr( name.length() + markAndSlash);
            std::string description = getTextFromNextMarks(parameters);

            //Date
            parameters = parameters.substr( description.length() + markAndSlash);
            std::string timeParameter = getTextFromNextMarks(parameters);
            struct std::tm createTime;
            std::istringstream ss(timeParameter);
            ss >> std::get_time(&createTime, "%Y-%m-%d %H:%M");

            //Category
            parameters = parameters.substr( timeParameter.length() + markAndSlash);
            std::string category = getTextFromNextMarks(parameters);

            tasks.addTask( Task(name, createTime, description, category, UNDONE) );
            std::cout << "new task added!\n";
        }
    }
}

void DoneCommand::execute(std::string parameters, TaskContainer &tasks) {

    if( !this->validator.validateString(parameters) )   {

        std::cout << "unacceptable parameters!\n";
    }
    else    {

            std::string taskName = parameters;
            if( tasks.checkTaskAvailability(taskName) ) {

                tasks.markTaskDone(taskName);
                std::cout << "task " << taskName << " now is done\n";
            }
            else    {

                std::cout << "no task with name: " << taskName;
            }
    }
}

void UpdateCommand::execute(std::string parameters, TaskContainer &tasks) {

    if( !this->validator.validateString(parameters) )   {

        std::cout << "unacceptable parameters!\n";
    }
    else    {

        const std::string& taskName = parameters;
        if( tasks.checkTaskAvailability(taskName) ) {
            //!!!!!
            std::string datePattern = "\\s{0,}[0-9]{4}-(1[0-2]|0[1-9])-(3[0-1]|[0-2][0-9]) (2[0-3]|[0-1][0-9]){1}:[0-5][0-9]\\s{0,}";
            Validator parameterValidator(datePattern);

            std::cout << "Enter new create date: ";
            std::string dateString = InputHandler::scanUntilValidate( parameterValidator );
            struct std::tm createTime;
            std::istringstream ss(dateString);
            ss >> std::get_time(&createTime, "%Y-%m-%d %H:%M");


            std::string descriptionPattern = "\\s{0,}[\\w\\d ]{0,}\\s{0,}";
            parameterValidator.setNewRegExp(descriptionPattern);
            std::cout << "Enter new description: ";
            std::string description = InputHandler::scanUntilValidate( parameterValidator );

            std::string categoryPattern = "[\\w\\d]{0,}";
            parameterValidator.setNewRegExp(categoryPattern);
            std::cout << "Enter new category: ";
            std::string category = InputHandler::scanUntilValidate( parameterValidator );

            Task newTask(taskName, createTime, description, category, UNDONE);
            tasks.removeTask(taskName);
            tasks.addTask( newTask );

            std::cout << taskName << " updated\n";
        }
        else    {

            std::cout << "no task with name: " << taskName;
        }//else
    }//else
}//execute

void DeleteCommand::execute(std::string parameters, TaskContainer &tasks) {

    if( !this->validator.validateString(parameters) )   {

        std::cout << "unacceptable parameters!\n";
    }
    else    {

        std::string taskName = parameters;
        if( tasks.checkTaskAvailability(taskName) ) {

            tasks.removeTask(taskName);
            std::cout << "task " << taskName << " now deleted\n";
        }
        else    {

            std::cout << "no task with name: " << taskName;
        }//else
    }//else
}//execute

void SelectCommand::execute(std::string parameters, TaskContainer &tasks) {

    //Проверяем соответсвие строки с параметрами паттерну
    if( !this->validator.validateString(parameters) )   {

        std::cout << "unacceptable parameters!\n";
        return;
    }

    //Если не нашли where, то показываем все задачи
    if (parameters.find("where") == std::string::npos)  {

        std::cout << "Selected tasks:\n";

        const std::unordered_map<std::string, Task> &tasksMap = tasks.getRefToTasks();
        for (const auto &it : tasksMap) {

            std::cout << it.second.getAllAboutTask() << "\n";
        }
    }
    else{

        //Лямбда возвращающая текст в первых найденных кавычках ""
        auto getTextFromFirstMarks = []( std::string& checkedString ) -> std::string {

            try {

                std::string tempStr = checkedString.substr( checkedString.find_first_of( "\"") + 1);
                std::string result = tempStr.substr(0, tempStr.find_first_of( "\"") );
                return result;
            }
            catch (const std::out_of_range& e) {

                return "";
            }
        };

        std::vector<std::shared_ptr<DateLJ>>     dateConditions = {};
        std::vector<std::shared_ptr<StringLJ>>   statusConditions = {};
        std::vector<std::shared_ptr<StringLJ>>   categoryConditions = {};
        std::vector<std::shared_ptr<StringLJ>>   descriptionConditions = {};

        //Вырезаем из в строки с параметрами комманды все, что после where
        std::string logicalConditions = parameters.substr( parameters.find("where") + std::string("where").length() );

        //Условие для даты создания задачи
        auto datePos = logicalConditions.find("date");
        if( datePos != std::string::npos )   {

            std::string dateConditionString = logicalConditions.substr( logicalConditions.find("date") + std::string("date").length()) ;

            struct std::tm createTime{};
            std::string conditionText =  getTextFromFirstMarks(dateConditionString);
            std::istringstream ss( conditionText );
            ss >> std::get_time(&createTime, "%Y-%m-%d %H:%M");

            std::string operatorString = dateConditionString.substr(0, dateConditionString.find_first_of("\"") );
            operatorString.erase( remove( operatorString.begin(), operatorString.end(), ' ' ), operatorString.end() );

            std::tm zeroTime = {};//!!!
            dateConditions.push_back( std::make_shared<DateLJ>( zeroTime, createTime, operatorString ) );//!!!
        }

        //Условие для категории задачи
        auto categoryPos = logicalConditions.find("category");
        if( categoryPos != std::string::npos )   {

            std::string categoryConditionString = logicalConditions.substr( logicalConditions.find("category") + std::string("category").length()) ;

            std::string conditionText =  getTextFromFirstMarks(categoryConditionString);

            std::string operatorString = categoryConditionString.substr(0, categoryConditionString.find("\"") );

            categoryConditions.push_back( std::make_shared<StringLJ>("", conditionText) );
        }

        //Условие для описания задачи
        auto descPos = logicalConditions.find("description");
        if( descPos != std::string::npos )   {

            std::string descConditionString = logicalConditions.substr( logicalConditions.find("description") + std::string("description").length()) ;

            std::string conditionText =  getTextFromFirstMarks(descConditionString);

            std::string operatorString = descConditionString.substr(0, descConditionString.find("\"") );
            operatorString.erase( remove( operatorString.begin(), operatorString.end(), ' ' ), operatorString.end() );

            if(operatorString == "like") descriptionConditions.push_back( std::make_shared<SubstringInStringLJ>( "", conditionText ) );
            else descriptionConditions.push_back( std::make_shared<StringLJ>("", conditionText) );
        }


        //Условие для статуса задачи
        auto statusPos = logicalConditions.find("status");
        if( statusPos != std::string::npos )   {

            std::string statusConditionString = logicalConditions.substr( logicalConditions.find("status") + std::string("status").length()) ;

            std::string conditionText =  getTextFromFirstMarks(statusConditionString);

            statusConditions.push_back( std::make_shared<StringLJ>("", conditionText) );
        }

        TaskLE logicalExpression(dateConditions, statusConditions, categoryConditions, descriptionConditions);

        std::vector<Task> satisfyingTasks = tasks.getTasks(logicalExpression);

        std::cout << "Selected tasks:\n";
        for (const auto &it : satisfyingTasks) {

            std::cout << it.getAllAboutTask() << "\n";
        }
    }
}


