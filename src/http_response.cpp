#include "http_response.h"

#include <sstream>

HttpResponse::HttpResponse()
{
    statusCode = 200;
    statusMessage = "OK";
}

void HttpResponse::setStatus(int code, const std::string& message)
{
    statusCode = code;
    statusMessage = message;
}

void HttpResponse::setHeader(const std::string& key, const std::string& value)
{
    headers[key] = value;
}

void HttpResponse::setBody(const std::string& content)
{
    body = content;
}

std::string HttpResponse::toString() const
{
    std::ostringstream response;

    response << "HTTP/1.1 "
             << statusCode
             << " "
             << statusMessage
             << "\r\n";

    for (const auto& header : headers)
    {
        response << header.first
                 << ": "
                 << header.second
                 << "\r\n";
    }

    response << "Content-Length: "
             << body.size()
             << "\r\n";

    response << "\r\n";

    response << body;

    return response.str();
}