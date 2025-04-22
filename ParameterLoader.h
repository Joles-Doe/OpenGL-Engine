#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <fstream>
#include <exception>

#include "SharedStructs&Enums.h"

class ParameterLoader
{
public:
	ParameterLoader(const std::string& _path);

	float GetFloat(const std::string& _key, float _defaultVal = 0.0f);
	std::string GetString(const std::string& _key, const std::string& _defaultVal = "");

private:
	std::unordered_map<std::string, std::string> mParameterMap;

	std::string TrimWhitespace(std::string _str);
};

