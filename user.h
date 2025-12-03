#ifndef USER_H
#define USER_H

#include<iostream>
#include<string>
#include<vector>

class User {
    private:
        std::string name;
        int age;
        std::string sexyty;
        std::vector<std::string> interestingThing;
    public:
        User(const std::string& username, const int& userage, const std::string& usersexyty);
        User();

        //basic personality
        void addAge(const int& userage);
        int getAge() const;
        void setName(const std::string& username);
        std::string getName() const;
        void addSexyty(const std::string& usersexyty);
        std::string getSexyty() const;

        //interesting personality
        void addInterestingThing(const std::string& userinterestingThing);
        void removeInterestingThing(const std::string& userinterestingThing);
        std::vector<std::string> getInterestingThing() const;

        //print info
        void printInfo() const;
};

#endif