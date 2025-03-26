#include "checkers.h"
#include <regex>

std::string NameIsValid(const std::string& name) {
    for (char ch : name) {
        if (!std::isalpha(ch) && ch != ' ' && ch != '-') {
            return "It Should Conatain Only letters,space Or -";
        }
    }
    return "Valid";
}

std::string EmailIsValid(const std::string& email) {

    std::regex emailRegex("^[A-Za-z0-9_.+-]+@[A-Za-z]+\\.[A-Za-z-.]+$");


    if (std::regex_match(email, emailRegex)) {

        size_t atPos = email.find('@');
        size_t dotPos = email.find('.', atPos);


        if (atPos == 0 || atPos == email.length() - 1 || dotPos == email.length() - 1) {
            return "Invalid Email Format";
        }


        std::string domain = email.substr(atPos + 1);
        for (char ch : domain) {
            if (ch == ' ' || (!isalnum(ch) && ch != '-' && ch != '.')) {
                return "Invalid Email Format";
            }
        }

        return "Valid";
    }

    return "Invalid Email Format";
}
std::string UserNameIsValid(const std::string username){

}
std::string PasswordIsValid(const std::string password){

}


Checkers::Checkers() {}
