#include "Result.h"
#include "ResultButton.h"
#include "ResultText.h"
#include "MonsterFadeInEffect.h"
#include "../../Button/ButtonManager.h"

using namespace scene::result;

void Result::init()
{
    // ボタンの初期化
    std::shared_ptr<ResultButton> button;
    button = std::make_shared<OneMoreGame>(shared_from_this());
    ButtonManager::add(button);
    drawables_m.add(button, 1);
    button = std::make_shared<GoToTitle>(shared_from_this());
    ButtonManager::add(button);
    drawables_m.add(button, 2);
    // テキストの初期化
    drawables_m.add(std::make_shared<ResultText>(
        L"リザルト", L"MainFont", FontAssetData(50), Window::Center().moveBy(0, -250)), 3);
}

void Result::update()
{
    // エフェクト
    if(Input::MouseL.clicked) {
        effect_m.add<MonsterFadeInEffect>();
    }
    effect_m.update();
}

void Result::draw() const
{
    drawables_m.drawAll();
}