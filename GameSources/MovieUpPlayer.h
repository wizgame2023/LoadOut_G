/*!
@file MovieUpPlayer.h
@brief マンホールに当たって打ちあがるプレイヤー
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieUpPlayer :public Movie
	{
	private:
		float m_time;
		Col4 m_spriteCol;//スプライト(暗転用)のカラー
		shared_ptr<Sprite> m_sprite;
	public:
		MovieUpPlayer(shared_ptr<Stage>& stagePtr);
		~MovieUpPlayer();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
