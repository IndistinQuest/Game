#include "Title.h"
#include "../../Drawable/DrawableTxture.h"
#include"../../Button/ButtonManager.h"
#include"../../Button/RoundRectButton.h"

using namespace scene::title;
using namespace jumpaku;

void Title::init()
{
    drawables.add(std::make_shared<DrawableTxture>(L"/200", Window::Center()), 0);

    Point const center = Window::Center();
    int const W = 300;
    int const H = 80;
    auto makeButton = [=](int deltaCenterY, String text, double colorH, std::function<void(void)> handler) {
        return std::make_shared<RoundRectTextButton>(center.x - 150, center.y-40+deltaCenterY, W, H, colorH, text, handler);
    };
    auto changeScene = [this](String sceneName) {
        (this->*&Scene::changeScene)(sceneName, 500, false);
        ButtonManager::clearAll();
    };
    
    std::shared_ptr<RoundRectTextButton> button;

    button = makeButton(40, L"Start Game", 0, [changeScene]() {
        changeScene(L"Game");
    });
    ButtonManager::add(button);
    drawables.add(button, 1);
    
    button = makeButton(130, L"Go to Rule", 90, [changeScene]() {
        changeScene(L"Rule");
    });
    ButtonManager::add(button);
    drawables.add(button, 2);
    
    button = makeButton(220, L"Enemies", 180, [changeScene]() {
        changeScene(L"DefeatedEnemies");
    });
    ButtonManager::add(button);
    drawables.add(button, 3);
    
    button = makeButton(310, L"Quit Game", 270, []() {
        System::Exit();
    });
    ButtonManager::add(button);
    drawables.add(button, 4);

}

void Title::update()
{
}

void Title::draw() const
{
    drawables.drawAll();
}
