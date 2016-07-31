#pragma once

#include<Siv3D.hpp>
#include"../../Button/RemovedOnClickedButton.h"
#include"../../Drawable/Drawable.h"

namespace scene {
namespace title {

class TitleButton : public RemovedOnClickedButton, public Drawable
{
protected:
    double const colorH_m;
    String const text_m;
    RoundRect const rect_m;

    static String const FONT_NAME;
public:
    static int getWidth()
    {
        return 300;
    }
    static int getHeight()
    {
        return 80;
    }
    static RoundRect getRoundRectAt(Point point)
    {
        return RoundRect(point, { getWidth(), getHeight() }, 5);
    }
    static double const SCALE;
public:
    TitleButton(double colorH, String text, Point center, std::function<void(void)> handler);
    void draw()const;
    virtual ~TitleButton() = default;
};

}
}
