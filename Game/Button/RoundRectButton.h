#pragma once

#include"LambdaButton.h"
#include"../Drawable/Drawable.h"

class RoundRectTextButton :
    public LambdaButton,
    public Drawable
{
private:
    RoundRect rect_m;
    double colorH_m;
    String text_m;
    int width_m;
    int height_m;
    static double const SCALE;

public:
    static String const FONT_NAME;
    RoundRectTextButton(int x, int y, int w, int h, double colorH, String text, std::function<void(void)> handler);
    virtual ~RoundRectTextButton() = default;
    void draw()const override;
};

