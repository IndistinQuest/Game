#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

class GameData;

using Scene = SceneManager<String, GameData>::Scene;

namespace scene {
	namespace enemyGuide {
		class EGDetailType : public Scene
		{
		public:
			void init() override;
			void update() override;
			void draw()const override;
		};
	}
}

