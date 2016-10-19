#pragma once
#include"BattleSceneButton.h"
namespace scene {
	namespace battle {
		// �^�C�g���ւ̃{�^��
		class TitleButton : public BattleSceneButton {
		public:
			TitleButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black);
			void onClicked()override;
		};
	}
}