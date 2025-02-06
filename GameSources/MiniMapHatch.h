/*!
@file MiniMapHatch.h
@brief ミニマップ用のハッチ
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class MiniMapHatch :public Sprite
	{
	private:
		bool m_plusColorFlag;//色をの透明度を足すか決めるフラグ
		bool m_updateFlag;
	public:
		MiniMapHatch(shared_ptr<Stage>& stagePtr,wstring textureName,Vec2 size, Vec3 pos = Vec3(0.0f,0.0f,0.0f),Vec3 rot = Vec3(0.0f,0.0f,0.0f),Col4 color = Col4(1.0f,1.0f,1.0f,1.0f),int layer = 1);
		~MiniMapHatch();

		void OnUpdate()override;

		void OnClear(bool OnOff)override;//透明になる関数

	};

}
//end basecross
