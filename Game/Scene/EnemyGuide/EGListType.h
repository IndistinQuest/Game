#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "Heading.h"
#include "../../Data/DataManager.h"
#include "../../Drawable/DrawableList.h"
#include "../../Drawable/DrawableTxture.h"
#include "../../Button/ButtonManager.h"
#include "../../Button/RoundRectButton.h"
#include "DrawableTexture.h"

class GameData;

using Scene = SceneManager<String, GameData>::Scene;

namespace scene {
	namespace enemyGuide {
		class EGListType :public Scene
		{
		private:
			static const double W;
			static const double H;
			static const Point POS_HEADING;
			static const Point POS_HOME_BUTTON;
			static const int KIND_OF_ENEMIES;
			static const double LIST_MARGIN;
			static const double LIST_BORDER;
			static const int LIST_ROW;
			static const int LIST_COL;
			static const double ICON_W;
			static const double ICON_H;

			double iconX(int i);
			double iconY(int i);


			DataManager dataManager_m;
			const Heading title_m;
			DrawableList graphics_m;
			std::function<void(void)> backToTitle_m;
			std::shared_ptr<RoundRectTextButton> homeButton_m;
			std::shared_ptr<jumpaku::DrawableTxture> background_m;

		public:
			void init() override;
			void update() override;
			void draw() const override;
		};
	}
}

