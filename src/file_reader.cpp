#include "file_reader.h"

#include <fstream>
#include <sstream>

bool FileReader::exists(const std::string& filename)
{
    std::ifstream file(filename);

    return file.good();
}

std::string FileReader::readFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return "";
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}