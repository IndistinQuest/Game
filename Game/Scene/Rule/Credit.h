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
    // クラスの初期化時に一度だけ呼ばれる（省略可）
    void init() override;

    // 毎フレーム updateAndDraw() で呼ばれる
    void update() override;

    // 毎フレーム update() の次に呼ばれる
    void draw() const override;
};

}
}
