#include"EnemyManager.h"
#include"AnswerManager.h"
#include"StateManager.h"
using namespace scene::battle;

EnemyManager::EnemyManager() : dataManager_m()
{
	initIdList();
}
EnemyManager::~EnemyManager() {
	writeGameDataAndSaveData(data_m);
}
void EnemyManager::setObjects(pic enemy, pic background, std::shared_ptr<CutIn> cutIn)
{
	backPic_m = background;
	cutIn_m = cutIn;
	enemyPic_m = enemy;
	initIdList();
}
void EnemyManager::update(){

	//�}�E�X�����Ńt�F�[�h�A�E�g�̑����𒲐�
	//BattleSceneNums::fadeOut = (Input::MouseL.pressed) ? 4 : 2;

	switch (StateManager::getState())
	{
		// �G���o�ꂷ��Ƃ��̏���
	case BattleState::EnemyEntry:
		newEnemy();
		break;
		//������I�񂾏u�Ԃ̏���
	case BattleState::Corect:
		enemyPic_m->setFadeOut();
		enemyPic_m->setRoolAndSmall();
		break;

		// ���Ԑ؂�ɂȂ����u�Ԃ̏���
	case BattleState::TimeOver:
		enemyPic_m->setExpansion();
		break;

	default:
		break;
	}
}

void EnemyManager::draw()const{}

std::shared_ptr<EnemyData> EnemyManager::getEnemy() {
	return enemy_m;
}

int EnemyManager::getId(int round) {
	return (0 < round && round < 31) ? enemyIdList_m[round] : 0;
}

void EnemyManager::setRoundCounter(std::shared_ptr<RoundCounter> r) {
	round_m = r;
}

void EnemyManager::setGameData(std::shared_ptr<GameData> data) {
	data_m = data;
}

void EnemyManager::newEnemy() {

	int round = round_m->getRound();

	// ���̓G�̃f�[�^���擾
	enemy_m = std::make_shared<EnemyData>(dataManager_m.getEnemy(getId(round)));

	int id = enemy_m->id_m;

	// ����ȏ���������G�̏ꍇ�̊֐����Ă�
	if (id == 16) { montagePhantom(round); }
	else if (id == 29) { carillon(); }

	// Enemy�摜�ݒ�
	enemyPic_m->changeTexture(Format(L"Enemy", enemy_m->id_m));
	enemyPic_m->setBigger();

	// �w�i�摜�ݒ�
	backPic_m->changeTexture(Format(L"battleBack", enemy_m->bgid_m));

	// ������o�^
	AnswerManager::setCorectAnswer(enemy_m->collectAnswer_m);

	// ����ȓG�̎��J�b�g�C��������	
	if (id == 16 || id == 22 || id == 29) { cutIn_m->init(); }
	else { cutIn_m->hide(); }
}

void EnemyManager::writeGameDataAndSaveData(std::shared_ptr<GameData> data) {
	for (int i = 1; i < round_m->getRound(); i++) {
		data->addEnemy(getId(i));
		dataManager_m.setSaveData(getId(i), true);
	}
	dataManager_m.writeSaveData();
}

// �o�ꏇ���X�g������������
void EnemyManager::initIdList() {
	for (int i = 1; i <= 30; i++)enemyIdList_m[i] = i;
	std::swap(enemyIdList_m[16], enemyIdList_m[27]);
	std::swap(enemyIdList_m[22], enemyIdList_m[28]);
	for (int i = 1; i <= 26; i++) {
		std::swap(enemyIdList_m[i], enemyIdList_m[Random(1, 26)]);
	}
	std::swap(enemyIdList_m[27], enemyIdList_m[Random(15, 29)]);
	std::swap(enemyIdList_m[28], enemyIdList_m[Random(15, 29)]);
	std::swap(enemyIdList_m[29], enemyIdList_m[Random(15, 29)]);
}

// ���ꃂ���X�^�[�@�����^�[�W���t�@���g��
void EnemyManager::montagePhantom(int round) {
	int rand;
	do {
		rand = enemyIdList_m[Random(1, round - 1)];
	} while (rand == 16 || rand == 22 || rand == 29);		//���ꃂ���X�^�[�̓R�s�[���Ȃ�

															//�R�s�[���郂���X�^�[�̃f�[�^���擾
	auto monta = std::make_shared<EnemyData>(dataManager_m.getEnemy(rand));

	//�o�ꃁ�b�Z�[�W��ݒ�
	enemy_m->messages_m.onContact_m = L"�����^�[�W���t�@���g�������ꂽ�I\n�����^�[�W���t�@���g����" + monta->name_m + L"�ɕω������I";

	//�U�����s���̃��b�Z�[�W��ݒ�
	enemy_m->messages_m.onPlayerLost_m = monta->name_m + L"�ɍU�����d�|�����I\n�����|������Ȃ������I";

	//�������R�s�[
	enemy_m->collectAnswer_m = monta->collectAnswer_m;

	//�I�������R�s�[
	for (int i = 0; i < 3; i++) {
		enemy_m->answers_m.weapon_m[i] = monta->answers_m.weapon_m[i];
		enemy_m->answers_m.magic_m[i] = monta->answers_m.magic_m[i];
		enemy_m->answers_m.special_m[i] = monta->answers_m.special_m[i];
	}
}
// ���ꃂ���X�^�[�@�J���L����
void EnemyManager::carillon() {

	//���Ɠ�����ݒ�
	int a = Random(10, 99);
	int b = Random(1, a);
	String ope = (Random(1) == 0) ? L"+" : L"-";
	int ans = (ope == L"+") ? a + b : a - b;

	//������ݒ�
	enemy_m->collectAnswer_m = Format(ans);

	//�o�ꃁ�b�Z�[�W��ݒ�
	enemy_m->messages_m.onContact_m = Format(L"�v�Z����J���L���������ꂽ�I\n�u", a, ope, b, L"�́H�v");

	//�U�����s���̃��b�Z�[�W��ݒ�
	enemy_m->messages_m.onPlayerLost_m = Format(L"�u���̒��x�̖����ԈႦ��ȁv\n�v�Z����J���L������|������Ȃ������I");//\n�u", a, ope, b, L"�́H�v");

																							//�I�����������_���ɗp��
	int nums[9];
	for (int i = 0; i < 9; i++) nums[i] = Random(1, 100);
	nums[Random(8)] = ans + 10;		// �������10�傫���I������p��
	nums[Random(8)] = ans;			// ������p��

	for (int i = 0; i < 3; i++) {
		enemy_m->answers_m.weapon_m[i] = Format(nums[i]);
		enemy_m->answers_m.magic_m[i] = Format(nums[3 + i]);
		enemy_m->answers_m.special_m[i] = Format(nums[6 + i]);
	}
}
