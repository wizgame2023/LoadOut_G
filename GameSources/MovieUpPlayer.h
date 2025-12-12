/*!
@file MovieUpPlayer.h
@brief マンホールに当たって打ちあがるプレイヤー
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieUpPlayer :public Movie
	{
	private:
		float m_time;				 // 時間計測
		Col4 m_spriteCol;			 // スプライト(暗転用)のカラー
		shared_ptr<Sprite> m_sprite; // 暗転用のスプライト
	public:
		MovieUpPlayer(shared_ptr<Stage>& stagePtr);
		~MovieUpPlayer();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
