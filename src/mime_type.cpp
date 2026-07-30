#include "mime_type.h"

bool hasExtension(const std::string& filename,
                  const std::string& ext)
{
    if (filename.length() < ext.length())
        return false;

    return filename.compare(
        filename.length() - ext.length(),
        ext.length(),
        ext) == 0;
}

std::string MimeType::getType(const std::string& filename)
{
    if (hasExtension(filename, ".html"))
        return "text/html";

    if (hasExtension(filename, ".css"))
        return "text/css";

    if (hasExtension(filename, ".js"))
        return "application/javascript";

    if (hasExtension(filename, ".png"))
        return "image/png";

    if (hasExtension(filename, ".jpg"))
        return "image/jpeg";

    if (hasExtension(filename, ".jpeg"))
        return "image/jpeg";

    if (hasExtension(filename, ".gif"))
        return "image/gif";

    if (hasExtension(filename, ".ico"))
        return "image/x-icon";

    if (hasExtension(filename, ".json"))
        return "application/json";

    if (hasExtension(filename, ".txt"))
        return "text/plain";

    return "application/octet-stream";
}