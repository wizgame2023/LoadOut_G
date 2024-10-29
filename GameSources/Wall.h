/*!
@file Wall.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Wall :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション
		Vec3 m_rot;//回転
		Vec3 m_scale;//サイズ

	public:
		Wall(shared_ptr<Stage>& stagePtr, Vec3 pos, Vec3 rot,Vec3 scalse = Vec3(10.0f, 10.0f, 1.0f));//コンストラクタ
		~Wall();//デストラクタ

		void OnCreate()override;//生成
	};


}
//end basecross
