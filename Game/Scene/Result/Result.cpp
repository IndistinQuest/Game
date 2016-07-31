#include "Result.h"
#include "ResultButton.h"
#include "ResultText.h"
#include "MonsterFadeInEffect.h"
#include "../../Button/ButtonManager.h"

using namespace scene::result;

void Result::init()
{
    // �{�^���̏�����
    std::shared_ptr<ResultButton> button;
    button = std::make_shared<OneMoreGame>(shared_from_this());
    ButtonManager::add(button);
    drawables_m.add(button, 1);
    button = std::make_shared<GoToTitle>(shared_from_this());
    ButtonManager::add(button);
    drawables_m.add(button, 2);
    // �e�L�X�g�̏�����
    drawables_m.add(std::make_shared<ResultText>(
        L"���U���g", L"MainFont", FontAssetData(50), Window::Center().moveBy(0, -250)), 3);
}

void Result::update()
{
    // �G�t�F�N�g
    if(Input::MouseL.clicked) {
        effect_m.add<MonsterFadeInEffect>();
    }
    effect_m.update();
}

void Result::draw() const
{
    drawables_m.drawAll();
}