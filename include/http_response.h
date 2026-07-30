#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <map>
#include <string>

class HttpResponse
{
private:
    int statusCode;
    std::string statusMessage;

    std::map<std::string, std::string> headers;

    std::string body;

public:
    HttpResponse();

    void setStatus(int code, const std::string& message);

    void setHeader(const std::string& key,
                   const std::string& value);

    void setBody(const std::string& content);

    std::string toString() const;
};

#endif