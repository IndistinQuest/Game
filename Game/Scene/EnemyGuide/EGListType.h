#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "Heading.h"
#include "../../Data/DataManager.h"
#include "../../Drawable/DrawableList.h"
#include "../../Drawable/DrawableTxture.h"
#include "../../Button/ButtonManager.h"
#include "../../Button/RoundRectButton.h"

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

			DataManager dataManager_m;
			const Heading title_m;
			DrawableList icons_m;
			std::function<void(void)> backToTitle_m;
			std::shared_ptr<RoundRectTextButton> homeButton_m;

		public:
			//EGListType();
			//~EGListType();
			void init() override;
			void update() override;
			void draw() const override;
		};
	}
}

