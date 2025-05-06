#include "HUDObject.h"

HUDObject::HUDObject(const glm::vec2& _topLeft, const float& _width, const float& _height) : mVaoID(0), mVboID(0), mEboID(0)
{
    mTopLeft = _topLeft;
    mSize = glm::vec2(_width, _height);

    mDirty = true;
}

void HUDObject::Start()
{
}

void HUDObject::Update()
{
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

    if (mTexture)
    {
        glBindTexture(GL_TEXTURE_2D, mTexture->ID());
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

void HUDObject::SetFillColor(COLOR _fill)
{
    switch (_fill)
    {
    case RED:
        mTexture = std::make_shared<Texture>("./data/models/primitives/colors/red.png");
        break;
    case BLUE:
        mTexture = std::make_shared<Texture>("./data/models/primitives/colors/blue.png");
        break;
    case GREEN:
        mTexture = std::make_shared<Texture>("./data/models/primitives/colors/green.png");
        break;
    case ORANGE:
        mTexture = std::make_shared<Texture>("./data/models/primitives/colors/orange.png");
        break;
    case PURPLE:
        mTexture = std::make_shared<Texture>("./data/models/primitives/colors/purple.png");
        break;
    case YELLOW:
        mTexture = std::make_shared<Texture>("./data/models/primitives/colors/yellow.png");
        break;
    case WHITE:
        mTexture = std::make_shared<Texture>("./data/models/primitives/colors/white.png");
        break;
    default:
    case BLACK:
        mTexture = std::make_shared<Texture>("./data/models/primitives/colors/black.png");
        break;
    }
}

void HUDObject::SetImage(const std::string& _path)
{
    try
    {
        std::shared_ptr<Texture> newtex = std::make_shared<Texture>(_path);
        mTexture = newtex;
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what();
    }
}