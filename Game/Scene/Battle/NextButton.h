#pragma once
#include"BattleSceneButton.h"
namespace scene {
	namespace battle {
		// Ÿ‚Öi‚Şƒ{ƒ^ƒ“
		class NextButton
			: public BattleSceneButton {
		public:
			NextButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black);
			void update()override;
			void onClicked() override;
		};
	}
}