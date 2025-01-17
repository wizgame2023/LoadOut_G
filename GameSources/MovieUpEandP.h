/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MovieUpEandP :public Movie
	{
	private:
		float m_time;
		Col4 m_spriteCol;//スプライト(暗転用)のカラー
		weak_ptr<Enemy> m_Enemy;//ムービーの注視点となるEnemy
		weak_ptr<Player> m_Player;//ムービーの注視点となるPlayer
		shared_ptr<Sprite> m_sprite;

	public:
		MovieUpEandP(shared_ptr<Stage>& stagePtr, weak_ptr<Enemy> enemy,weak_ptr<Player> player);
		~MovieUpEandP();

		void OnCreate()override;
		void OnUpdate()override;
	};


}
//end basecross
