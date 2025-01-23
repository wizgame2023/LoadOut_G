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
		float m_speed;
	public:
		SpriteMove(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f), Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f), float speed = 0.0f , int layer = 1);
		~SpriteMove();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
