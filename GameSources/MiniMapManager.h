/*!
@file MiniMapManager.h
@brief ミニマップ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MiniMapManager :public GameObject
	{
	private:
	public:
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//作成
		void OnUpdate()override;//更新
	};

}
//end basecross
