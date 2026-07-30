#include "http_response.h"

#include <sstream>

HttpResponse::HttpResponse()
{
    statusCode = 200;
    statusMessage = "OK";
}

void HttpResponse::setStatus(
    int code,
    const std::string& message)
{
    statusCode = code;
    statusMessage = message;
}

void HttpResponse::setHeader(
    const std::string& key,
    const std::string& value)
{
    headers[key] = value;
}

void HttpResponse::setBody(
    const std::string& bodyContent)
{
    body = bodyContent;

    headers["Content-Length"] =
        std::to_string(body.size());
}

std::string HttpResponse::toString() const
{
    std::ostringstream response;

    response
        << "HTTP/1.1 "
        << statusCode
        << " "
        << statusMessage
        << "\r\n";

    for (const auto& header : headers)
    {
        response
            << header.first
            << ": "
            << header.second
            << "\r\n";
    }

    response << "\r\n";

    response << body;

    return response.str();
}

int HttpResponse::getStatusCode() const
{
    return statusCode;
}

std::string HttpResponse::getStatusMessage() const
{
    return statusMessage;
}