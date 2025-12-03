#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <vector>
#include <map>
#include "user.h"

//using to manage user database
class Database {
    private:
    //using map which has username as key and user object as value
    std::map<std::string, User> users;

    public:
    bool addUser(const User& user);
    User* findUser(const std::string& username);
    bool removeUser(const std::string& username);
    
    //function about file save or load
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);

    //function to update user information
    bool updateUser(const User& user);

    //clear all users
    void clearAllUsers();
};

#endif