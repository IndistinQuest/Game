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

		// “G‚ª“oê‚·‚é‚Æ‚«‚Ìˆ—
	case BattleState::EnemyEntry:
		curentState_m = BattleState::Answer;
		break;

		// ‰ñ“š
	case BattleState::Answer:
	{
		auto ans = AnswerManager::checkAnswer();
		// ³‰ğ
		if (ans == Answers::correct) {
			curentState_m = BattleState::Corect;
		}
		// •s³‰ğ
		else if (ans == Answers::incorrect) {
			curentState_m = BattleState::Incorect;
		}
	}
	break;

	// •s³‰ğ‚ğ‘I‚ñ‚Å‘I‘ğ‚Å‚«‚È‚­‚È‚Á‚Ä‚¢‚éŠÔ‚Ìˆ—
	case BattleState::CanNotAnswer:
		if (isImprove) {
			curentState_m = BattleState::Answer;
		}
		AnswerManager::init();
		break;

		// •s³‰ğ‚ğ‘I‚ñ‚¾uŠÔ‚Ìˆ—
	case BattleState::Incorect:
		curentState_m = BattleState::CanNotAnswer;
		break;

		//³‰ğ‚ğ‘I‚ñ‚¾uŠÔ‚Ìˆ—
	case BattleState::Corect:
		curentState_m = BattleState::ExitEnemy;
		break;

		// ³‰ğ‚µ‚Ä“G‚ªÁ‚¦‚Ä‚¢‚­ŠÔ‚Ìˆ—
	case BattleState::ExitEnemy:
		if (StateManager::isImprove) {
			curentState_m = BattleState::CheckGameClear;
		}
		break;

	case BattleState::CheckGameClear:
		curentState_m = BattleState::EnemyEntry;
		break;

		// ŠÔØ‚ê‚É‚È‚Á‚½uŠÔ‚Ìˆ—
	case BattleState::TimeOver:
		curentState_m = BattleState::GameOver;
		break;

		// ƒQ[ƒ€ƒI[ƒo[‚É‚È‚Á‚½‚Ìˆ—
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
