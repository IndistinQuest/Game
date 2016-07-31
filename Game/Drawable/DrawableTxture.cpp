#include "DrawableTxture.h"

using namespace jumpaku;

DrawableTxture::DrawableTxture(String fileNumber, Point center)
    :texture_m(Texture(fileNumber)),
    center_m(center)
{}


void DrawableTxture::draw() const
{
    texture_m.drawAt(center_m);
}
