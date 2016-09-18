#include "Rule.h"
#include "../../Drawable/DrawableAssetTexture.h"
#include"../../Button/ButtonManager.h"
#include"../../Button/TextureAssetButton.h"

using namespace scene::rule;

void Rule::init()
{
    ButtonManager::clearAll();
    ButtonManager::update();

    drawables.add(std::make_shared<DrawableAssetTexture>(
        L"Rule", Window::Center()), 0);

    SoundAsset(L"タイトル6").play();
    auto changeScene = [this](String sceneName) {
        SoundAsset(L"タイトルボタン2").playMulti();
        SoundAsset(L"タイトル6").stop();
        (this->*&Scene::changeScene)(sceneName, 500, false);
        ButtonManager::clearAll();
    };
    
    std::shared_ptr<TextureAssetButton> button;

    button = std::make_shared<TextureAssetButton>(Vec2{ 1190, 360 }, L"right_button_resize", [changeScene]() {
        changeScene(L"Rule2");
    });
    ButtonManager::add(button);
    drawables.add(button, 1);

    button = std::make_shared<TextureAssetButton>(Vec2{ 1150, 600 }, L"title_button_resize", [changeScene]() {
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
