#pragma once
#include <Luma3D.h>

using namespace Core;
using namespace Graphics;

class PlayScene : public Scene
{
public:
    PlayScene() = default;

    void OnCreate() override;
    void OnShutdown() override;
    void OnUpdate() override;
    void OnRender() override;

private:
    // std::shared_ptr<Entity> m_camera;
    // std::shared_ptr<Entity> m_directionalLight;
};
