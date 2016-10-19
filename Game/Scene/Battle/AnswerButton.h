#pragma once
#include"BattleSceneButton.h"
#include"AnswerManager.h"
namespace scene {
	namespace battle {
		// ‰ñ“š‚Ìƒ{ƒ^ƒ“
		class AnswerButton : public BattleSceneButton {
		public:
			AnswerButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black);
			void onClicked()override;
		};
	}
}