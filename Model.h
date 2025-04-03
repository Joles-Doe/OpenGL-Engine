#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <string>
#include <fstream>

class Model
{
public:
	struct Vertex
	{
		glm::vec3 mPosition;
		glm::vec2 mTextureCoord;
		glm::vec3 mNormal;
	};
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

	std::vector<Face>* GetFaceVector() { return &mFaces; }

	GLsizei VertexCount() const;
	GLuint ID();
private:
	
	void SplitStringWhitespace(const std::string& _input, std::vector<std::string>& _output);
	void SplitString(const std::string& _input, char _splitter, std::vector<std::string>& _output);

	std::vector<Face> mFaces;

	GLuint mVaoID;
	GLuint mVboID;
	
	bool mDirty;
};