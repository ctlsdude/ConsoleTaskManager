#ifndef CONSOLETASKMANAGER_LOGICALJUDMENT_H
#define CONSOLETASKMANAGER_LOGICALJUDMENT_H

#include <string>
#include <ctime>
#include <utility>

//Логическое суждние
class LogicalJudment {

public:

    virtual bool compute() { return true; };
};

//Логическое суждение, является ли одна строка равной другой
class StringLJ: public LogicalJudment {

public:

    StringLJ(std::string operand1, std::string operand2): mainString(std::move(operand1)), subString(std::move(operand2)) {}
    explicit StringLJ(std::string operand1): mainString(std::move(operand1)) {}

    void setMainString(std::string str) { mainString = str;  };
    void setSubstring(std::string str) { subString = str; };

    virtual bool compute() override   {

        return mainString == subString;
    }

protected:

    std::string mainString = "";
    std::string subString  = "";

};

//Логическое суждение, является ли одна строка под строкой другой
class SubstringInStringLJ: public StringLJ    {

public:

    SubstringInStringLJ(std::string operand1, std::string operand2): StringLJ( std::move(operand1), std::move(operand2) ) {}

     bool compute() final    {

         return mainString.find(subString) != std::string::npos;
     }
};

//Логическое суждение, сравнение двух дат
class DateLJ: LogicalJudment    {

public:

    DateLJ() {};
    DateLJ(std::tm mainOperand, std::tm subOperand, std::string operatorSymbols)
    :   operand1(std::mktime( &mainOperand ) ),
        operand2(std::mktime( &subOperand ) ),
        logicOperator( std::move(operatorSymbols) ){}

    void setOperand1(std::tm date) {

        operand1 = std::mktime(&date);
    }

    void setOperand2(std::tm date) {

        operand2 = std::mktime(&date);
    }

    bool compute() override {

        if(logicOperator.find('=') != std::string::npos) {

            if( std::difftime(operand1, operand2) == 0 ) return true;
        }
        if(logicOperator.find('<') != std::string::npos)  {

            if( std::difftime(operand1, operand2) < 0 ) return true;
        }
        if(logicOperator.find('>') != std::string::npos)    {

            if( std::difftime(operand1, operand2) > 0 ) return true;
        }
        return false;
    }

private:

    std::string logicOperator = "==";
    time_t operand1{};//Время записанное в задаче
    time_t operand2{};//Время из фильтра

};



#endif //CONSOLETASKMANAGER_LOGICALJUDMENT_H
