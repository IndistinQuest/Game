#pragma once
#include"WindowAndText.h"
namespace scene {
	namespace battle {
		// êÌì¨êî
		class RoundCounter : public WindowAndText {
		private:
			int round_m;
		public:
			RoundCounter(Point center, String textureAssetName, Color c = Palette::Black);
			void next();
			void update()override;
			bool isGameClear()const;
			int getRound()const;
		};
	}
}