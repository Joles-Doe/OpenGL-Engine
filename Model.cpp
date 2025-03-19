#include "Model.h"

Model::Model(const std::string& _path) : mVaoID(0), mVboID(0), mDirty(false)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> tcs;
    std::vector<glm::vec3> normals;
    std::string currentline;

    std::ifstream file(_path.c_str());

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open model [" + _path + "]");
    }

    while (!file.eof())
    {
        std::getline(file, currentline);
        if (currentline.length() < 1) continue;

        std::vector<std::string> tokens;
        SplitStringWhitespace(currentline, tokens);
        if (tokens.size() < 1) continue;

        if (tokens.at(0) == "v" && tokens.size() >= 4)
        {
            glm::vec3 p(atof(tokens.at(1).c_str()),
                atof(tokens.at(2).c_str()),
                atof(tokens.at(3).c_str()));

            positions.push_back(p);
        }
        else if (tokens.at(0) == "vt" && tokens.size() >= 3)
        {
            glm::vec2 tc(atof(tokens.at(1).c_str()),
                1.0f - atof(tokens.at(2).c_str()));

            tcs.push_back(tc);
        }
        else if (tokens.at(0) == "vn" && tokens.size() >= 4)
        {
            glm::vec3 n(atof(tokens.at(1).c_str()),
                atof(tokens.at(2).c_str()),
                atof(tokens.at(3).c_str()));

            normals.push_back(n);
        }
        else if (tokens.at(0) == "f" && tokens.size() >= 4)
        {
            Face f;
            std::vector<std::string> sub;
            SplitString(tokens.at(1), '/', sub);
            if (sub.size() >= 1) f.a.mPosition = positions.at(atoi(sub.at(0).c_str()) - 1);
            if (sub.size() >= 2) f.a.mTextureCoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
            if (sub.size() >= 3) f.a.mNormal = normals.at(atoi(sub.at(2).c_str()) - 1);

            for (size_t ti = 2; ti + 1 < tokens.size(); ti++)
            {
                SplitString(tokens.at(ti), '/', sub);
                if (sub.size() >= 1) f.b.mPosition = positions.at(atoi(sub.at(0).c_str()) - 1);
                if (sub.size() >= 2) f.b.mTextureCoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
                if (sub.size() >= 3) f.b.mNormal = normals.at(atoi(sub.at(2).c_str()) - 1);

                SplitString(tokens.at(ti + 1), '/', sub);
                if (sub.size() >= 1) f.c.mPosition = positions.at(atoi(sub.at(0).c_str()) - 1);
                if (sub.size() >= 2) f.c.mTextureCoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
                if (sub.size() >= 3) f.c.mNormal = normals.at(atoi(sub.at(2).c_str()) - 1);

                mFaces.push_back(f);
                mDirty = true;
            }
        }
    }
}

Model& Model::operator=(const Model& _assign)
{
    mFaces = _assign.mFaces;
    mDirty = true;

    return *this;
}

Model::~Model()
{
    if (mVaoID)
    {
        glDeleteVertexArrays(1, &mVaoID);
    }

    if (mVboID)
    {
        glDeleteBuffers(1, &mVboID);
    }
}

GLsizei Model::VertexCount() const
{
    return (GLsizei)mFaces.size() * 3;
}

GLuint Model::ID()
{
    if (!mFaces.size())
    {
        throw std::runtime_error("Model is empty");
    }

    if (!mVboID)
    {
        glGenBuffers(1, &mVboID);

        if (!mVboID)
        {
            throw std::runtime_error("Failed to generate vertex buffer");
        }
    }

    if (!mVaoID)
    {
        glGenVertexArrays(1, &mVaoID);

        if (!mVaoID)
        {
            throw std::runtime_error("Failed to generate vertex array");
        }
    }

    if (mDirty)
    {
        std::vector<GLfloat> data;

        for (size_t fi = 0; fi < mFaces.size(); ++fi)
        {
            data.push_back(mFaces[fi].a.mPosition.x);
            data.push_back(mFaces[fi].a.mPosition.y);
            data.push_back(mFaces[fi].a.mPosition.z);
            data.push_back(mFaces[fi].a.mTextureCoord.x);
            data.push_back(mFaces[fi].a.mTextureCoord.y);
            data.push_back(mFaces[fi].a.mNormal.x);
            data.push_back(mFaces[fi].a.mNormal.y);
            data.push_back(mFaces[fi].a.mNormal.z);

            data.push_back(mFaces[fi].b.mPosition.x);
            data.push_back(mFaces[fi].b.mPosition.y);
            data.push_back(mFaces[fi].b.mPosition.z);
            data.push_back(mFaces[fi].b.mTextureCoord.x);
            data.push_back(mFaces[fi].b.mTextureCoord.y);
            data.push_back(mFaces[fi].b.mNormal.x);
            data.push_back(mFaces[fi].b.mNormal.y);
            data.push_back(mFaces[fi].b.mNormal.z);

            data.push_back(mFaces[fi].c.mPosition.x);
            data.push_back(mFaces[fi].c.mPosition.y);
            data.push_back(mFaces[fi].c.mPosition.z);
            data.push_back(mFaces[fi].c.mTextureCoord.x);
            data.push_back(mFaces[fi].c.mTextureCoord.y);
            data.push_back(mFaces[fi].c.mNormal.x);
            data.push_back(mFaces[fi].c.mNormal.y);
            data.push_back(mFaces[fi].c.mNormal.z);
        }

        glBindBuffer(GL_ARRAY_BUFFER, mVboID);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data.at(0), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(mVaoID);
        glBindBuffer(GL_ARRAY_BUFFER, mVboID);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
            8 * sizeof(data.at(0)), (void*)0);

        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
            8 * sizeof(data.at(0)), (void*)(3 * sizeof(GLfloat)));

        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
            8 * sizeof(data.at(0)), (void*)(5 * sizeof(GLfloat)));

        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        mDirty = false;
    }

    return mVaoID;
}

void Model::SplitStringWhitespace(const std::string& _input, std::vector<std::string>& _output)
{
    std::string curr;

    _output.clear();

    for (size_t i = 0; i < _input.length(); i++)
    {
        if (_input.at(i) == ' ' ||
            _input.at(i) == '\r' ||
            _input.at(i) == '\n' ||
            _input.at(i) == '\t')
        {
            if (curr.length() > 0)
            {
                _output.push_back(curr);
                curr = "";
            }
        }
        else
        {
            curr += _input.at(i);
        }
    }

    if (curr.length() > 0)
    {
        _output.push_back(curr);
    }
}

void Model::SplitString(const std::string& _input, char _splitter, std::vector<std::string>& _output)
{
    std::string curr;

    _output.clear();

    for (size_t i = 0; i < _input.length(); i++)
    {
        if (_input.at(i) == _splitter)
        {
            _output.push_back(curr);
            curr = "";
        }
        else
        {
            curr += _input.at(i);
        }
    }

    if (curr.length() > 0)
    {
        _output.push_back(curr);
    }
}