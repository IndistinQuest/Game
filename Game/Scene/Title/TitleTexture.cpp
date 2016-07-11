#include "TitleTexture.h"

using namespace scene::title;

TitleTexture::TitleTexture(String fileNumber, Point center)
    :texture_m(Texture(fileNumber)),
    center_m(center)
{}


void scene::title::TitleTexture::draw() const
{
    texture_m.drawAt(center_m);
}
