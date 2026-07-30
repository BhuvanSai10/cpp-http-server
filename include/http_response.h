#pragma once

#include <map>
#include <string>

class HttpResponse
{
public:
    HttpResponse();

    void setStatus(int code, const std::string& message);

    void setHeader(
        const std::string& key,
        const std::string& value);

    void setBody(const std::string& body);

    std::string toString() const;

    int getStatusCode() const;

    std::string getStatusMessage() const;

private:
    int statusCode;
    std::string statusMessage;

    std::map<std::string, std::string> headers;

    std::string body;
};