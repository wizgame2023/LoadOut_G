/*!
@file SpriteMove.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpriteMove :public Sprite
	{
	private:

	public:
		SpriteMove();
		~SpriteMove();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
