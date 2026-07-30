#pragma once

#include <string>

#include "http_request.h"

class Router
{
public:
    std::string route(const HttpRequest& request);
};