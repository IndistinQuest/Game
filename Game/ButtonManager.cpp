#include "ButtonManager.h"
#include"ButtonInterface.h"
#include<algorithm>

ButtonManager::ButtonManager()
{}


ButtonManager::~ButtonManager()
{}

std::list<std::shared_ptr<ButtonInterface>> ButtonManager::buttons_m;



void ButtonManager::add(std::shared_ptr<ButtonInterface> const &button)
{
    buttons_m.emplace_back(button);
}


void ButtonManager::update()
{
    auto rmend = std::remove_if(buttons_m.begin(), buttons_m.end(), [](std::shared_ptr<ButtonInterface> const &button) {
        return button->getState() == ButtonInterface::State::REMOVED;
    });
    buttons_m.erase(rmend, buttons_m.end());
    std::for_each(buttons_m.begin(), buttons_m.end(), [](std::shared_ptr<ButtonInterface> const &button) {
        if (button->isEnabled()) {
            button->transition();
            if (button->getState() == ButtonInterface::State::RELEASED) {
                button->onClicked();
            }
        }
    });
}
