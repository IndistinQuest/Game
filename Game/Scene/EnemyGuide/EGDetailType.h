#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "../../Data/DataManager.h"
#include "../../Data/EnemyData.h"
#include "MyDrawableList.h"
#include "EnemyGuide.h"


class GameData;

using Scene = SceneManager<String, GameData>::Scene;

namespace scene {
	namespace enemyGuide {
		class EGDetailType : public EnemyGuide, public Scene
		{
		private:
			static const Point POS_NEXT_BUTTON;
			static const Point POS_PREVIOUS_BUTTON;
			static const Point POS_LIST_BUTTON;
			static const Point POS_TARGET;


			DataManager dataManager_m;

			EnemyData target_m;

			std::function<void(void)> goToNext_m;
			std::function<void(void)> backToPrevious_m;
			std::function<void(void)> backToList_m;

			std::shared_ptr<RoundRectTextButton> nextButton_m;
			std::shared_ptr<RoundRectTextButton> previousButton_m;
			std::shared_ptr<RoundRectTextButton> backToListButton_m;

			int cursorID_m;
			MyDrawableList targetGraphics_m;

			void changeTarget();
			void nextTarget();
			void previousTarget();
		public:
			void init() override;
			void update() override;
			void draw()const override;
		};
	}
}

