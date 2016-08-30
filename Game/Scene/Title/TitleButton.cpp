#include"TitleButton.h"
#include"Title.h"

using namespace scene::title;

String const TitleButton::FONT_NAME = L"TitleFont";

double const TitleButton::SCALE = 1.03;

TitleButton::TitleButton(double color, String text, Point point, std::function<void(void)> handler)
    :RemovedOnClickedButton(Shape(getRoundRectAt(point)), handler),
    colorH_m(color),
    text_m(text),
    rect_m(getRoundRectAt(point))
{
    if (!FontAsset::IsRegistered(FONT_NAME)) {
        FontAsset::Register(FONT_NAME, FontAssetData(20));
    }
}

void TitleButton::draw() const
{
    int const W = getWidth();
    int const H = getHeight();
    switch (getState()) {
    case State::LEFT:
        rect_m.draw(HSV(colorH_m, 0.5, 0.9));
        FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
        break;
    case State::MOUSE_OVER:
        RoundRect(rect_m.rect.scaled(1.03), 5).moveBy(-W*SCALE/2, -H*SCALE/2).draw(HSV(colorH_m, 0.8, 0.9));
        FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
        break;
    case State::PRESSED:
        RoundRect(rect_m.rect.scaled(1.03), 5).moveBy(-W*SCALE/2, -H*SCALE/2+2).draw(HSV(colorH_m, 0.8, 0.6));
        FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
        break;
    case State::RELEASED:
        rect_m.draw(HSV(colorH_m, 0.5, 0.9));
        FontAsset(FONT_NAME).drawCenter(text_m, rect_m.center);
        break;
    default:
        break;
    }
}