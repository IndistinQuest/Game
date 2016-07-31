#include "RoundRectButton.h"

double const RoundRectTextButton::SCALE = 1.03;
String const RoundRectTextButton::FONT_NAME = L"ButtonFont";
RoundRectTextButton::RoundRectTextButton(int x, int y, int w, int h, double colorH, String text, std::function<void(void)> handler)
    :LambdaButton(Shape(RoundRect(x, y, w, h, 5)), handler),
    rect_m(RoundRect(x, y, w, h, 5)),
    colorH_m(colorH),
    text_m(text),
    width_m(w),
    height_m(h)
{}

void RoundRectTextButton::draw()const
{
    int const W = width_m;
    int const H = height_m;
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