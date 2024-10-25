/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player :public GameObject
	{
	private:
		Vec3 m_Pos;//ポジション
		Vec3 m_Rot;//回転度

		shared_ptr<Transform> m_Trans;//トランスフォーム

	public:
		Player(const shared_ptr<Stage>& StagePtr, Vec3 pos,Vec3 rot);//コンストラクタ
		~Player();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross

