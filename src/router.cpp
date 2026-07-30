#include "router.h"

#include "external/json.hpp"
#include "file_reader.h"
#include "mime_type.h"

using json = nlohmann::json;

HttpResponse Router::route(const HttpRequest& request)
{
    HttpResponse response;

    FileReader fileReader;
    MimeType mimeType;

    //--------------------------------------------------
    // Dynamic Route : POST /user
    //--------------------------------------------------

    if (request.method == "POST" &&
        request.path == "/user")
    {
        try
        {
            json requestJson = json::parse(request.body);

            std::string name =
                requestJson["name"];

            std::string course =
                requestJson["course"];

            int age =
                requestJson["age"];

            json responseJson;

            responseJson["status"] = "success";
            responseJson["message"] =
                "Welcome " + name;
            responseJson["course"] = course;
            responseJson["age"] = age;

            response.setStatus(200, "OK");

            response.setHeader(
                "Content-Type",
                "application/json");

            response.setBody(
                responseJson.dump(4));

            return response;
        }
        catch (const json::exception& e)
        {
            json errorJson;

            errorJson["status"] = "error";
            errorJson["message"] = "Invalid JSON";

            response.setStatus(400, "Bad Request");

            response.setHeader(
                "Content-Type",
                "application/json");

            response.setBody(
                errorJson.dump(4));

            return response;
        }
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