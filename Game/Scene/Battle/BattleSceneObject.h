#pragma once
#include"../../Drawable/Drawable.h"
namespace scene {
	namespace battle {
		class BattleSceneObject : public Drawable
		{
		public:
			virtual void update() = 0;
		};
	}
}
