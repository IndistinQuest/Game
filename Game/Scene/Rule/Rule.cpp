#include "Rule.h"
#include "../../Drawable/DrawableTxture.h"
#include"../../Button/ButtonManager.h"
#include"../../Button/TextureButton.h"

using namespace scene::rule;
using namespace jumpaku;

void Rule::init()
{
    ButtonManager::clearAll();
    ButtonManager::update();

    drawables.add(std::make_shared<DrawableTxture>(L"/200", Window::Center()), 0);

    auto changeScene = [this](String sceneName) {
        (this->*&Scene::changeScene)(sceneName, 500, false);
        ButtonManager::clearAll();
    };
    
    std::shared_ptr<TextureButton> button = std::make_shared<TextureButton>(Vec2{ 1000, 600 }, L"/208", [changeScene]() {
        changeScene(L"Title");
    });
    ButtonManager::add(button);
    drawables.add(button, 2);
}

void Rule::update()
{
}

void Rule::draw() const
{
    drawables.drawAll();
}
