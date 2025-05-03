#include "Canvas.h"

bool Canvas::IsKill()
{
    return false;
}

void Canvas::Draw(std::shared_ptr<ShaderProgram> _shader)
{
    for (int i = 0; i < mObjects.size(); i++)
    {
        mObjects[i]->Draw(_shader);
    }
}
