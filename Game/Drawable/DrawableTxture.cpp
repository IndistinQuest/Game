#include "DrawableTxture.h"

using namespace jumpaku;

DrawableTxture::DrawableTxture(String fileNumber, Point center)
    :DrawableTxture(Texture(fileNumber), center)
{}

DrawableTxture::DrawableTxture(Texture texture, Point center)
    :texture_m(texture),
    center_m(center)
{}



void DrawableTxture::draw() const
{
    texture_m.drawAt(center_m);
}
