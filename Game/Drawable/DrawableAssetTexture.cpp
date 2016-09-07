#include "DrawableAssetTexture.h"



DrawableAssetTexture::DrawableAssetTexture(String name, Vec2 center)
    :DrawableAssetTexture(name, center, 1.0)
{}

DrawableAssetTexture::DrawableAssetTexture(String name, Vec2 center, double scale)
    :name_m(name),
    center_m(center),
    scale_m(scale)
{}

void DrawableAssetTexture::draw() const
{
    TextureAsset(name_m).scale(scale_m).drawAt(center_m);
}
