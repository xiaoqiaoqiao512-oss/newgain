#ifndef UI_H
#define UI_H

#include<iostream>
#include<filesystem>
#include"user.h"
#include"news.h"
#include"database.h"
#include <vector>

class ui{
    private:
        Database& db;
        std::vector<News> newsList;
        User* user;

    public:
        ui(const std::vector<News>& news, Database& database);
        void setUser(User* usr);
        void showMenu();
        void handselfchoice(int choice);
        void setUserInfo();
        void viewUserInfo();
        void ViewSelfRconmendedNews();
        void addInterestingThings();
        User* userSignIn();
        void findOtherUsers();
        void updateUserInfo();
        void searchnews();
        void saveFavorite();

        //destructor to clean up user pointer
        ~ui() {
            if(user) {
                delete user;
                user = nullptr;
            }
        }
};

#endif