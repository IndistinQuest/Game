#include"StateManager.h"
#include"AnswerManager.h"
using namespace scene::battle;

void StateManager::init() {
	isGoTitle = false;
	isGameClear = false;
	isTimeOver = false;
	isImprove = false;
	curentState_m = BattleState::Start;
}

void StateManager::update() {
	switch (curentState_m)
	{
	case BattleState::Start:
		if (AnswerManager::checkAnswer() == Answers::correct) {
			StateManager::goToNext();
		}
		if (isImprove) {
			curentState_m = BattleState::EnemyEntry;
		}
		break;

		// 敵が登場するときの処理
	case BattleState::EnemyEntry:
		curentState_m = BattleState::Answer;
		break;

		// 回答
	case BattleState::Answer:
	{
		auto ans = AnswerManager::checkAnswer();
		// 正解時
		if (ans == Answers::correct) {
			curentState_m = BattleState::Corect;
		}
		// 不正解時
		else if (ans == Answers::incorrect) {
			curentState_m = BattleState::Incorect;
		}
	}
	break;

	// 不正解を選んで選択できなくなっている間の処理
	case BattleState::CanNotAnswer:
		if (isImprove) {
			curentState_m = BattleState::Answer;
		}
		AnswerManager::init();
		break;

		// 不正解を選んだ瞬間の処理
	case BattleState::Incorect:
		curentState_m = BattleState::CanNotAnswer;
		break;

		//正解を選んだ瞬間の処理
	case BattleState::Corect:
		curentState_m = BattleState::ExitEnemy;
		break;

		// 正解して敵が消えていく間の処理
	case BattleState::ExitEnemy:
		if (StateManager::isImprove) {
			curentState_m = BattleState::CheckGameClear;
		}
		break;

	case BattleState::CheckGameClear:
		curentState_m = BattleState::EnemyEntry;
		break;

		// 時間切れになった瞬間の処理
	case BattleState::TimeOver:
		curentState_m = BattleState::GameOver;
		break;

		// ゲームオーバーになった時の処理
	case BattleState::GameOver:
		if (isImprove) {
			curentState_m = BattleState::GoToResult;
		}
		break;

	default:
		break;
	}

	if (isTimeOver && curentState_m != BattleState::GameOver && curentState_m != BattleState::GoToResult) { curentState_m = BattleState::TimeOver; }
	if (isGoTitle) { curentState_m = BattleState::BackToTitle; }
	if (isGameClear) { curentState_m = BattleState::GoToResult; }

	isImprove = false;
}

BattleState StateManager::getState() {
	return curentState_m;
}
void StateManager::setNextState(BattleState next) {
	curentState_m = next;
}
void StateManager::setBackToTitle() {
	isGoTitle = true;
}
void StateManager::setTimeOver() {
	isTimeOver = true;
}
void StateManager::setGameClear() {
	isGameClear = true;
}
void StateManager::goToNext() {
	isImprove = true;
}
		
bool StateManager::isGoTitle = false;
bool StateManager::isGameClear = false;
bool StateManager::isTimeOver = false;
bool StateManager::isImprove = false;
BattleState StateManager::curentState_m = BattleState::Start;
