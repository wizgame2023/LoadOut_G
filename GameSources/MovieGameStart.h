/*!
@file MovieGameStart.h
@brief ゲーム開始時のムービ用
*/

#pragma once
#include "stdafx.h"
#include"Movie.h"

namespace basecross {
	class MovieGameStart :public Movie
	{
	private:
		int m_count;//ムービーの進行度
	public:
		MovieGameStart(shared_ptr<Stage>& stagePtr);
		~MovieGameStart();

		void OnCreate()override;
		void OnUpdate()override;

		void CameraChange()override;
	};

}
//end basecross
