#include "ui.h"


//ui构造函数
ui::ui(const std::vector<News>& news, Database& database) : db(database), newsList(news), user(nullptr) {
    std::cout << "UI initialized successfully!" << std::endl;
}

//set current user
void ui::setUser(User* usr){
            user = usr;
        }

//user sign in
User* ui::userSignIn(){
    std::cout<<"please enter your username to sign in: ";
    std::string username;
    std::cin>>username;
    // try to find user in database
    User* found = db.findUser(username);
    if(found){
        std::cout<<"Sign in successful! Welcome back, "<<username<<"!"<<std::endl;
        return found;
    }

    // if not found, prompt to sign up
    std::cout<<"User not found! Please sign up first."<<std::endl;
    int age;
    std::string sexyty;
    std::cout<<"please enter your age: ";
    std::cin>>age;
    std::cout<<"please enter your sexyty:(m/f) ";
    std::cin>>sexyty;
    
    //add new user to database
    db.addUser(User(username, age, sexyty));
    return db.findUser(username);
}

//show main menu
void ui::showMenu(){
    while(true){
        // let user choose an option and handle the choice
        std::cout<<"===== News Management System ====="<<std::endl;
        std::cout<<"1. Set User information"<<std::endl;
        std::cout<<"2. View User information"<<std::endl;
        std::cout<<"3. View Self recommended News"<<std::endl;
        std::cout<<"4. Find other users"<<std::endl;
        std::cout<<"5. adjust User information"<<std::endl;
        std::cout<<"6. Search News by Title"<<std::endl;
        std::cout<<"7. Exit"<<std::endl;
        std::cout<<"Please enter your choice (1-7): ";
        int choice;
        std::cin>>choice;
        handselfchoice(choice);

        if(choice == 7) break;
    }
}

//check user input
void ui::handselfchoice(int choice){
    switch (choice){
        case 1:
            {
                setUserInfo();  
                break;            
            }
        case 2:
            {
                viewUserInfo();
                break;
            }
        case 3:
            {
                ViewSelfRconmendedNews();
                saveFavorite();
                break;
            }
        case 4:
            {
                findOtherUsers();
                break;
            }
        case 5:
            {
                updateUserInfo();
                break;
            }
        case 6:
            {
                searchnews();
                break;
            }
        case 7:
            {
                std::cout<<"Exiting the system. Goodbye!"<<std::endl;
                break;
            }
        default:
            {
                std::cout<<"Invalid choice. Please try again."<<std::endl;
                break;
            }
    }
}

//set user information
void ui::setUserInfo(){
    std::string name;
    int age;
    std::string sexyty;
    std::cout<<"please enter your name:";
    std::cin>>name;
    std::cout<<std::endl;
    std::cout<<"please enter your age:";
    std::cin>>age;
    std::cout<<std::endl;
    std::cout<<"please enter your sexyty:(m/f)";
    std::cin>>sexyty;
    std::cout<<std::endl;
    if(user) delete user;  // 避免内存泄漏
    user = new User(name, age, sexyty);
    std::cout<<"User information set successfully!"<<std::endl; 

    //remind user to add interesting things
    std::cout<<"A better user profile helps us recommend better news for you!"<<std::endl;  
    addInterestingThings();

    //check if interesting things are added
    if(user->getInterestingThing().empty()){
        std::cout<<"No interesting things added. Please add at least one interesting thing."<<std::endl;
        addInterestingThings();
    }
    std::cout<<"finished! enjoy your news reading experience!"<<std::endl;
}

//add interesting things
void ui::addInterestingThings(){
    std::cout<<"please add your interesting things(you can type 'finish' to end your input): ";
    while(true){
        std::string interestingthing;
        std::cin>>interestingthing;
        if(interestingthing == "finish"){
            break;
        } else {
            user->addInterestingThing(interestingthing);
            std::cout<<"Continue putting or choose others options"<<std::endl;
        }
    }
}

//view user information
void ui::viewUserInfo(){
    user->printInfo();
}

//view self recommended news
void ui::ViewSelfRconmendedNews(){
    std::cout<<"Displaying recommended news based on your profile..."<<std::endl;
    //dummy implementation
    auto interst =user->getInterestingThing();
    //exception handling for no interesting things set
    if(interst.empty()){
        std::cout<<"No interesting things set. Please set your interesting things first."<<std::endl;
        addInterestingThings();
        return;
    }
    for(const auto& interstitem:interst){
        std::cout<<"Based on your interest in "<<interstitem<<", we recommend the following news:"<<std::endl;
        for(const auto& news:newsList){
            if(news.getCategory() == interstitem){
                news.printNews();
            }
        }
    }
}

//save favorite news
void ui::saveFavorite(){
    std::cout<<"Would you like to save any favorite news? (yes/no): ";
    std::string choice;
    std::cin>>choice;
    if(choice == "yes"){
        std::cout<<"Please enter the title keyword of the news you want to save: ";
        std::string titleKeyword;
        std::cin>>titleKeyword;
        std::vector<News> result;
        if(db.searchNewsByName(titleKeyword,result)){
            db.saveFavoriteNews(result, user->getName() + "_favorites.json");
            std::cout<<"Favorite news saved successfully!"<<std::endl;
        } else {
            std::cout<<"No news found with the given title keyword."<<std::endl;
        }
    } else {
        std::cout<<"No favorite news saved."<<std::endl;
    }
}

//a easy code to find other users
void ui::findOtherUsers(){
    std::cout<<"Finding other users with similar interests..."<<std::endl;
    std::string otherusername;
    User* otheruser=db.findUser(otherusername);
    if(otheruser){
        std::cout<<"User found!"<<std::endl;
        otheruser->printInfo();
    } else {
        std::cout<<"User not found!"<<std::endl;
        return;
    }

    std::cout<<"Name: "<<otheruser->getName()<<std::endl;
    std::cout<<"Age: "<<otheruser->getAge()<<std::endl;
    std::cout<<"Sexyty: "<<otheruser->getSexyty()<<std::endl;
    std::cout<<"Interesting Things: ";
    for(const auto& it : otheruser->getInterestingThing()){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Feature under development. Please check back later."<<std::endl;
}


void ui::updateUserInfo(){
    if(!user){
        std::cout << "No signed-in user!" << std::endl;
        return;
    }

    std::cout << "Updating user info for " << user->getName() << std::endl;
    
    int age;
    std::string sexyty;
    std::cout << "Enter new age: ";
    std::cin >> age;
    std::cout << "Enter new gender (m/f): ";
    std::cin >> sexyty;

    user->addAge(age);
    user->addSexyty(sexyty);

    // 可以清空兴趣再重新添加
    user->getInterestingThing().clear();
    std::cout<<"intersting things will be reset"<<std::endl;
    addInterestingThings();

    db.updateUser(*user);
}

void ui::searchnews(){
    std::cout<<"please enter the news title you want to search: ";
    std::string title;
    std::cin>>title;
    std::vector<News> result;
    if(db.searchNewsByName(title,result)){
        std::cout<<"Search results:"<<std::endl;
        for(const auto& news:result){
            news.printNews();
        }
    } else {
        std::cout<<"please change your search!"<<title<<std::endl;
    }
}
