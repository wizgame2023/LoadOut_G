/*!
@file MovieGameOver.h
@brief ゲームオーバーのムービー
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieGameOver :public Movie
	{
	private:
		Vec3 m_tagetPos;//目的地
		bool m_gameOverFlag;//ゲームオーバーのフラグ
	public:
		MovieGameOver(shared_ptr<Stage>& stagePtr);
		~MovieGameOver();

		void OnCreate()override;
		void OnUpdate()override;

	};


}
//end basecross
