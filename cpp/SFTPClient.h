#ifndef SFTPCLIENT_H
#define SFTPCLIENT_H

#include <string>
class SFTPClient {
public:
    SFTPClient(const std::string& url, const std::string& user, const std::string& password);
    ~SFTPClient();
    std::string extractData();
private:
    std::string m_url;
    std::string m_user;
    std::string m_password;
};

#endif // SFTPCLIENT_H
