/*!
@file ManholeSprite.h
@brief ミニマップ用のマンホールスプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ManholeSprite : public Sprite
	{
	private:
		weak_ptr<Manhole> m_parent;//マンホールのポインタ
		float m_countTime;//時間計測
	public:
		ManholeSprite(shared_ptr<Stage>& stagePtr,shared_ptr<Manhole> parent, wstring textureName, Vec2 size, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f), Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f), int layer = 1);
		~ManholeSprite();

		void OnUpdate()override;
	};
}
//end basecross
