#pragma once

#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "ResultText.h"
#include "../GameData.h"
#include "../../Drawable/DrawableList.h"

using Scene = SceneManager<String, GameData>::Scene;

namespace scene
{
namespace result
{

class Result : public Scene
{
private:
    Stopwatch stopwatch_m;
    DrawableList drawables_m;
    Effect effect_m;
    std::shared_ptr<ResultText> enemyNum_m;
    std::shared_ptr<ResultText> score_m;
public:
    Result();
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