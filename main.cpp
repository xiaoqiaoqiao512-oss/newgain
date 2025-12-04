#include"news.h"
#include"ui.h"
#include"user.h"
#include"database.h"
#include"fetcher.h"

#include<iostream>
#include<vector>
#include<windows.h>

int main(){

    //enable utf-8 console output
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout<<"initializing news management system..."<<std::endl;
    
    FETCHER fetcher;
    std::string newsJson = fetcher.NewsFetcher();
    if (fetcher.getLastStatusCode() != 0) {
        std::cerr << "Failed to fetch news: " << fetcher.getLastErrorMessage() << std::endl;
        return 1;
    }

    std::vector<News> newslist = News::parseNewsJson(newsJson);
    //load user database from file
    Database db;
    db.saveNewsToFile("news_data.json", newslist);
    if(!db.loadFromFile("user_database.txt")){
        std::cout<<"No existing database found. Starting with an empty database."<<std::endl;
    }

    std::vector<News> loadedNews = db.loadNewsFromFile("news_data.json");
    ui Ui(loadedNews, db);
    User* signedInUser = Ui.userSignIn();

    if (!signedInUser) {
        std::cout << "Failed to sign in. Exiting...\n";
        return 0;
    }

    Ui.setUser(signedInUser);
    Ui.showMenu();
    db.saveToFile("user_database.txt");
    //save user database to file before exit
    //file name is user_database.txt
    return 0;
}