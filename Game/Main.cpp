﻿
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"Scene\GameData.h"
#include"Button/ButtonManager.h"
#include"Scene\Title\Title.h"
#include"Scene\Battle\Battle.h"
#include"Scene\Rule\Rule.h"
#include"Scene\EnemyGuide\EGListType.h"
#include"Scene\EnemyGuide\EGDetailType.h"

using Manager = SceneManager<String, GameData>;

// ↓後で消す
namespace scene {
	namespace debug {
		class GameOver : public SceneManager<String, GameData>::Scene {
			Font font;
		public:
			GameOver() :font(50) {}
			void init()override { ButtonManager::clearAll(); }
			void update()override { if (Input::MouseL.clicked)changeScene(L"Battle"); }
			void draw()const override {
				ClearPrint();
				for (int v : m_data->defeatedEnemyList) {
					Println(Format(v));
				}
				font.drawCenter(L"GameOver", Window::Center());
			}
		};
	};
};

void Main()
{
    // ウィンドウを設定
    Window::SetStyle(WindowStyle::NonFrame);
    Window::Resize({ 1280, 720 });
    Window::Centering();

	Manager manager;

	// フェードイン・アウト時の色
	manager.setFadeColor(Palette::White);

	// シーンを設定
	manager.add<scene::enemyGuide::EGDetailType>(L"EGDetailType");
	manager.add<scene::enemyGuide::EGListType>(L"EGListType");
    manager.add<scene::rule::Rule>(L"Rule");
	manager.add<scene::title::Title>(L"Title");
	

	manager.init(L"Battle");

	while (System::Update())
	{
        ButtonManager::update();
        if (!manager.updateAndDraw())
			break;
	}
}
