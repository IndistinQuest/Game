#include"AnswerButton.h"
using namespace scene::battle;
AnswerButton::AnswerButton(Point pos, Size size, String textureAssetName, Color c) 
	:BattleSceneButton(pos, size, textureAssetName, c) {};
void AnswerButton::onClicked(){
	AnswerManager::answer(text_m);
}