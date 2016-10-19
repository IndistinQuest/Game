#include"SoundPlayer.h"
#include"StateManager.h"
using namespace scene::battle;

SoundPlayer::SoundPlayer() {
	// BGMをループ再生
	bgmName_m = Format(L"battle_bgm", Random<int>(3));
	SoundAsset(bgmName_m).setLoop(true);
	SoundAsset(bgmName_m).play();
}
SoundPlayer::~SoundPlayer() {
	SoundAsset(bgmName_m).stop();
}
void SoundPlayer::update(){

	switch (StateManager::getState())
	{
		// 敵が登場するときの処理
	case BattleState::EnemyEntry:
		SoundAsset(L"bettle_entry").setSpeed(0.5);
		SoundAsset(L"bettle_entry").play();
		break;

		// 不正解を選んだ瞬間の処理
	case BattleState::Incorect:
		SoundAsset(L"battle_incorect").playMulti();
		break;

		//正解を選んだ瞬間の処理
	case BattleState::Corect:
		SoundAsset(L"battle_corect").playMulti();
		break;

		// 時間切れになった瞬間の処理
	case BattleState::TimeOver:
		SoundAsset(L"bettle_GameOver").play();
	default:
		break;
	}
}
void SoundPlayer::draw()const{}
