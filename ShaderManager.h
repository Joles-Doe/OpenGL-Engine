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
	ShaderManager(const std::string& _defaultShaderPath);
	ShaderManager(const std::string& _defaultVertexPath, const std::string& _defaultFragmentPath);

	/// <summary>
	/// Attempts to compile and add a shader to the shader cache. Returns nullptr if key already exists, or if shader compilation fails.
	/// </summary>
	/// <param name="_key"> Name of the key used for the shader </param>
	/// <param name="_generalPath"> The general path to the vertex and fragment shaders. Assumes both shaders share the same name </param>
	/// <returns> Shared_ptr to compiled shader on success, nullptr on failure </returns>
	std::shared_ptr<ShaderProgram> AddShader(const std::string& _key, const std::string& _generalPath);
	
	/// <summary>
	/// Attempts to compile and add a shader to the shader cache. Returns nullptr if key already exists, or if shader compilation fails.
	/// </summary>
	/// <param name="_key"> Name of the key used for the shader </param>
	/// <param name="_vertexPath"> Path to the vertex shader </param>
	/// <param name="_fragmentPath"> Path to the fragment shader </param>
	/// <returns> Shared_ptr to compiled shader on success, nullptr on failure </returns>
	std::shared_ptr<ShaderProgram> AddShader(const std::string& _key, const std::string& _vertexPath, const std::string& _fragmentPath);
	
	/// <summary>
	/// Adds a shader to the shader cache.
	/// </summary>
	/// <param name="_key"> Name of the key used for the shader </param>
	/// <param name="_shaderProgram"></param>
	void AddShader(const std::string& _key, std::shared_ptr<ShaderProgram> _shaderProgram);

	/// <summary>
	/// Finds and returns a shader using the given key.
	/// </summary>
	/// <param name="_key"> Name of key </param>
	/// <returns> Shared_ptr to compiled shader on success, nullptr on failure </returns>
	std::shared_ptr<ShaderProgram> GetShader(const std::string& _key) const;

	//Add a remove shader method?

private:
	std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> mShaderCache;

	std::shared_ptr<ShaderProgram> Load(const std::string& _vertexPath, const std::string& _fragmentPath);
};