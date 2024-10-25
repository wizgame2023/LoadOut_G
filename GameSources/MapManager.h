/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MapManager :public GameObject
	{
	private:

	public:
		MapManager(shared_ptr<Stage>& stagePtr);//コンストラクタ
		~MapManager();//デストラクタ

		void OnCreate()override;//生成
		void OnUpdate()override;//更新

		Vec2 MyMapNow(Vec3 worldPosition);
	};


}
//end basecross
