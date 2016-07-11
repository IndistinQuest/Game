#include "Title.h"
#include "TitleTexture.h"
#include"../../Button/ButtonManager.h"
#include"TitleButton.h"

using namespace scene::title;

void Title::init()
{
    drawables.add(std::make_shared<TitleTexture>(L"/200", Window::Center()), 0);

    std::shared_ptr<TitleButton> button;

    button = std::make_shared<StartGame>(shared_from_this());
    ButtonManager::add(button);
    drawables.add(button, 1);
    
    button = std::make_shared<GoToRule>(shared_from_this());
    ButtonManager::add(button);
    drawables.add(button, 2);
    
    button = std::make_shared<DefeatedEnemies>(shared_from_this());
    ButtonManager::add(button);
    drawables.add(button, 3);
    
    button = std::make_shared<QuitGame>(shared_from_this());
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
