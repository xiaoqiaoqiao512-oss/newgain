#ifndef NEWS_H
#define NEWS_H

#include <iostream>
#include <string>
#include <vector>

class News{

    public:
    //news status
        int id;
        std::string title;
        std::string content;
        std::string author;
        std::string category;
        std::string publishDate;
        std::string origin;
        News(int newsId, const std::string& newsTitle, const std::string& newsContent, const std::string& newsAuthor,
             const std::string& newsCategory, const std::string& newsPublishDate,
             const std::string& newsOrigin);
        
        //set news info
        void printNews() const; 
        int getId() const;
        void setId(int newsId);
        void setTitle(const std::string& newsTitle);
        void setContent(const std::string& newsContent);
        void setAuthor(const std::string& newsAuthor);
        void setCategory(const std::string& newsCategory);
        void setPublishDate(const std::string& newsPublishDate);
        void setOrigin(const std::string& newsOrigin);
        
        //get news info
        std::string getTitle() const;
        std::string getContent() const;
        std::string getCategory() const;

        //news information
        std::string getNewInfo() const;
        
        //news list
        std::vector<News> newsList;

        //fetch news from json
        static std::vector<News> parseNewsJson(const std::string& NewsJson);


};

#endif