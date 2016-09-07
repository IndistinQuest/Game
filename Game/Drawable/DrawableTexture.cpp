#include "DrawableTexture.h"

using namespace jumpaku;

DrawableTexture::DrawableTexture(Texture texture, Vec2 center)
    :DrawableTexture(texture, center, 1.0)
{}

DrawableTexture::DrawableTexture(Texture texture, Vec2 center, double scale)
    :texture_m(texture),
    center_m(center),
    scale_m(scale)
{}

void DrawableTexture::draw() const
{
    texture_m.drawAt(center_m);
}
