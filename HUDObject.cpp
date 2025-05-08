#include "HUDObject.h"

HUDObject::HUDObject(const glm::vec2& _topLeft, const float& _width, const float& _height) : mVaoID(0), mVboID(0), mEboID(0)
{
    mTopLeft = _topLeft;
    mSize = glm::vec2(_width, _height);

    mKILL = false;
    mDirty = true;

    mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    mUsingImage = false;
    mUsingCustomShader = false;
}

HUDObject::~HUDObject()
{
    if (mVaoID)
    {
        glDeleteVertexArrays(1, &mVaoID);
    }
    
    if (mVboID)
    {
        glDeleteBuffers(1, &mVboID);
    }

    if (mEboID)
    {
        glDeleteBuffers(1, &mEboID);
    }
}

void HUDObject::Start()
{
}

void HUDObject::Update()
{
}

void HUDObject::OnHover()
{
}

void HUDObject::OnClick()
{
}

void HUDObject::Draw(const glm::mat4& _projectionMatrix)
{
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

    if (!mEboID)
    {
        glGenBuffers(1, &mEboID);

        if (!mEboID)
        {
            throw std::runtime_error("Failed to generate element buffer");
        }
    }

    // Initialise the HUD Quad if it's dirty
    if (mDirty)
    {
        // Pos [3], Tex coord [2]
        float quad[] = {
            // x     y     z     u     v
            0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
            0.0f, 1.0f, 0.0f,  0.0f, 1.0f
        };
        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

        glBindVertexArray(mVaoID);
        glBindBuffer(GL_ARRAY_BUFFER, mVboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        glBindVertexArray(0);
        mDirty = false;
    }

    glBindVertexArray(mVaoID);

    /*mCustomShader->SetActive();
    mCustomShader->SetUniform("uProjection", _projectionMatrix);*/

    mShaderStore->ChangeUniform("uProjection", _projectionMatrix);

    if (mUsingImage)
    {
        glBindTexture(GL_TEXTURE_2D, mTexture->ID());
    }
    else
    {
        //mCustomShader->SetUniform("uColor", mColor);
        mShaderStore->ChangeUniform("uColor", mColor);
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mTopLeft, 0.0f));
    model = glm::scale(model, glm::vec3(mSize, 1.0f));

    //mCustomShader->SetUniform("uModel", model);
    mShaderStore->ChangeUniform("uModel", model);

    int currentVAO = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);

    mShaderStore->UpdateShaderUniforms(mCustomShader);

    // Draw elements
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Reset the state
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void HUDObject::Draw(std::shared_ptr<ShaderProgram> _shader)
{
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

    if (!mEboID)
    {
        glGenBuffers(1, &mEboID);

        if (!mEboID)
        {
            throw std::runtime_error("Failed to generate element buffer");
        }
    }

    // Initialise the HUD Quad if it's dirty
    if (mDirty)
    {
        // Pos [3], Tex coord [2]
        float quad[] = {
            // x     y     z     u     v
            0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
            0.0f, 1.0f, 0.0f,  0.0f, 1.0f
        };
        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

        glBindVertexArray(mVaoID);
        glBindBuffer(GL_ARRAY_BUFFER, mVboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        glBindVertexArray(0);
        mDirty = false;
    }

    glBindVertexArray(mVaoID);

    if (mUsingImage)
    {
        glBindTexture(GL_TEXTURE_2D, mTexture->ID());
    }
    else
    {
        _shader->SetUniform("uColor", mColor);
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mTopLeft, 0.0f));
    model = glm::scale(model, glm::vec3(mSize, 1.0f));

    _shader->SetUniform("uModel", model);

    int currentVAO = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);

    // Draw elements
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Reset the state
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void HUDObject::UseCustomShader(const std::string& _key, const std::string& _generalPath)
{
    if (mShaderManager != nullptr)
    {
        if (mShaderManager->GetShader(_key) == nullptr)
        {
            mCustomShader = mShaderManager->AddShader(_key, _generalPath);
            mUsingCustomShader = true;
            if (mCustomShader == nullptr)
            {
                mUsingCustomShader = false;
                //warning?
            }
        }
        else
        {
            mCustomShader = mShaderManager->GetShader(_key);
            mUsingCustomShader = true;
        }

        // If now using custom shader, initialise shader store
        if (mUsingCustomShader)
        {
            mShaderStore = std::make_unique<ShaderStore>(ShaderStore::TWO_DIMENSION);
        }
    }
    else
    {
        //warning?
    }
}

void HUDObject::UseCustomShader(const std::string& _key, const std::string& _vertexPath, const std::string& _fragmentPath)
{
    if (mShaderManager != nullptr)
    {
        if (mShaderManager->GetShader(_key) == nullptr)
        {
            mCustomShader = mShaderManager->AddShader(_key, _vertexPath, _fragmentPath);
            mUsingCustomShader = true;
            if (mCustomShader == nullptr)
            {
                mUsingCustomShader = false;
                //warning?
            }
        }
        else
        {
            mCustomShader = mShaderManager->GetShader(_key);
            mUsingCustomShader = true;
        }

        // If now using custom shader, initialise shader store
        if (mUsingCustomShader)
        {
            mShaderStore = std::make_unique<ShaderStore>(ShaderStore::TWO_DIMENSION);
        }
    }
    else
    {
        //warning?
    }
}

bool HUDObject::MouseIntersect(glm::vec2 _mousePos)
{
    return (_mousePos.x >= mTopLeft.x &&
        _mousePos.x <= mTopLeft.x + mSize.x &&
        _mousePos.y >= mTopLeft.y &&
        _mousePos.y <= mTopLeft.y + mSize.y);
}

void HUDObject::SetFillColor(COLOR _fill)
{
    switch (_fill)
    {
    case RED:
        mColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        break;
    case BLUE:
        mColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        break;
    case GREEN:
        mColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        break;
    case ORANGE:
        mColor = glm::vec4(1.0f, 0.49f, 0.153f, 1.0f);
        break;
    case PURPLE:
        mColor = glm::vec4(0.635f, 0.286f, 0.643f, 1.0f);
        break;
    case YELLOW:
        mColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        break;
    case WHITE:
        mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        break;
    default:
    case BLACK:
        mColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        break;
    }
}

void HUDObject::SetFillColor(glm::ivec3 _color)
{
    mColor = glm::vec4(RGBtoUnit(_color.x), RGBtoUnit(_color.y), RGBtoUnit(_color.z), 1.0f);
}

void HUDObject::SetFillColor(glm::ivec4 _color)
{
    mColor = glm::vec4(RGBtoUnit(_color.x), RGBtoUnit(_color.y), RGBtoUnit(_color.z), RGBtoUnit(_color.w));
}

void HUDObject::SetFillColor(int _r, int _g, int _b)
{
    mColor = glm::vec4(RGBtoUnit(_r), RGBtoUnit(_g), RGBtoUnit(_b), 1.0f);
}

void HUDObject::SetFillColor(int _r, int _g, int _b, int _a)
{
    mColor = glm::vec4(RGBtoUnit(_r), RGBtoUnit(_g), RGBtoUnit(_b), RGBtoUnit(_a));
}

void HUDObject::SetImage(const std::string& _path)
{
    try
    {
        std::shared_ptr<Texture> newtex = std::make_shared<Texture>(_path);
        mTexture = newtex;
        mUsingImage = true;
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        mUsingImage = false;
    }
}

bool HUDObject::UsingImage() const
{
    return mUsingImage;
}

float HUDObject::RGBtoUnit(int _value)
{
    return std::round(((float)_value / 255) * 1000) / 1000;
}