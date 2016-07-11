#pragma once
#include "BasicButton.h"
#include<Siv3D.hpp>

class SimpleButton :
    public BasicButton
{
private:
    double const rectColorH_m;
    String const text_m;
    Color const textColor_m;
    Font const font_m;
    RoundRect const rect_m;
public:
    void draw()const;
    void onClicked()override;
    SimpleButton(RoundRect rect, double const rectColor, String text, Color const fontColor = Palette::Black);
    ~SimpleButton();
};

