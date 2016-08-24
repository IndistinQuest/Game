#pragma once

#include <Siv3D.hpp>

namespace scene
{
namespace result
{
class MonsterFadeInEffect : public IEffect
{
private:
    static const Vec2 END_POS;
private:
    const Vec2 beginPos_m;
    const Color color_m;
    Rect texture_m;
    Vec2 position_m;
    double alpha_m;
public:
    MonsterFadeInEffect();
    ~MonsterFadeInEffect() = default;
public:
    bool update(double t) override;
};
}
}
