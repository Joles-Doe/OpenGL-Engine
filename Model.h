#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <string>
#include <fstream>

/// <summary>
/// Model Class - Holds the Faces of a passed model path to send to the GPU via OpenGL
/// </summary>
class Model
{
public:
	/// <summary>
	/// Vertex Struct - holds the position, normal, and texure coordinate of a specific vertex in the model
	/// </summary>
	struct Vertex
	{
		glm::vec3 mPosition;
		glm::vec2 mTextureCoord;
		glm::vec3 mNormal;
	};
	
	/// <summary>
	/// Face Struct - holds a specific face of the model - comprised of three vertices
	/// </summary>
	struct Face
	{
		Vertex a;
		Vertex b;
		Vertex c;
	};

	Model() : mVaoID(0), mVboID(0), mDirty(false) {};
	Model(const Model& _copy) : mVaoID(0), mVboID(0), mDirty(true), mFaces() {};
	Model(const std::string& _path);

	Model& operator=(const Model& _assign);
	virtual ~Model();

	/// <summary>
	/// Returns the mFaces vector.
	/// </summary>
	/// <returns> A vector containing Face structs </returns>
	const std::vector<Model::Face>& GetFaces() const noexcept { return mFaces; }

	/// <summary>
	/// Returns the count of Vertices within the model.
	/// </summary>
	/// <returns> The amount of Vertex structs in the model </returns>
	GLsizei VertexCount() const { return (GLsizei)mFaces.size() * 3; }

	/// <summary>
	/// Returns the ID of the Vertex array used by the model. 
	/// Utilizes dirty loading, so calling this function inexplicitly initializes Vertex buffer and arrays if none are present.
	/// </summary>
	/// <returns> The OpenGL Vertex array ID of the model </returns>
	GLuint ID();
private:
	/// <summary>
	/// Splits a given string into substrings if any whitespace characters are present.
	/// </summary>
	/// <param name="_input"> String to split </param>
	/// <param name="_output"> Output vector</param>
	void SplitStringWhitespace(const std::string& _input, std::vector<std::string>& _output);
	
	/// <summary>
	/// Splits a given string into substrings dependent on a delimiter.
	/// </summary>
	/// <param name="_input"> String to split </param>
	/// <param name="_splitter"> Delimiter used as the predicate to split the string </param>
	/// <param name="_output"> Output vector </param>
	void SplitString(const std::string& _input, char _splitter, std::vector<std::string>& _output);

	std::vector<Face> mFaces;

	GLuint mVaoID;
	GLuint mVboID;
	
	bool mDirty;
};