
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"Scene\GameData.h"
#include"Button/ButtonManager.h"
#include"Scene\Title\Title.h"
#include"Scene\Battle\Battle.h"
#include"Scene\Rule\Rule.h"


using Manager = SceneManager<String, GameData>;

class GameOver : public Manager::Scene{
	Font font;
public:
	GameOver() :font(50) {}
	void init()override { ButtonManager::clearAll(); }
	void update()override { if (Input::MouseL.clicked)changeScene(L"Battle"); }
	void draw()const override { font.drawCenter(L"GameOver", Window::Center()); }
};

void Main()
{
	Manager manager;

	// フェードイン・アウト時の色
	manager.setFadeColor(Palette::White);

	// シーンを設定
	
	manager.add<Battle>(L"Battle");
	manager.add<GameOver>(L"GameOver");
	manager.add<scene::title::Title>(L"Title");
    manager.add<scene::rule::Rule>(L"Rule");

    // ウィンドウを設定
    Window::SetStyle(WindowStyle::NonFrame);
    Window::Resize({ 1280, 720 });
    Window::Centering();

	while (System::Update())
	{
        ButtonManager::update();
        if (!manager.updateAndDraw())
			break;
	}
}
