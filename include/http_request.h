#pragma once

#include <map>
#include <string>

struct HttpRequest
{
    // Request Line
    std::string method;
    std::string path;
    std::string version;

    // HTTP Headers
    std::map<std::string, std::string> headers;

    // HTTP Request Body (used for POST, PUT, PATCH)
    std::string body;
};