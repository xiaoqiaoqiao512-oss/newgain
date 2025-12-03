#ifndef FETCHER_H
#define FETCHER_H

#include<iostream>
#include <string>

class FETCHER{
    private:
        long lastStatusCode = 0;
        std::string lastErrorMessage = "";

    public:
        std::string NewsFetcher();
        long getLastStatusCode() const;
        std::string getLastErrorMessage() const;
};

#endif