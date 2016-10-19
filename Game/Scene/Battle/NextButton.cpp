#include"NextButton.h"
#include"StateManager.h"
using namespace scene::battle;

NextButton::NextButton(Point pos, Size size, String textureAssetName, Color c) 
	:BattleSceneButton(pos, size, textureAssetName, c) {
	setText(L"ŽŸ‚É‚·‚·‚Þ");
	hide();
	setStrColor(Palette::Blue);
};
void NextButton::update(){
	switch (StateManager::getState())
	{
	case BattleState::ExitEnemy:
	case BattleState::GameOver:
		show();
		break;
	default:
		hide();
		break;
	}
}
void NextButton::onClicked() {
	StateManager::goToNext();
}