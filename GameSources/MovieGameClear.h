/*!
@file MovieGameClear.h
@brief ゲームクリアのムービー
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieGameClear :public Movie
	{
	private:
		Vec3 m_tagetPos;//目的地
	public:
		MovieGameClear(shared_ptr<Stage>& stagePtr);
		~MovieGameClear();

		void OnCreate()override;
		void OnUpdate()override;

	};


}
//end basecross
