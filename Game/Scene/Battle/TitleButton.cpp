#include"TitleButton.h"
#include"StateManager.h"
using namespace scene::battle;

TitleButton::TitleButton(Point pos, Size size, String textureAssetName, Color c) 
	:BattleSceneButton(pos, size, textureAssetName, c) 
{
	setText(L"タイトルにもどる");
}
void TitleButton::onClicked(){
	StateManager::setBackToTitle();
}
