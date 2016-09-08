
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"Scene\GameData.h"
#include"Button/ButtonManager.h"
#include"Scene\Title\Title.h"
#include"Scene\Battle\Battle.h"
#include"Scene\Rule\Rule.h"
#include"Scene\EnemyGuide\EGListType.h"
#include"Scene\EnemyGuide\EGDetailType.h"
#include"Scene\Result\Result.h"
#include"RegisterAsset.h"

using Manager = SceneManager<String, GameData>;


// GameDataの内容を確認するシーン
// あとで消す
class TestScene : public Manager::Scene {
public:
	void init() override {
		Println(L"time", m_data->time);
		for (int i : m_data->defeatedEnemyList) {
			Print(i, L" ");
		}
	};
	void update()override {
		if (Input::MouseL.clicked) {
			changeScene(L"Battle");
			ClearPrint();
		}
	}
	void draw()const override {}
};

void Main()
{
    // ウィンドウを設定
    Window::SetStyle(WindowStyle::NonFrame);
    Window::Resize({ 1280, 720 });
    Window::Centering();

	// 展示の時はフルスクリーンがいいね
	//Window::SetFullscreen(true, { 1280, 720 });

	// 各アセットの登録
	RegisterAsset registerAsset;

	Manager manager;

	// フェードイン・アウト時の色
	manager.setFadeColor(Palette::White);	

	// シーンを設定
	manager.add<scene::enemyGuide::EGDetailType>(L"EGDetailType");
	manager.add<scene::enemyGuide::EGListType>(L"EGListType");
    manager.add<scene::rule::Rule>(L"Rule");
	manager.add<scene::title::Title>(L"Title");
	manager.add<scene::result::Result>(L"Result");
	manager.add<scene::battle::Battle>(L"Battle");
	manager.add<TestScene>(L"Test");

	manager.init(L"Title");

	while (System::Update())
	{
        ButtonManager::update();
        if (!manager.updateAndDraw())
			break;
	}
}
