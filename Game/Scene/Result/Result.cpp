#include "Result.h"
#include "ResultText.h"
#include "MonsterFadeInEffect.h"
#include "../../Button/ButtonManager.h"
#include "../../Drawable/DrawableAssetTexture.h"
#include "../../Button/TextureAssetButton.h"

using namespace scene::result;

scene::result::Result::Result()
{
}

void Result::init()
{
    auto changeScene = [this](String sceneName) {
		SoundAsset(L"Result_ButtonSE").play();
        (this->*&Scene::changeScene)(sceneName, 500, false);
        ButtonManager::clearAll();
		SoundAsset(L"Result_BGM").stop();
    };
    // �{�^���̏�����
    ButtonManager::clearAll();
    ButtonManager::update();
    std::shared_ptr<TextureAssetButton> button;
    button = std::make_shared<TextureAssetButton>(Vec2(300, 610), L"Result_RetryButton", [changeScene]() {
        changeScene(L"Battle");
    });
    ButtonManager::add(button);
    drawables_m.add(button, 2);
    button = std::make_shared<TextureAssetButton>(Vec2(980, 610), L"Result_TitleButton", [changeScene]() {
        changeScene(L"Title");
    });
    ButtonManager::add(button);
    drawables_m.add(button, 2);
    // �w�i�̐ݒ�
    drawables_m.add(std::make_shared<DrawableAssetTexture>(L"Result_Background", Window::Center()), 0);
    // �e�L�X�g�̏�����
    int numOfdefeatedEnemy = static_cast<int>(m_data->defeatedEnemyList.size());
    int remainingTime = m_data->time;
    drawables_m.add(std::make_shared<DrawableAssetTexture>(L"Result_Logo", Window::Center().moveBy(0, -230), 0.7), 3);
    drawables_m.add(std::make_shared<ResultText>(L"�|�����G: ", L"Result_Font", Window::Center().moveBy(-50, -80)), 3);
    enemyNum_m = std::make_shared<ResultText>(Format(numOfdefeatedEnemy), L"Result_Font", Window::Center().moveBy(150, -80));
    drawables_m.add(enemyNum_m, 3);
    enemyNum_m->hide();
    drawables_m.add(std::make_shared<ResultText>(L"�c�莞��: ", L"Result_Font", Window::Center().moveBy(-50, 20)), 3);
	drawables_m.add(std::make_shared<ResultText>(Format(remainingTime / 100, ".", Pad(remainingTime % 100, {2, L"0"})), L"Result_Font", Window::Center().moveBy(150, 20)), 3);
    score_m = std::make_shared<ResultText>(Format(numOfdefeatedEnemy, L" �~ 100 + ", remainingTime / 10, L" = ", numOfdefeatedEnemy * 100 + remainingTime), L"Result_Font", Window::Center().moveBy(0, 120));
    drawables_m.add(score_m, 3);
    score_m->hide();
    // �^�C�}�[�n��
    stopwatch_m.start();
	// BGM�Đ�
	SoundAsset(L"Result_BGM").play();
}

void Result::update()
{
    static int counter = 0;
    // �G�t�F�N�g
    if(counter < m_data->defeatedEnemyList.size()) {
        if(stopwatch_m.elapsed() >= 150ms) {
            effect_m.add<MonsterFadeInEffect>(TextureAsset(Format(L"Enemy", m_data->defeatedEnemyList[counter])));
            stopwatch_m.restart();
            ++counter;
        }
    }
    else {
        if(effect_m.num_effects == 0) {
            enemyNum_m->show();
            score_m->show();
            stopwatch_m.reset();
            counter = 0;
        }
    }
}

void Result::draw() const
{
    drawables_m.drawAll();
    effect_m.update();
}