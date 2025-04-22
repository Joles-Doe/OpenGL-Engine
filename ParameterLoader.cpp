#include "ParameterLoader.h"

ParameterLoader::ParameterLoader(const std::string& _path)
{
    std::ifstream file(_path.c_str());
    std::string currentLine;

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open parameters: [" + _path + "]");
    }

    while (std::getline(file, currentLine))
    {
        // Skip the line if it's invalid
        if (currentLine.empty() || currentLine[0] == '#' || currentLine.find('=') == std::string::npos) continue;

        // Remove semi colon at end, if present
        if (currentLine.back() == ';') currentLine.pop_back();

        // Find the position of the '=' character
        size_t equalPos = currentLine.find('=');

        // Grab values
        std::string key = currentLine.substr(0, equalPos);
        std::string value = currentLine.substr(equalPos + 1);

        key = TrimWhitespace(key);
        value = TrimWhitespace(value);

        mParameterMap[key] = value;
    }
}

float ParameterLoader::GetFloat(const std::string& _key, float _defaultVal)
{
    auto it = mParameterMap.find(_key);
    return it != mParameterMap.end() ? std::stof(mParameterMap[_key]) : _defaultVal;
}

std::string ParameterLoader::GetString(const std::string& _key, const std::string& _defaultVal)
{
    auto it = mParameterMap.find(_key);
    return it != mParameterMap.end() ? it->second : _defaultVal;
}

std::string ParameterLoader::TrimWhitespace(std::string _str)
{
    _str.erase(0, _str.find_first_not_of(" \t\r\n"));
    _str.erase(_str.find_last_not_of(" \t\r\n") + 1);
    return _str;
}
