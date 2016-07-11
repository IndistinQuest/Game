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
    // クラスの初期化時に一度だけ呼ばれる（省略可）
    void init() override;

    // 毎フレーム updateAndDraw() で呼ばれる
    void update() override;

    // 毎フレーム update() の次に呼ばれる
    void draw() const override;

    void changeScene(String sceneId)
    {
        Scene::changeScene(sceneId);
    }
};

}
}
