
#include "Validator.h"

Validator::Validator() {

}

bool Validator::validateString(std::string checkedString) {

    return std::regex_match(checkedString, stringRegex);
}

void Validator::setNewRegExp(std::string newRegExp) {

    stringRegex = std::move(newRegExp);
}

