#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"../../Drawable/DrawableList.h"

class GameData;

using Scene = SceneManager<String, GameData>::Scene;

namespace scene {
namespace title {

class Title : public Scene, public std::enable_shared_from_this<Title>
{
private:
    DrawableList drawables;
    Texture back;
public:
    // �N���X�̏��������Ɉ�x�����Ă΂��i�ȗ��j
    void init() override;

    // ���t���[�� updateAndDraw() �ŌĂ΂��
    void update() override;

    // ���t���[�� update() �̎��ɌĂ΂��
    void draw() const override;

    void changeScene(String sceneId)
    {
        Scene::changeScene(sceneId);
    }
};

}
}
