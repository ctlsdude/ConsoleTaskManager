
#ifndef CONSOLETASKMANAGER_VALIDATOR_H
#define CONSOLETASKMANAGER_VALIDATOR_H

#include "regex"


//Класс для реализации логики проверки строк
class Validator {

public:

    Validator();
    Validator(const std::string& str) : stringRegex(str) {};

    bool validateString(std::string);

    void setNewRegExp(std::string);

private:

    std::regex stringRegex;
};


#endif //CONSOLETASKMANAGER_VALIDATOR_H
