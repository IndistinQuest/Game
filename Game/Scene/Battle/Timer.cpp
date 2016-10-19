#include "Timer.h"
#include"StateManager.h"
using namespace scene::battle;

Timer::Timer(Point center, String textureAssetName, Color c)
	:WindowAndText(center, textureAssetName, c)
{
	time_m = TIME_LIMIT;
	stopWatch_m.reset();
	timeShow();
}
Timer::~Timer() {
	data_m->time = Max(0, time_m - stopWatch_m.ms()) / 10;
}
void Timer::update(){
	int curentTime = getCurentTime();
	strColor_m = ((curentTime < 10000) ? Palette::Red : Palette::Black);
	for (int i = 0; i < 4; i++) { SoundAsset(Format(L"battle_bgm", i)).changeTempo((curentTime < 10000) ? 1.2 : 1.0); }
	switch (StateManager::getState()) {
	case BattleState::Answer:
	case BattleState::CanNotAnswer:
		stopWatch_m.start();
		if (curentTime <= 0) { StateManager::setTimeOver(); }
		break;
	case BattleState::Corect:
		recovery();
		break;
	default:
		stopWatch_m.pause();
		break;
	}
	timeShow();
}
void Timer::recovery() {
	time_m += TIME_RECOVERY;
}
void Timer::setGameData(std::shared_ptr<GameData> data) {
	data_m = data;
}
void Timer::timeShow() {
	int curentTime = getCurentTime();
	setText(Format(Pad(curentTime / 1000, { 2,L'0' }), L".", Pad((curentTime % 1000) / 10, { 2,L'0' })));
}
int Timer::getCurentTime() {
	return Max(0, time_m - stopWatch_m.ms());
}