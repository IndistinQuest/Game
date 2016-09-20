
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"Scene\GameData.h"
#include"Button/ButtonManager.h"
#include"Scene\Title\Title.h"
#include"Scene\Battle\Battle.h"
#include"Scene\Rule\Rule.h"
#include"Scene\Rule\Rule2.h"
#include"Scene\Rule\Rule3.h"
#include"Scene\EnemyGuide\EGListType.h"
#include"Scene\EnemyGuide\EGDetailType.h"
#include"Scene\Result\Result.h"
#include"RegisterAsset.h"

using Manager = SceneManager<String, GameData>;

void Main()
{
	// 各アセットの登録
	RegisterAsset registerAsset;

	// ウィンドウを設定	
	Window::Resize({ 1280, 720 });
	Window::SetStyle(WindowStyle::NonFrame);
	Window::Centering();

	System::Update();	//これがないとTitleの背景がずれる

	// 展示の時はフルスクリーンがいいね
	//Window::SetFullscreen(true, { 1280, 720 });	

	// ロード画面を表示
	/*System::Update();
	Texture(L"/1100").draw();
	System::Update();*/
	
	// シーンマネージャーちゃん
	Manager manager;

	// フェードイン・アウト時の色
	manager.setFadeColor(Palette::White);	

	// シーンを設定
	manager.add<scene::enemyGuide::EGDetailType>(L"EGDetailType");
	manager.add<scene::enemyGuide::EGListType>(L"EGListType");
    manager.add<scene::rule::Rule>(L"Rule");
    manager.add<scene::rule::Rule2>(L"Rule2");
    manager.add<scene::rule::Rule3>(L"Rule3");
	manager.add<scene::title::Title>(L"Title");
	manager.add<scene::result::Result>(L"Result");
	manager.add<scene::battle::Battle>(L"Battle");

	manager.init(L"Title");

	SoundAsset(L"enemies_bgm").setLoopBySec(true, 19.3s, 83.4s);

	while (System::Update())
	{
        ButtonManager::update();
        if (!manager.updateAndDraw())
			break;
	}
}
