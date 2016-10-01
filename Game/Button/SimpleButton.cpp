#include "SimpleButton.h"



SimpleButton::SimpleButton(RoundRect rect, double const rectColorH, String text, Color const textColor)
    :BasicButton(Shape(rect)), rectColorH_m(rectColorH), rect_m(rect), font_m(24), text_m(text), textColor_m(textColor)
{}


void SimpleButton::draw() const
{
    switch (getState()) {
    case State::LEFT:
        rect_m.draw(HSV(rectColorH_m, 1.0, 0.9));
        font_m(text_m).drawCenter(rect_m.center, textColor_m);
        break;
    case State::MOUSE_OVER:
        rect_m.draw(HSV(rectColorH_m, 1.0, 0.9)).drawFrame(-4, -6, HSV(rectColorH_m, 1.0, 0.9));
        font_m(text_m).drawCenter(rect_m.center, textColor_m);
        break;
    case State::PRESSED:
        rect_m.draw(HSV(rectColorH_m, 1.0, 0.5));
        font_m(text_m).drawCenter(rect_m.center, textColor_m);
        break;
    case State::RELEASED:
        rect_m.draw(HSV(rectColorH_m, 1.0, 0.9));
        font_m(text_m).drawCenter(rect_m.center, textColor_m);
        break;
    default:
        break;
    }
}

void SimpleButton::onClicked()
{
    setState(State::REMOVED);
}

SimpleButton::~SimpleButton()
{}
