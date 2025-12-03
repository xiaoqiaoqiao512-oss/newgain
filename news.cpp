#include "news.h"
#include"json.hpp"

using json = nlohmann::json;

//news构造函数
News::News(int newsId, const std::string& newsTitle, const std::string& newsContent, const std::string& newsAuthor,
             const std::string& newsCategory, const std::string& newsPublishDate,
             const std::string& newsOrigin) : id(newsId), title(newsTitle), content(newsContent), author(newsAuthor),
             category(newsCategory), publishDate(newsPublishDate), origin(newsOrigin) {
    std::cout << "News titled \"" << newsTitle << "\" created successfully!" << std::endl;
    newsList.push_back(*this);
}

//设置新闻ID
void News::setId(int newsId){
    id = newsId;
}
//获取新闻ID
int News::getId() const{
    return id;
}
//设置新闻标题
void News::setTitle(const std::string& newsTitle){
    title = newsTitle;
}
//设置新闻内容
void News::setContent(const std::string& newsContent){
    content = newsContent;
}
//设置新闻作者
void News::setAuthor(const std::string& newsAuthor){
    author = newsAuthor;
}
//设置新闻类别
void News::setCategory(const std::string& newsCategory){
    category = newsCategory;
}
//设置新闻发布日期
void News::setPublishDate(const std::string& newsPublishDate){
    publishDate = newsPublishDate;
}
//设置新闻来源
void News::setOrigin(const std::string& newsOrigin){
    origin = newsOrigin;
}

//获取新闻标题
std::string News::getTitle() const{
    return title;
}
//获取新闻内容
std::string News::getContent() const{
    return content;
}
//获取新闻类别
std::string News::getCategory() const{
    return category;
}

//打印新闻信息
void News::printNews() const{
    std::cout << "News ID: " << id << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Category: " << category << std::endl;
    std::cout << "Publish Date: " << publishDate << std::endl;
    std::cout << "Origin: " << origin << std::endl;
}

//a function to clean html tags from content
std::string cleanText(const std::string& etxt){
    std::string rst;
    bool inTag = false;

    for(char c : etxt){
        if(c == '<'){
            inTag = true;
        } else if(c == '>'){
            inTag = false;
        } else if(!inTag){
            rst += c;
        }
    }
    return rst;
}


//news from json
//using nlohmann json library to parse json
std::vector<News> News::parseNewsJson(const std::string& NewsJson){
    std::vector<News> newlsit;

    try{
        auto j = json::parse(NewsJson);

        //check if json contains news array
        if(j.contains("status")&&j["status"]==0){
            auto newsArray = j["result"]["list"];
            for(const auto& item : newsArray){
                std::string cleanedContent = cleanText(item.value("content",""));
                News news(
                    item.value("num",0),
                    item.value("title",""),
                    cleanedContent,
                    item.value("src",""),
                    item.value("category",""),
                    item.value("time",""),
                    item.value("weburl","")
                );
                newlsit.push_back(news);
            }
        } else {
            //if status is not 0, print error message
            std::cerr << "Error: API returned status " << j["status"] << std::endl;
        }
    }
    catch(const json::parse_error& e){
        //return error message
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    catch(const std::exception& e){
        //other exceptions
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return newlsit;
}

//get news information
std::string News::getNewInfo() const{
    std::string info = "Title: " + title + "\n";
    info += "Author: " + author + "\n";
    info += "Category: " + category + "\n";
    info += "Publish Date: " + publishDate + "\n";
    info += "Origin: " + origin + "\n";
    info += "Content: " + content + "\n";
    return info;
}


