#include "ResultButton.h"

using namespace scene::result;

const int ResultButton::WIDTH = 300;
const int ResultButton::HEIGHT = 80;
const String ResultButton::FONT_NAME = L"ResultFont";

ResultButton::ResultButton(const String text, const Point position, const std::shared_ptr<Result> result)
    : BasicButton(Shape(RoundRect(position, {WIDTH, HEIGHT}, 5)))
    , text_m(text)
    , rect_m(RoundRect(position, {WIDTH, HEIGHT}, 5))
    , result_m(result)
{
    if(!FontAsset::IsRegistered(FONT_NAME)) {
        FontAsset::Register(FONT_NAME, FontAssetData(20));
    }
}

void ResultButton::draw() const
{
    rect_m.draw(HSV(135, 1.0, 0.5));
    FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
}


OneMoreGame::OneMoreGame(const std::shared_ptr<Result> result)
    : ResultButton(L"One More Game", Window::Center().moveBy(-WIDTH / 2 - 250, -HEIGHT / 2 + 250), result)
{
}

void OneMoreGame::onClicked()
{
    result_m->changeScene(L"Game");
    setState(State::REMOVED);
}


GoToTitle::GoToTitle(const std::shared_ptr<Result> result)
    : ResultButton(L"Go To Title", Window::Center().moveBy(-WIDTH / 2 + 250, -HEIGHT / 2 + 250), result)
{
}

void GoToTitle::onClicked()
{
    result_m->changeScene(L"Title");
    setState(State::REMOVED);
}
