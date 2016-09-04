#include "Title.h"
#include "../../Drawable/DrawableAssetTexture.h"
#include"../../Button/ButtonManager.h"
#include"../../Button/TextureAssetButton.h"

using namespace scene::title;

void Title::init()
{
    ButtonManager::clearAll();
    ButtonManager::update();

    drawables.add(std::make_shared<DrawableAssetTexture>(L"title_graphicM", Window::Center()), 0);
    drawables.add(std::make_shared<DrawableAssetTexture>(L"title_logo2M", Window::Center().movedBy(0, -160)), 0);

    auto changeScene = [this](String sceneName) {
        (this->*&Scene::changeScene)(sceneName, 500, false);
        ButtonManager::clearAll();
    };
    
    std::shared_ptr<TextureAssetButton> button;
    
    button = std::make_shared<TextureAssetButton>(Vec2{ 200, 430 }, L"RuleButtonM", [changeScene]() {
        changeScene(L"Rule");
    });
    ButtonManager::add(button);
    drawables.add(button, 2);
    
    button = std::make_shared<TextureAssetButton>(Vec2{ 220, 510 }, L"EnemiesButtonM", [changeScene]() {
        changeScene(L"EGListType");
    });
    ButtonManager::add(button);
    drawables.add(button, 3);
    
    button = std::make_shared<TextureAssetButton>(Vec2{ 240, 590 }, L"CreditButtonM", [changeScene]() {
        //changeScene(L"Creddit");
    });
    ButtonManager::add(button);
    drawables.add(button, 4);

    button = std::make_shared<TextureAssetButton>(Vec2{ 260, 670 }, L"QuitButtonM", []() {
        System::Exit();
    });
    ButtonManager::add(button);
    drawables.add(button, 5);

    button = std::make_shared<TextureAssetButton>(Vec2{640, 550}, L"StartButtonL", [changeScene]() {
        changeScene(L"Battle");
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
