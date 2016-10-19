#pragma once
#include"BattleSceneObject.h"

namespace scene {
	namespace battle {
		// カットイン
		class CutIn : public BattleSceneObject
		{
		private:
			const Point END_POS = { 155,200 };
			const double LAST_SCALE = 0.5;
			double alpha_m;
			double scale_m;
			Point pos_m;
			unsigned timer_m;
			enum State { in, center, move, moved } state_m;
			bool isHide;
		public:
			CutIn();
			~CutIn();
			void init();
			void hide();
			void update() override;
			void draw()const override;
		};
	}
}