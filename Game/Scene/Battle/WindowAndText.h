#pragma once
#include"BattleSceneObject.h"

namespace scene {
	namespace battle {
		//�e�L�X�g�t���E�B���h�E
		class WindowAndText : public BattleSceneObject
		{
		protected:
			const Point center_m;
			const String textureAssetName_m;
			Color strColor_m;
			String str_m;
		public:
			WindowAndText(Point center, String textureAssetName, Color c = Palette::Black);
			void update()override;
			void setText(String text);
			void draw()const override;
		};
	}
}