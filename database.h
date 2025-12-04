#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <vector>
#include <map>
#include "user.h"
#include "news.h"
#include"json.hpp"

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

    //save news to file
    bool saveNewsToFile(const std::string& filename, const std::vector<News>& newsList);
    //load news from file
    std::vector<News> loadNewsFromFile(const std::string& filename);

    //search news by title
    bool searchNewsByName(const std::string& title, std::vector<News>& result);

    //the news which be loved by users
    void saveFavoriteNews(const std::vector<News>& news, const std::string& filename);
    std::vector<News> getFavoriteNews(const std::string name, const std::string& filename);
};

#endif