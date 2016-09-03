#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<memory>
#include<map>
#include"..\GameData.h"
#include"..\..\Button\ButtonInterface.h"
#include"..\..\Drawable\DrawableList.h"
#include"..\..\TextView\TextView.h"
#include"..\..\Data\EnemyData.h"
#include"..\..\Data\DataManager.h"


namespace scene{
namespace battle{

class BattleSceneObject;
class BattleSceneButton;
class PictureObject;
class CutIn;
enum class BattleState { Start, EnemyEntry, Answer, CanNotAnswer, Incorect, Corect, ExitEnemy, TimeOver, GameOver,BackToTitle, GoToResult, CheckGameClear };

class RoundCounter;
class MessageWindow;
class Timer;


class AnswerButtons;
class EnemyManager;


class Battle : public SceneManager<String, GameData>::Scene {
public:
	Battle();
	~Battle();
	void init()override;
	void update()override;
	void draw()const override;

private:
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer);
	void Battle::nextScene(String sceneName);
private:
	// objects
	std::vector<std::shared_ptr<BattleSceneObject>> objects;
	DrawableList drawList_m;						

	std::shared_ptr<EnemyManager> enemyManger_m;	// エネミーマネージャ

	std::shared_ptr<AnswerButtons> answerButtons;	// 回答のボタン郡

	std::shared_ptr<RoundCounter> roundCounter_m;	// 戦闘数	
	std::shared_ptr<MessageWindow> message_m;		// メッセージ	
	std::shared_ptr<Timer> timer_m;					// タイマー
};

};

};

