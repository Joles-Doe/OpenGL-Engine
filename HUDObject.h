#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SharedStructs&Enums.h"

#include "EventManager.h"
#include "TimeManager.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Model.h"
#include "Texture.h"

class HUDObject
{
public:
    HUDObject(const glm::vec2& _topLeft, const float& _width, const float& _height);

    /// <summary>
    /// Start function - called once by the Window when the GameObject gets initialized. Use this as your constructor to initialize all of your variables.
    /// </summary>
    virtual void Start();

    /// <summary>
    /// Update function - called once a frame by the Window.
    /// </summary>
    virtual void Update();

    /// <summary>
    /// Draw function - called by the Window to draw the Object.
    /// </summary>
    void Draw(std::shared_ptr<ShaderProgram> _shader);

    void SetFillColor(COLOR _fill);

    void SetImage(const std::string& _path);
private:
    std::shared_ptr<Model> mModel;
    std::shared_ptr<Texture> mTexture;

    GLuint mVaoID;
    GLuint mVboID;
    GLuint mEboID;
    bool mDirty;

    glm::vec2 mTopLeft;
    glm::vec2 mSize;
};