#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"../../Drawable/DrawableList.h"

class GameData;

using Scene = SceneManager<String, GameData>::Scene;

namespace scene {
namespace rule {

class Credit : public Scene
{
private:
    DrawableList drawables;
public:
    // �N���X�̏��������Ɉ�x�����Ă΂��i�ȗ��j
    void init() override;

    // ���t���[�� updateAndDraw() �ŌĂ΂��
    void update() override;

    // ���t���[�� update() �̎��ɌĂ΂��
    void draw() const override;
};

}
}
