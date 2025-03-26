#ifndef CHECKERS_H
#define CHECKERS_H
#include <string>

class Checkers
{
public:
    Checkers();
    std::string NameIsValid(const std::string name);
    std::string EmailIsValid(const std::string email);
    std::string UserNameIsValid(const std::string username);
    std::string PasswordIsValid(const std::string password);
};

#endif // CHECKERS_H
