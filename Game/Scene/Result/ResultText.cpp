#include "ResultText.h"

using namespace scene::result;

ResultText::ResultText(const String text, const String fontName, const Point position)
    : text_m(text)
    , fontName_m(fontName)
    , position_m(position)
{
    assert(FontAsset::IsRegistered(fontName));
}

void ResultText::draw() const
{
    FontAsset(fontName_m).drawCenter(text_m, position_m);
}
