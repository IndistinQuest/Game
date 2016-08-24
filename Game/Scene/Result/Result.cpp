#include "Result.h"
#include "ResultButton.h"
#include "ResultText.h"
#include "MonsterFadeInEffect.h"
#include "../../Button/ButtonManager.h"

using namespace scene::result;

scene::result::Result::Result()
{
}

void Result::init()
{
    ButtonManager::clearAll();
    ButtonManager::update();
    // �{�^���̏�����
    std::shared_ptr<ResultButton> button;
    button = std::make_shared<OneMoreGame>(shared_from_this());
    ButtonManager::add(button);
    drawables_m.add(button, 1);
    button = std::make_shared<GoToTitle>(shared_from_this());
    ButtonManager::add(button);
    drawables_m.add(button, 1);
    // �e�L�X�g�̏�����
    drawables_m.add(std::make_shared<ResultText>(
        L"���U���g", L"MainFont", FontAssetData(50), Window::Center().moveBy(0, -250)), 3);
    drawables_m.add(std::make_shared<ResultText>(
        L"�|�����G: ", L"SubFont", FontAssetData(30), Window::Center().moveBy(-100, -100)), 3);
    enemyNum_m = std::make_shared<ResultText>(
        Format(12), L"SubFont", FontAssetData(30), Window::Center().moveBy(100, -100));
    drawables_m.add(enemyNum_m, 3);
    enemyNum_m->hide();
    score_m = std::make_shared<ResultText>(
        Format(12, L" + ", 1234, L" = ", 12 + 1234), L"SubFont", FontAssetData(30), Window::Center().moveBy(0, 100));
    drawables_m.add(score_m, 3);
    score_m->hide();
    drawables_m.add(std::make_shared<ResultText>(
        L"�c�莞��: ", L"SubFont", FontAssetData(30), Window::Center().moveBy(-100, 0)), 3);
    drawables_m.add(std::make_shared<ResultText>(
        Format(1234), L"SubFont", FontAssetData(30), Window::Center().moveBy(100, 0)), 3);
    // �^�C�}�[�n��
    stopwatch_m.start();
}

void Result::update()
{
    static int counter = 0;
    // �G�t�F�N�g
    if(counter < 12) {
        if(stopwatch_m.elapsed() >= 100ms) {
            effect_m.add<MonsterFadeInEffect>();
            stopwatch_m.reset();
            stopwatch_m.start();
            ++counter;
        }
    }
    else {
        if(effect_m.num_effects == 0) {
            enemyNum_m->show();
            score_m->show();
        }
    }
    effect_m.update();
}

void Result::draw() const
{
    drawables_m.drawAll();
}