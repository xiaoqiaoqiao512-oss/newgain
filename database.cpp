#include "database.h"
#include <map>
#include <string>
#include<fstream>

//construct database
bool Database::addUser(const User& user){
        if(users.count(user.getName())>0){
            std::cout<<"User already exists!"<<std::endl;
            return false;
        }
        else{
            // insert without default-constructing to avoid calling User::User()
            users.emplace(user.getName(), user);
            std::cout<<"User added successfully!"<<std::endl;
            return true;
        }
}

//using the map to find user by username
User* Database::findUser(const std::string& username){
        if(users.count(username)==0){
            std::cout<<"User not found!"<<std::endl;
            //return null pointer if user not found
            return nullptr;
        }
        else{
            return &users.at(username);
        }
}

//below is part about file
//remove user by username
bool Database::removeUser(const std::string& username){
        if(users.count(username)==0){
            std::cout<<"User not found!"<<std::endl;
            return false;
        }
        else{
            users.erase(username);
            std::cout<<"User removed successfully!"<<std::endl;
            return true;
        }
}

//save database to file
bool Database::saveToFile(const std::string& filename){
    std::ofstream outFile(filename);
    if(!outFile.is_open()){
        std::cout<<"can't open file"<<std::endl;
        return false;
    }
    for(const auto& p : users){
        outFile<<"Username:"<<p.second.getName()<<std::endl;
        outFile<<"Ages:"<<p.second.getAge()<<std::endl;
        outFile<<"Sexyty:"<<p.second.getSexyty()<<std::endl;
        outFile<<"Intersting Things:";
        for(auto& it : p.second.getInterestingThing()){
            outFile<<it<<",";
        }
        outFile<<std::endl;
    }
    //the format of file is like:
    //Username:John
    //Ages:25
    //Sexyty:m
    //Intersting Things:music,sports,
    //please ensure the format when load from file
    outFile.close();
    std::cout<<"Database saved to file successfully!"<<std::endl;
    return true;
}

//load database from file
bool Database::loadFromFile(const std::string&filename){
    std::ifstream inFile(filename);
    if(!inFile.is_open()){
        //about file name error
        std::cout<<"can't open file,check your filename"<<std::endl;
        return false;
    }
    std::string line;
    while(std::getline(inFile,line)){\

        //judge if file is empty
        if(inFile.peek() == EOF){
            std::cout << "File is empty, no users loaded." << std::endl;
            return true;
        }

        //read user info line by line,and using substr to cut string
        if(line.find("Username:")!=std::string::npos){
            //"9" is the length of "Username:" and so on
            std::string username=line.substr(9);
            std::getline(inFile,line);
            int age=std::stoi(line.substr(5));
            std::getline(inFile,line);
            std::string sexyty=line.substr(7);
            User user(username,age,sexyty);
            std::getline(inFile,line);
            if(line.find("Intersting Things:")!=std::string::npos){
                //using substr toget interesting things into pieces
                std::string items=line.substr(18);
                size_t pos=0;
                std::string token;
                while((pos=items.find(","))!=std::string::npos){
                    token=items.substr(0,pos);

                    //add check for empty token
                    if(!token.empty()){
                    user.addInterestingThing(token);
                    }
                    items.erase(0,pos+1);
                }
            }
            else{
                std::cout<<"there is no intersting things,please check is!"<<std::endl;
            }
            // insert loaded user without default-construction
            users.emplace(username, user);
        }
        else{
            std::cout<<"your file's format is incorrect,please check it"<<std::endl;
            return false;
        }
    }
    inFile.close();
    std::cout<<"Database loaded from file successfully!"<<std::endl;
    return true;
}

// database.cpp
bool Database::updateUser(const User& user){
    auto it = users.find(user.getName());
    if(it != users.end()){
        // 更新已有用户信息
        it->second = user;
        std::cout << "User " << user.getName() << " updated successfully!" << std::endl;
        return true;
    } else {
        std::cout << "User " << user.getName() << " not found. Cannot update!" << std::endl;
        return false;
    }
}


void Database::clearAllUsers(){
    users.clear();
    std::cout<<"All users cleared successfully!"<<std::endl;
}

