#include "user.h"
#include <algorithm>


//默认构造函数
User::User() : name("guest"), age(0), sexyty("unknown") {
    std::cout << "you don't set your name ,age and sexyty" << std::endl;
}

//带用户名构造函数
User::User(const std::string& username, const int& userage, const std::string& usersexyty) : name(username), age(userage), sexyty(usersexyty) {
    std::cout << "Welcome, " << username << "!" << std::endl;
}

//set your name
void User::setName(const std::string& username){
    name = username;
    std::cout << "your name " << name << " is set successfully!" << std::endl;
}

//get your name
std::string User::getName() const{
    return name;
}

//set your age (single value)
void User::addAge(const int& userage){
    age = userage;
    std::cout << "your age " << userage << " is set successfully!" << std::endl;
}

//get your age
int User::getAge() const{
    return age;
}

//set your sexyty
void User::addSexyty(const std::string& usersexyty){
    sexyty = usersexyty;
    std::cout << "your sexyty " << usersexyty << " is set successfully!" << std::endl;
}

//get your sexyty
std::string User::getSexyty() const{
    return sexyty;
}

//add your interesting thing
void User::addInterestingThing(const std::string& userinterestingThing){
    interestingThing.push_back(userinterestingThing);
    std::cout << "your interesting thing " << userinterestingThing << " is added successfully!" << std::endl;
}

//remove your interesting thing
void User::removeInterestingThing(const std::string& userinterestingThing){
    auto it = std::find(interestingThing.begin(), interestingThing.end(), userinterestingThing);
    if(it != interestingThing.end()){
        interestingThing.erase(it);
        std::cout << "your interesting thing " << userinterestingThing << " is removed successfully!" << std::endl;
    } else {
        std::cout << "your interesting thing " << userinterestingThing << " not found!" << std::endl << "please putin correct interesting thing" << std::endl;
    }
}

//get your interesting thing
std::vector<std::string> User::getInterestingThing() const{
    return interestingThing;
}

//print user info
void User::printInfo() const{
    std::cout << "User Info:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Sexyty: " << sexyty << std::endl;
    std::cout << "Interesting Things: ";
    for(const auto& it : interestingThing){
        std::cout << it << " ";
    }
    std::cout << std::endl;
}
