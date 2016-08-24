#pragma once

#include "../../Drawable/Drawable.h"

namespace scene
{
namespace result
{

class ResultText : public Drawable
{
private:
    const String text_m;
    const String fontName_m;
    const Point position_m;
public:
    ResultText(const String text, const String fontName, const FontAssetData fontData, const Point position);
    ~ResultText() = default;
public:
    void draw() const override;
};

}
}
