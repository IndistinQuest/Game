#include"TitleButton.h"
#include"Title.h"

using namespace scene::title;

String const TitleButton::FONT_NAME = L"TitleFont";

int const TitleButton::W = 300;
int const TitleButton::H = 80;
double const TitleButton::SCALE = 1.03;

TitleButton::TitleButton(double rectColor, String text, Point point, std::shared_ptr<Title> title)
    :BasicButton(Shape(RoundRect(point, { W, H }, 5))),
    rectColorH_m(rectColor),
    text_m(text),
    rect_m(RoundRect(point, { W, H }, 5)),
    title_m(title)
{
    if (!FontAsset::IsRegistered(FONT_NAME)) {
        FontAsset::Register(FONT_NAME, FontAssetData(20));
    }
}

void TitleButton::draw() const
{
    switch (getState()) {
    case State::LEFT:
        rect_m.draw(HSV(rectColorH_m, 0.5, 0.9));
        FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
        break;
    case State::MOUSE_OVER:
        RoundRect(rect_m.rect.scaled(1.03), 5).moveBy(-W*SCALE/2, -H*SCALE/2).draw(HSV(rectColorH_m, 0.8, 0.9));
        FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
        break;
    case State::PRESSED:
        RoundRect(rect_m.rect.scaled(1.03), 5).moveBy(-W*SCALE/2, -H*SCALE/2+2).draw(HSV(rectColorH_m, 0.8, 0.6));
        FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
        break;
    case State::RELEASED:
        rect_m.draw(HSV(rectColorH_m, 0.5, 0.9));
        FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
        break;
    default:
        break;
    }
}

StartGame::StartGame(std::shared_ptr<Title> title)
    :TitleButton(0, L"Start Game", Window::Center().moveBy(-W/2, -H/2+40), title)
{}

void StartGame::onClicked()
{
    title_m->changeScene(L"Game");
    setState(State::REMOVED);
}

GoToRule::GoToRule(std::shared_ptr<Title> title)
    :TitleButton(90, L"Go to Rule", Window::Center().moveBy(-W/2, -H/2+130), title)
{}

void GoToRule::onClicked()
{
    title_m->changeScene(L"Rule");
    setState(State::REMOVED);
}

DefeatedEnemies::DefeatedEnemies(std::shared_ptr<Title> title)
    :TitleButton(180, L"Enemies", Window::Center().moveBy(-W/2, -H/2+220), title)
{}

void DefeatedEnemies::onClicked()
{
    title_m->changeScene(L"DefeatedEnemies");
    setState(State::REMOVED);
}

QuitGame::QuitGame(std::shared_ptr<Title> title)
    :TitleButton(270, L"Quit Game", Window::Center().moveBy(-W/2, -H/2+310), title)
{}

void QuitGame::onClicked()
{
    setState(State::REMOVED);
    System::Exit();
}
