#include "router.h"
#include "file_reader.h"
#include "mime_type.h"

std::string Router::route(const HttpRequest& request)
{
    FileReader reader;
    MimeType mime;

    std::string filePath;

    //----------------------------------
    // Home Page
    //----------------------------------

    if (request.path == "/")
    {
        filePath = "static/index.html";
    }
    else
    {
        filePath = "static" + request.path;
    }

    //----------------------------------
    // File Exists?
    //----------------------------------

    std::string status;

    if (reader.exists(filePath))
    {
        status = "HTTP/1.1 200 OK";
    }
    else
    {
        status = "HTTP/1.1 404 Not Found";

        filePath = "static/404.html";
    }

    //----------------------------------
    // Read File
    //----------------------------------

    std::string body =
        reader.readFile(filePath);

    //----------------------------------
    // MIME Type
    //----------------------------------

    std::string contentType =
        mime.getType(filePath);

    //----------------------------------
    // Build Response
    //----------------------------------

    std::string response =
        status + "\r\n"
        "Content-Type: " +
        contentType +
        "\r\n"
        "Content-Length: " +
        std::to_string(body.size()) +
        "\r\n"
        "Connection: close\r\n"
        "\r\n"
        + body;

    return response;
}