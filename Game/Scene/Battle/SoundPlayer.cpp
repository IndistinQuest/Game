#include"SoundPlayer.h"
#include"StateManager.h"
using namespace scene::battle;

SoundPlayer::SoundPlayer() {
	// BGM‚ğƒ‹[ƒvÄ¶
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
		// “G‚ª“oê‚·‚é‚Æ‚«‚Ìˆ—
	case BattleState::EnemyEntry:
		SoundAsset(L"bettle_entry").setSpeed(0.5);
		SoundAsset(L"bettle_entry").play();
		break;

		// •s³‰ğ‚ğ‘I‚ñ‚¾uŠÔ‚Ìˆ—
	case BattleState::Incorect:
		SoundAsset(L"battle_incorect").playMulti();
		break;

		//³‰ğ‚ğ‘I‚ñ‚¾uŠÔ‚Ìˆ—
	case BattleState::Corect:
		SoundAsset(L"battle_corect").playMulti();
		break;

		// ŠÔØ‚ê‚É‚È‚Á‚½uŠÔ‚Ìˆ—
	case BattleState::TimeOver:
		SoundAsset(L"bettle_GameOver").play();
	default:
		break;
	}
}
void SoundPlayer::draw()const{}
