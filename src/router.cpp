#include "router.h"

#include "file_reader.h"
#include "mime_type.h"

HttpResponse Router::route(const HttpRequest& request)
{
    HttpResponse response;

    FileReader fileReader;
    MimeType mimeType;

    //--------------------------------------------------
    // Dynamic Route : POST /echo
    //--------------------------------------------------

    if (request.method == "POST" &&
        request.path == "/echo")
    {
        response.setStatus(200, "OK");

        response.setHeader(
            "Content-Type",
            "text/plain");

        response.setBody(
            "You sent:\n\n" + request.body);

        return response;
    }

    //--------------------------------------------------
    // Determine requested file
    //--------------------------------------------------

    std::string path = request.path;

    if (path == "/")
    {
        path = "/index.html";
    }

    std::string filePath = "static" + path;

    //--------------------------------------------------
    // File exists
    //--------------------------------------------------

    if (fileReader.exists(filePath))
    {
        std::string content = fileReader.readFile(filePath);

        response.setStatus(200, "OK");

        response.setHeader(
            "Content-Type",
            mimeType.getType(filePath));

        response.setBody(content);

        return response;
    }

    //--------------------------------------------------
    // 404 Not Found
    //--------------------------------------------------

    std::string notFound =
        fileReader.readFile("static/404.html");

    response.setStatus(404, "Not Found");

    response.setHeader(
        "Content-Type",
        "text/html");

    response.setBody(notFound);

    return response;
}