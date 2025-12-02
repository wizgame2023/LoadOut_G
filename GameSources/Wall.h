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

		Vec3 m_miniMapStartPos;//ミニマップの中心点

	public:
		Wall(const shared_ptr<Stage>& stagePtr,const Vec3& pos,const Vec3& rot,const Vec3& miniMapStartPos,const Vec3& scalse = Vec3(10.0f, 10.0f, 1.0f));//コンストラクタ
		~Wall();//デストラクタ

		void MiniMapCreate(const Vec3& miniMapStartPos);//ミニマップの自分自身を生成

		void OnCreate()override;//生成
	};


}
//end basecross
