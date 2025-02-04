/*!
@file RepopEnemy.h
@brief リポップ時の敵の動き
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TargetLost :public Patrol
	{
	private:
		float m_goalPosY;//目標地点
		float m_speed;
		float m_aStarUpdateCount;//AStar処理の更新する時間を測るもの

		bool m_arrive;//たどり着いたかのフラグ

		Vec3 m_ownerPos;
		Vec3 m_ownerRot;
		Vec3 m_playerPos;
		Vec3 m_forward;
		Vec3 m_right;

		Vec3 m_targetPos;//目標地点
		vector<Vec3>m_navi;//目標地点にたどり着くための移動場所
		int m_numbers;//移動処理の何番目の移動処理科を数えるための変数

	public:
		TargetLost(const shared_ptr<Enemy> ptrOwner);
		~TargetLost();

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}
//end basecross
