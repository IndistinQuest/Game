#include "MonsterFadeInEffect.h"

using namespace scene::result;

//const Vec2 MonsterFadeInEffect::BEGIN_POS = {100, 100};
const Vec2 MonsterFadeInEffect::END_POS = {100, 150};

MonsterFadeInEffect::MonsterFadeInEffect()
    : beginPos_m(RandomVec2(100) + END_POS)
    , texture_m(beginPos_m.asPoint(), {50, 50})
    , position_m(beginPos_m)
    , alpha_m(1.0)
    , color_m(RandomColorH(1.0, 0.75))
{
}

bool MonsterFadeInEffect::update(double t)
{
    if(1.0 < t)  return false;
    position_m = Easing::EaseOut<Vec2>(beginPos_m, END_POS, Easing::Expo, t);
    alpha_m = -4 * Pow(t - 0.5, 2) + 1;
    texture_m.movedBy((position_m - beginPos_m).asPoint()).draw(ColorF(color_m, alpha_m));
    return true;
}
