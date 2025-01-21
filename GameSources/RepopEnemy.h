/*!
@file RepopEnemy.h
@brief リポップ時の敵の動き
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RepopEnemy :public StateBase
	{
	private:
		float m_goalPosY;//目標地点
		float m_speed;
	public:
		RepopEnemy(const shared_ptr<Enemy> ptrOwner,float goalPosY = 10.0f);
		~RepopEnemy();

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;
	}; 

}
//end basecross
