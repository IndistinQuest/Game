#include"SoundPlayer.h"
#include"StateManager.h"
using namespace scene::battle;

SoundPlayer::SoundPlayer() {
	// BGM�����[�v�Đ�
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
		// �G���o�ꂷ��Ƃ��̏���
	case BattleState::EnemyEntry:
		SoundAsset(L"bettle_entry").setSpeed(0.5);
		SoundAsset(L"bettle_entry").play();
		break;

		// �s������I�񂾏u�Ԃ̏���
	case BattleState::Incorect:
		SoundAsset(L"battle_incorect").playMulti();
		break;

		//������I�񂾏u�Ԃ̏���
	case BattleState::Corect:
		SoundAsset(L"battle_corect").playMulti();
		break;

		// ���Ԑ؂�ɂȂ����u�Ԃ̏���
	case BattleState::TimeOver:
		SoundAsset(L"bettle_GameOver").play();
	default:
		break;
	}
}
void SoundPlayer::draw()const{}
