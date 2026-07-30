#include "parser.h"

#include <sstream>

HttpRequest HttpParser::parse(const std::string& request)
{
    HttpRequest httpRequest;

    std::stringstream stream(request);
    std::string line;

    //--------------------------------------------------
    // Parse Request Line
    //--------------------------------------------------

    if (std::getline(stream, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        std::stringstream firstLine(line);

        firstLine >> httpRequest.method
                  >> httpRequest.path
                  >> httpRequest.version;
    }

    //--------------------------------------------------
    // Parse Headers
    //--------------------------------------------------

    while (std::getline(stream, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.empty())
        {
            break;
        }

        std::size_t colonPosition = line.find(':');

        if (colonPosition == std::string::npos)
        {
            continue;
        }

        std::string key = line.substr(0, colonPosition);
        std::string value = line.substr(colonPosition + 1);

        if (!value.empty() && value.front() == ' ')
        {
            value.erase(0, 1);
        }

        httpRequest.headers[key] = value;
    }

    //--------------------------------------------------
    // Parse Body
    //--------------------------------------------------

    std::ostringstream body;

    body << stream.rdbuf();

    httpRequest.body = body.str();

    return httpRequest;
}