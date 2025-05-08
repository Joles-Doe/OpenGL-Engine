#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SharedStructs&Enums.h"

#include "EventManager.h"
#include "TimeManager.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "ShaderStore.h"
#include "Transform.h"
#include "Model.h"
#include "Texture.h"

class HUDObject
{
public:
    HUDObject(const glm::vec2& _topLeft, const float& _width, const float& _height);
    ~HUDObject();

    /// <summary>
    /// Start function - called once by the Window when the GameObject gets initialized. Use this as your constructor to initialize all of your variables.
    /// </summary>
    virtual void Start();

    /// <summary>
    /// Update function - called once a frame by the Window.
    /// </summary>
    virtual void Update();

    virtual void OnHover();

    virtual void OnClick();

    /// <summary>
    /// Draw function - called by the Window to draw the Model. Uses a custom shader.
    /// </summary>
    void Draw(const glm::mat4& _projectionMatrix);

    /// <summary>
    /// Draw function - called by the Window to draw the Object.
    /// </summary>
    void Draw(std::shared_ptr<ShaderProgram> _shader);

    /// <summary>
    /// Returns true or false dependent on if the GameObject is dead and will be culled.
    /// </summary>
    /// <returns> Returns true or false dependent on if the GameObject needs culling </returns>
    bool IsKill() const noexcept { return mKILL; }
    
    glm::vec2 GetSize() const noexcept { return mSize; }
    glm::vec2 GetTopLeft() const noexcept { return mTopLeft; }

    bool MouseIntersect(glm::vec2 _mousePos);

    void SetFillColor(COLOR _fill);
    void SetFillColor(glm::ivec3 _color);
    void SetFillColor(glm::ivec4 _color);
    void SetFillColor(int _r, int _g, int _b);
    void SetFillColor(int _r, int _g, int _b, int _a);

    void SetImage(const std::string& _path);

    bool UsingImage() const;

    /// <summary>
    /// Attaches the Event Manager component to the GameObject.
    /// </summary>
    /// <param name="_manager"> Event Manager </param>
    void AttachEventManager(std::shared_ptr<EventManager> _manager) { mEventManager = _manager; }

    /// <summary>
    /// Attaches the Time Manager component to the GameObject.
    /// </summary>
    /// <param name="_manager"> Time Manager </param>
    void AttachTimeManager(std::shared_ptr<TimeManager> _manager) { mTimeManager = _manager; }

    /// <summary>
    /// Attaches the Shader Manager component to the GameObject.
    /// </summary>
    /// <param name="_manager"> Shader Manager </param>
    void AttachShaderManager(std::shared_ptr<ShaderManager> _manager) { mShaderManager = _manager; }

    void UseCustomShader(const std::string& _key, const std::string& _generalPath);

    void UseCustomShader(const std::string& _key, const std::string& _vertexPath, const std::string& _fragmentPath);

    bool HasCustomShader() const noexcept { return mUsingCustomShader; }
protected:
    std::shared_ptr<EventManager> mEventManager;
    std::shared_ptr<TimeManager> mTimeManager;
    std::shared_ptr<ShaderManager> mShaderManager;
    std::shared_ptr<ShaderProgram> mCustomShader;
    std::unique_ptr<ShaderStore> mShaderStore;

    std::shared_ptr<Model> mModel;
    std::shared_ptr<Texture> mTexture;

    bool mKILL;

    GLuint mVaoID;
    GLuint mVboID;
    GLuint mEboID;
    bool mDirty;

    glm::vec2 mTopLeft;
    glm::vec2 mSize;

    bool mUsingImage;
    glm::vec4 mColor;
    
    float RGBtoUnit(int _value);

    bool mUsingCustomShader;
};