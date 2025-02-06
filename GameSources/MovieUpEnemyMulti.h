/*!
@file MovieUpEnemyMulti.h
@brief 敵が複数打ちあがるムービー
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieUpEnemyMulti :public Movie
	{
	private:
		Vec3 m_tagetPos;//目的地
		Vec3 m_movieCameraAt;//カメラの注視点

		vector<weak_ptr<Enemy>> m_upEnemyVec;//打ち上げる敵のポインタの配列
		vector<float> m_upEnemyMoveAngleVec;//打ちあがる敵がどの方向に打ちあがるのか保存する配列

		bool m_removeFlag;//ムービーを終了するフラグ
	public:
		MovieUpEnemyMulti(shared_ptr<Stage>& stagePtr,vector<weak_ptr<Enemy>> enemyVec);
		~MovieUpEnemyMulti();

		void OnCreate()override;
		void OnUpdate()override;

	};
}
//end basecross
