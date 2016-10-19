#pragma once
#include<Siv3D.hpp>
#include"../../Button/BasicButton.h"
#include"BattleSceneObject.h"

namespace scene {
	namespace battle {
		class BattleSceneButton : public BasicButton, public BattleSceneObject {
		protected:
			const Size size;
			const Point pos;
			const Point center;
			String text_m;
			const String textureAssetName_m;
			Color color_m;	//ï∂éöêF
		public:
			BattleSceneButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black);
			void draw() const;
			void setText(String text);
			void onClicked() = 0;
			void update()override;
			void setStrColor(Color c);
		};
	}
}
