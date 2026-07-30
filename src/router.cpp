#include "router.h"

std::string Router::route(const HttpRequest& request)
{
    std::string body;
    std::string status;

    //-----------------------------------
    // Home Page
    //-----------------------------------

    if (request.path == "/")
    {
        status = "HTTP/1.1 200 OK";

        body =
            "<html>"
            "<body>"
            "<h1>Home Page</h1>"
            "<p>Welcome to my C++ HTTP Server.</p>"
            "</body>"
            "</html>";
    }

    //-----------------------------------
    // About
    //-----------------------------------

    else if (request.path == "/about")
    {
        status = "HTTP/1.1 200 OK";

        body =
            "<html>"
            "<body>"
            "<h1>About Page</h1>"
            "<p>This server is written in C++ using POSIX sockets.</p>"
            "</body>"
            "</html>";
    }

    //-----------------------------------
    // Contact
    //-----------------------------------

    else if (request.path == "/contact")
    {
        status = "HTTP/1.1 200 OK";

        body =
            "<html>"
            "<body>"
            "<h1>Contact</h1>"
            "<p>Email : example@test.com</p>"
            "</body>"
            "</html>";
    }

    //-----------------------------------
    // Unknown Page
    //-----------------------------------

    else
    {
        status = "HTTP/1.1 404 Not Found";

        body =
            "<html>"
            "<body>"
            "<h1>404 Not Found</h1>"
            "<p>The requested page does not exist.</p>"
            "</body>"
            "</html>";
    }

    std::string response =
        status + "\r\n" +
        "Content-Type: text/html\r\n" +
        "Content-Length: " + std::to_string(body.size()) + "\r\n" +
        "Connection: close\r\n" +
        "\r\n" +
        body;

    return response;
}