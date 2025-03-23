#include "SFTPClient.h"
#include <curl/curl.h>
#include <iostream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), total);
    return total;
}

SFTPClient::SFTPClient(const std::string& url, const std::string& user, const std::string& password)
    : m_url(url), m_user(user), m_password(password) {}

SFTPClient::~SFTPClient() {}

std::string SFTPClient::extractData() {
    std::string data;
    CURL* curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
        std::string creds = m_user + ":" + m_password;
        curl_easy_setopt(curl, CURLOPT_USERPWD, creds.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return data;
}
