#include "ShaderManager.h"

#include <iostream>


ShaderManager::ShaderManager()
{
	// No error handling in constructor, program should stop if the generic shader cannot compile
	mShaderCache.emplace("DEFAULT", std::make_shared<ShaderProgram>());
}

ShaderManager::ShaderManager(const std::string& _defaultShaderPath)
{
	// No error handling in constructor, program should stop if the generic shader cannot compile
	mShaderCache.emplace("DEFAULT", Load(_defaultShaderPath + ".vs", _defaultShaderPath + ".fs"));
}

ShaderManager::ShaderManager(const std::string& _defaultVertexPath, const std::string& _defaultFragmentPath)
{
	// No error handling in constructor, program should stop if the generic shader cannot compile
	mShaderCache.emplace("DEFAULT", Load(_defaultVertexPath, _defaultFragmentPath));
}

std::shared_ptr<ShaderProgram> ShaderManager::AddShader(const std::string& _key, const std::string& _generalPath)
{
	// Early return if element already exists
	if (mShaderCache.find(_key) != mShaderCache.end()) return std::shared_ptr<ShaderProgram>();
	
	std::shared_ptr<ShaderProgram> shader;
	bool success = false;
	// Load with error handling
	try 
	{
		shader = Load(_generalPath + ".vs", _generalPath + ".fs");
		mShaderCache.emplace(_key, shader);
		success = true;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Shader error: { " << e.what() << "}" << std::endl;
	}

	return success ? shader : std::shared_ptr<ShaderProgram>();
}

std::shared_ptr<ShaderProgram> ShaderManager::AddShader(const std::string& _key, const std::string& _vertexPath, const std::string& _fragmentPath)
{
	// Early return if element already exists
	if (mShaderCache.find(_key) != mShaderCache.end()) return std::shared_ptr<ShaderProgram>();

	std::shared_ptr<ShaderProgram> shader;
	bool success = false;
	// Load with error handling
	try
	{
		shader = Load(_vertexPath, _fragmentPath);
		mShaderCache.emplace(_key, shader);
		success = true;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Shader error: { " << e.what() << "}" << std::endl;
	}

	return success ? shader : std::shared_ptr<ShaderProgram>();
}

void ShaderManager::AddShader(const std::string& _key, std::shared_ptr<ShaderProgram> _shaderProgram)
{
	mShaderCache.try_emplace(_key, _shaderProgram);

	// potentially add a boolean return type to show success or failure?
}

std::shared_ptr<ShaderProgram> ShaderManager::GetShader(const std::string& _key) const
{
	auto it = mShaderCache.find(_key);
	return it != mShaderCache.end() ? it->second : std::shared_ptr<ShaderProgram>();
}

std::shared_ptr<ShaderProgram> ShaderManager::Load(const std::string& _vertexPath, const std::string& _fragmentPath)
{
	return std::make_shared<ShaderProgram>(_vertexPath, _fragmentPath);
}