#include "Title.h"
#include "../../Drawable/DrawableTxture.h"
#include"../../Button/ButtonManager.h"
#include"../../Button/TextureButton.h"

using namespace scene::title;
using namespace jumpaku;

void Title::init()
{
    drawables.add(std::make_shared<DrawableTxture>(L"/200", Window::Center()), 0);
    drawables.add(std::make_shared<DrawableTxture>(L"/201", Window::Center().movedBy(0, -160)), 0);

    auto changeScene = [this](String sceneName) {
        (this->*&Scene::changeScene)(sceneName, 500, false);
        ButtonManager::clearAll();
    };
    
    std::shared_ptr<TextureButton> button;
    
    button = std::make_shared<TextureButton>(Vec2{ 200, 430 }, L"/203", [changeScene]() {
        changeScene(L"Rule");
    });
    ButtonManager::add(button);
    drawables.add(button, 2);
    
    button = std::make_shared<TextureButton>(Vec2{ 220, 510 }, L"/204", [changeScene]() {
        changeScene(L"DefeatedEnemies");
    });
    ButtonManager::add(button);
    drawables.add(button, 3);
    
    button = std::make_shared<TextureButton>(Vec2{ 240, 590 }, L"/205", [changeScene]() {
        changeScene(L"Creddit");
    });
    ButtonManager::add(button);
    drawables.add(button, 4);

    button = std::make_shared<TextureButton>(Vec2{ 260, 670 }, L"/206", []() {
        System::Exit();
    });
    ButtonManager::add(button);
    drawables.add(button, 5);

    button = std::make_shared<TextureButton>(Vec2{640, 550}, L"/207", [changeScene]() {
        changeScene(L"Game");
    });
    ButtonManager::add(button);
    drawables.add(button, 1);

}

void Title::update()
{
}

void Title::draw() const
{
    drawables.drawAll();
}
