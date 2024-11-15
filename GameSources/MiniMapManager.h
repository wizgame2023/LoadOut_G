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
		Vec3 m_startPos;//初期位置(ピポット)
	public:
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void CreateWall();//ミニマップの壁を生成する

		Vec3 GetStartPos();//ミニマップの原点を渡す
	};

}
//end basecross
