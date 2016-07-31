#pragma once

#include<Siv3D.hpp>
#include"Drawable.h"

namespace jumpaku {

class DrawableTxture : public Drawable
{
    Texture texture_m;
    Point center_m;
public:
    void draw()const override;
    DrawableTxture(String fileNumber, Point center);
    ~DrawableTxture() = default;
};

}
