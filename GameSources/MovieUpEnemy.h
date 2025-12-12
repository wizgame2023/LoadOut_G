/*!
@file MovieUpEnemy.h
@brief 敵が打ちあがるムービー
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MovieUpEnemy :public Movie
	{
	private:
		float m_time;			     // 時間計測
		Col4 m_spriteCol;			 // スプライト(暗転用)のカラー
		weak_ptr<Enemy> m_Enemy;	 // ムービーの注視点となるEnemy
		shared_ptr<Sprite> m_sprite; // 暗転用のスプライト
	public:
		MovieUpEnemy(shared_ptr<Stage>& stagePtr,weak_ptr<Enemy> enemy);
		~MovieUpEnemy();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
