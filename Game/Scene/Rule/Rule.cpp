#include "Rule.h"
#include "../../Drawable/DrawableTxture.h"
#include"../../Button/ButtonManager.h"
#include"../../Button/RoundRectButton.h"

using namespace scene::rule;
using namespace jumpaku;

void Rule::init()
{
    drawables.add(std::make_shared<DrawableTxture>(L"/200", Window::Center()), 0);

    Point const center = Window::Center();
    int const W = 300;
    int const H = 80;
    auto makeButton = [=](int deltaCenterY, String text, double colorH, std::function<void(void)> handler) {
        return std::make_shared<RoundRectTextButton>(center.x - 150, center.y-40+deltaCenterY, W, H, colorH, text, handler);
    };
    auto changeScene = [this](String sceneName) {
        (this->*&Scene::changeScene)(sceneName, 1000, false);
        ButtonManager::clearAll();
    };
    std::shared_ptr<RoundRectTextButton> button;

    button = makeButton(40, L"Return to Title", 270, [this]() {
        (this->*&Scene::changeScene)(L"Title", 500, false);
        ButtonManager::clearAll();
    });
    ButtonManager::add(button);
    drawables.add(button, 4);
}

void Rule::update()
{
}

void Rule::draw() const
{
    drawables.drawAll();
}
