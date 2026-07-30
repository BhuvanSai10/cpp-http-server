#ifndef ROUTER_H
#define ROUTER_H

#include "http_request.h"
#include "http_response.h"

class Router
{
public:
    HttpResponse route(const HttpRequest& request);
};

#endif