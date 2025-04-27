#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <fstream>
#include <exception>

#include "SharedStructs&Enums.h"

/// <summary>
/// ParameterLoader - Loads simulation parameters when the program runs.
/// </summary>
class ParameterLoader
{
public:
	ParameterLoader(const std::string& _path);

	/// <summary>
	/// Returns a value from the simulation parameters.
	/// </summary>
	/// <param name="_key"> Key to retrieve the value from. This is the name of the variable located in the parameter file. </param>
	/// <returns> Returns the float held by the key, else returns 0.0 if key is invalid </returns>
	float GetFloat(const std::string& _key, float _defaultVal = 0.0f);

	/// <summary>
	/// Returns a value from the simulation parameters.
	/// </summary>
	/// <param name="_key"> Key to retrieve the value from. This is the name of the variable located in the parameter file. </param>
	/// <returns> Returns the string held by the key, else returns "" if key is invalid </returns>
	std::string GetString(const std::string& _key, const std::string& _defaultVal = "");

private:
	std::unordered_map<std::string, std::string> mParameterMap;

	/// <summary>
	/// Removes whitespace from a string
	/// </summary>
	/// <param name="_str"> String to change </param>
	/// <returns> String output </returns>
	std::string TrimWhitespace(std::string _str);
};

