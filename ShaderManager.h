#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "ShaderProgram.h"

/// <summary>
///	ShaderManager - Holds all of the shaders in one central location, and automatically compiles them when needed.
/// </summary>
class ShaderManager
{
public:
	ShaderManager();

	std::shared_ptr<ShaderProgram> AddShader(std::string _generalPath);
	std::shared_ptr<ShaderProgram> AddShader(std::string _vertexPath, std::string _fragmentPath);

private:
	std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> mShaderCache;
};