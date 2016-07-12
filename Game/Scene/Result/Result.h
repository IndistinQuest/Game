#pragma once

#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "../GameData.h"
#include "../../Drawable/DrawableList.h"

using Scene = SceneManager<String, GameData>::Scene;

namespace scene
{
namespace result
{

class Result : public Scene, public std::enable_shared_from_this<Result>
{
private:
    DrawableList drawables_m;
public:
    void init() override;
    void update() override;
    void draw() const override;
    void changeScene(String nextScene)
    {
        Scene::changeScene(nextScene);
    }
};

}
}