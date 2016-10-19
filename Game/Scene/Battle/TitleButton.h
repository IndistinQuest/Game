#pragma once
#include"BattleSceneButton.h"
namespace scene {
	namespace battle {
		// タイトルへのボタン
		class TitleButton : public BattleSceneButton {
		public:
			TitleButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black);
			void onClicked()override;
		};
	}
}