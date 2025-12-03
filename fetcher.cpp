#include "fetcher.h"
#include <curl/curl.h>
//intruduct curl library for http request


//callback function to handle data received from curl
size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp){
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string FETCHER::NewsFetcher(){
    CURL* curl = curl_easy_init();
    CURLcode res;
    std::string response;

    if (!curl) {
        //a result for curl init failed
        std::cerr << "curl init failed\n";
        return response;
    }

    //an api which using to fetch news data in json format
    std::string url = "https://api.jisuapi.com/news/get?channel=头条&start=0&num=10&appkey=26b0320fd72a9f6f";
    if(curl){
        //gain status code so that can judge request success or not
        long status_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, nullptr);
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");


        curl_easy_setopt(curl,CURLOPT_URL,url.c_str());

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        //0l means do not verify ssl certificate

        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteCallBack);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response);

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        //10l means 10 seconds timeout

        res = curl_easy_perform(curl);

        if(res != CURLE_OK){
            //check if curl perform is successful
            std::cerr<<"curl_easy_perform() failed: "<<curl_easy_strerror(res)<<std::endl;
            lastErrorMessage = curl_easy_strerror(res);
        }

        if (status_code != 200) {
            lastStatusCode = status_code;
            lastErrorMessage = "HTTP error code: " + std::to_string(status_code);
            //check http status code
            std::cerr << "HTTP error code: " << status_code << "\n";
        }
        curl_easy_cleanup(curl);
    }
    return response;
}

//using to get last status code
long FETCHER::getLastStatusCode() const {
    return lastStatusCode;
}

//using to get last error message
std::string FETCHER::getLastErrorMessage() const {
    return lastErrorMessage;
}