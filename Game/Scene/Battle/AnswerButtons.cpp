#include"AnswerButtons.h"
#include"StateManager.h"
#include"../../Button/ButtonManager.h"
using namespace scene::battle;

AnswerButtons::AnswerButtons() {
	const int tx = 5, ty = 5;
	const int width = 420;
	const int height = 60;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			auto b = std::make_shared<AnswerButton>(AnswerButton({ Window::Width() / 2 - width / 2 + (width + tx) * (i - 1), Window::Height() - (height + ty) * (3 - j) }, Size(width, height), L"battleButton"));
			b->setStrColor(Palette::Black);
			b->setText(L"Start");
			buttons_m[3 * i + j] = b;
			ButtonManager::add(b);
		}
	}
	AnswerManager::setCorectAnswer(L"Start");

	penalty_m = 0;
}
void AnswerButtons::update(){
	switch (StateManager::getState())
	{
		// 敵が登場するときの処理
	case BattleState::EnemyEntry:
		setAnswers();
		break;

	case BattleState::Answer:
		for (auto& b : buttons_m) { b->setStrColor(Palette::Black); }
		break;

		// 不正解を選んで選択できなくなっている間の処理
	case BattleState::CanNotAnswer:
		penalty_m--;
		if (penalty_m == 0) {
			for (auto& b : buttons_m) { b->setStrColor(Palette::Black); }
			StateManager::goToNext();
		}
		break;

		// 不正解を選んだ瞬間の処理
	case BattleState::Incorect:
		penalty_m = PENALTY_TIME;
		for (auto& b : buttons_m) { b->setStrColor(Palette::Red); }
		break;
	default:
		break;
	}
};
void AnswerButtons::draw()const{
	for (auto b : buttons_m) { b->draw(); }
}
void AnswerButtons::setAnswers() {
	// ボタンに選択しを設定
	for (int i = 0; i < 3; i++) {
		buttons_m[i]->setText(enemyManager_m->getEnemy()->answers_m.weapon_m[i]);
		buttons_m[i + 3]->setText(enemyManager_m->getEnemy()->answers_m.magic_m[i]);
		buttons_m[i + 6]->setText(enemyManager_m->getEnemy()->answers_m.special_m[i]);
	}
}
void AnswerButtons::setEnemyManager(std::shared_ptr<EnemyManager> e) {
	enemyManager_m = e;
}
