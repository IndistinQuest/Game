#include "MonsterFadeInEffect.h"

using namespace scene::result;

const Vec2 MonsterFadeInEffect::END_POS = {790, 280};

MonsterFadeInEffect::MonsterFadeInEffect(Texture enemy)
    : beginPos_m(RandomVec2(100) + END_POS)
    , texture_m(enemy)
    , position_m(beginPos_m)
    , alpha_m(1.0)
    , color_m(RandomColorH(1.0, 0.75))
{
    texture_m.resize({80, 80});
}

bool MonsterFadeInEffect::update(double t)
{
    if(1.0 < t)  return false;
    position_m = Easing::EaseOut<Vec2>(beginPos_m, END_POS, Easing::Expo, t);
    alpha_m = -4 * Pow(t - 0.5, 2) + 1;
    texture_m.scale(0.2).drawAt(position_m.asPoint(), AlphaF(alpha_m));
    return true;
}
