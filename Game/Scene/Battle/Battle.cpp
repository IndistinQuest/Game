#include"Battle.h"
#include"../../Button/ButtonManager.h"
#include"StateManager.h"
#include"SoundPlayer.h"
#include"RoundCounter.h"
#include"MessageWindow.h"
#include"Timer.h"
#include"TitleButton.h"
#include"NextButton.h"
#include"AnswerButtons.h"
#include"EnemyManager.h"
#include"CutIn.h"
#include"PictureObject.h"

using namespace std;
using namespace scene::battle;

Battle::Battle(){};

Battle::~Battle(){};

void Battle::init(){

	//各種定数
	const int tx = 5;
	const int ty = 5;	
	const int windowPosY = 80;
	const int width = 420;			//ボタンの
	const int height = 60;			//ぼたんの

	// 背景色変更
	Graphics::SetBackground(Palette::Lightslategray);

	// ボタンマネージャのクリア
	ButtonManager::clearAll();
	ButtonManager::update();

	// GameData 初期化
	m_data->resetEnemyList();
	m_data->time = 0;

	// 各種初期化
	AnswerManager::init();
	StateManager::init();

	// BGM再生
	addObject(std::make_shared<SoundPlayer>());	

	// 戦闘数
	auto roundCounter = make_shared<RoundCounter>(Point(100, windowPosY ), L"miniMesWindow");
	addObject(roundCounter, 10,1);

	// タイマー
	auto timer = make_shared<Timer>(Point(Window::Width() - 100, windowPosY), L"miniMesWindow");
	timer->setGameData(m_data);
	addObject(timer, 10);

	// 背景画像
	auto backPic = make_shared<PictureObject>(L"battleBack5", 1.0, Window::Center());
	addObject(backPic, 1);

	// カットイン
	auto cutIn = make_shared<CutIn>();
	addObject(cutIn, 15);

	// エネミー画像
	auto enemyPic = make_shared<PictureObject>(L"title_logo2M",1.0, Point(Window::Width() / 2, 330));
	addObject(enemyPic, 5);

	// エネミーマネージャ
	auto enemyManger = make_shared<EnemyManager>();
	enemyManger->setRoundCounter(roundCounter);
	enemyManger->setGameData(m_data);
	enemyManger->setObjects(enemyPic, backPic, cutIn);
	addObject(enemyManger, 0, 2);

	// メッセージ
	auto message = make_shared<MessageWindow>(Point(Window::Width() / 2, windowPosY), L"mesWindow");
	message->setEnemyManager(enemyManger);
	addObject(message, 10,3);

	// 回答のボタン
	auto answerButtons = make_shared<AnswerButtons>();
	answerButtons->setEnemyManager(enemyManger);
	addObject(answerButtons, 10,3);
	
	// タイトルボタン
	auto titleButton = make_shared<TitleButton>(TitleButton({ Window::Width() / 2 - width / 2 + (width + tx), windowPosY*2 + ty }, Size(width, height), L"battleButton"));
	addObject(titleButton, 12);
	ButtonManager::add(titleButton);

	// 次へボタン
	auto nextButton = make_shared<NextButton>(Point(Window::Width() / 2 - width / 2, Window::Height() - height * 4 - tx * 4), Size(width, height), L"battleButton");
	addObject(nextButton, 12);
	ButtonManager::add(nextButton);	
};

void Battle::update(){
	
	for_each(objects.begin(), objects.end(), [](auto obj) { obj.second->update(); });

	StateManager::update();	

	switch (StateManager::getState())
	{
	case BattleState::GoToResult:
		changeScene(L"Result");
		break;

	case BattleState::BackToTitle:
		changeScene(L"Title");
		break;

	default:
		break;
	}
};

void Battle::draw()const{
	drawList_m.drawAll();
};

void Battle::addObject(std::shared_ptr<BattleSceneObject> obj) {
	objects.insert(std::make_pair(4, obj));
}

void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer,const int order) {
	objects.insert(std::make_pair(order,obj));
	drawList_m.add(obj, layer);
}
