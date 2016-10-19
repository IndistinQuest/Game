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

	//マウス押しでフェードアウトの早さを調節
	//BattleSceneNums::fadeOut = (Input::MouseL.pressed) ? 4 : 2;

	switch (StateManager::getState())
	{
		// 敵が登場するときの処理
	case BattleState::EnemyEntry:
		newEnemy();
		break;
		//正解を選んだ瞬間の処理
	case BattleState::Corect:
		enemyPic_m->setFadeOut();
		enemyPic_m->setRoolAndSmall();
		break;

		// 時間切れになった瞬間の処理
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

	// 次の敵のデータを取得
	enemy_m = std::make_shared<EnemyData>(dataManager_m.getEnemy(getId(round)));

	int id = enemy_m->id_m;

	// 特殊な処理をする敵の場合の関数を呼ぶ
	if (id == 16) { montagePhantom(round); }
	else if (id == 29) { carillon(); }

	// Enemy画像設定
	enemyPic_m->changeTexture(Format(L"Enemy", enemy_m->id_m));
	enemyPic_m->setBigger();

	// 背景画像設定
	backPic_m->changeTexture(Format(L"battleBack", enemy_m->bgid_m));

	// 正解を登録
	AnswerManager::setCorectAnswer(enemy_m->collectAnswer_m);

	// 特殊な敵の時カットインを入れる	
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

// 登場順リストを初期化する
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

// 特殊モンスター　モンタージュファントム
void EnemyManager::montagePhantom(int round) {
	int rand;
	do {
		rand = enemyIdList_m[Random(1, round - 1)];
	} while (rand == 16 || rand == 22 || rand == 29);		//特殊モンスターはコピーしない

															//コピーするモンスターのデータを取得
	auto monta = std::make_shared<EnemyData>(dataManager_m.getEnemy(rand));

	//登場メッセージを設定
	enemy_m->messages_m.onContact_m = L"モンタージュファントムが現れた！\nモンタージュファントムは" + monta->name_m + L"に変化した！";

	//攻撃失敗時のメッセージを設定
	enemy_m->messages_m.onPlayerLost_m = monta->name_m + L"に攻撃を仕掛けた！\nだが倒しきれなかった！";

	//正解をコピー
	enemy_m->collectAnswer_m = monta->collectAnswer_m;

	//選択肢をコピー
	for (int i = 0; i < 3; i++) {
		enemy_m->answers_m.weapon_m[i] = monta->answers_m.weapon_m[i];
		enemy_m->answers_m.magic_m[i] = monta->answers_m.magic_m[i];
		enemy_m->answers_m.special_m[i] = monta->answers_m.special_m[i];
	}
}
// 特殊モンスター　カリキョン
void EnemyManager::carillon() {

	//式と答えを設定
	int a = Random(10, 99);
	int b = Random(1, a);
	String ope = (Random(1) == 0) ? L"+" : L"-";
	int ans = (ope == L"+") ? a + b : a - b;

	//正解を設定
	enemy_m->collectAnswer_m = Format(ans);

	//登場メッセージを設定
	enemy_m->messages_m.onContact_m = Format(L"計算兵器カリキョンが現れた！\n「", a, ope, b, L"は？」");

	//攻撃失敗時のメッセージを設定
	enemy_m->messages_m.onPlayerLost_m = Format(L"「この程度の問題を間違えるな」\n計算兵器カリキョンを倒しきれなかった！");//\n「", a, ope, b, L"は？」");

																							//選択肢をランダムに用意
	int nums[9];
	for (int i = 0; i < 9; i++) nums[i] = Random(1, 100);
	nums[Random(8)] = ans + 10;		// 正解より10大きい選択肢を用意
	nums[Random(8)] = ans;			// 正解を用意

	for (int i = 0; i < 3; i++) {
		enemy_m->answers_m.weapon_m[i] = Format(nums[i]);
		enemy_m->answers_m.magic_m[i] = Format(nums[3 + i]);
		enemy_m->answers_m.special_m[i] = Format(nums[6 + i]);
	}
}
