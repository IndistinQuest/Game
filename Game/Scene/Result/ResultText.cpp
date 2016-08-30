#include "ResultText.h"

using namespace scene::result;

ResultText::ResultText(const String text, const String fontName, const FontAssetData fontData, const Point position)
    : text_m(text)
    , fontName_m(fontName)
    , position_m(position)
{
    if(!FontAsset::IsRegistered(fontName)) {
        FontAsset::Register(fontName, fontData);
    }
}

void ResultText::draw() const
{
    FontAsset(fontName_m).drawCenter(text_m, position_m);
}
