/*!
@file MovieUpEandP.h
@brief プレイヤーと敵が一緒に打ちあがるムービー
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MovieUpEandP :public Movie
	{
	private:
		float m_time;			     // 時間計測
		Col4 m_spriteCol;		     // スプライト(暗転用)のカラー
		weak_ptr<Enemy> m_Enemy;     // ムービーの注視点となるEnemy
		weak_ptr<Player> m_Player;	 // ムービーの注視点となるPlayer
		shared_ptr<Sprite> m_sprite; // 暗転用のスプライト

	public:
		MovieUpEandP(shared_ptr<Stage>& stagePtr, weak_ptr<Enemy> enemy,weak_ptr<Player> player);
		~MovieUpEandP();

		void OnCreate()override;
		void OnUpdate()override;
	};


}
//end basecross
