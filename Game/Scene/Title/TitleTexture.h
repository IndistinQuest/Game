#pragma once

#include<Siv3D.hpp>
#include"../../Drawable/Drawable.h"

namespace scene {
namespace title {

class TitleTexture : public Drawable
{
    Texture texture_m;
    Point center_m;
public:
    void draw()const override;
    TitleTexture(String fileNumber, Point center);
    ~TitleTexture() = default;
};

}
}

