#pragma once

#include <string>

class FileReader
{
public:
    bool exists(const std::string& filename);

    std::string readFile(const std::string& filename);
};