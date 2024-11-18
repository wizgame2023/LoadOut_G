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

		float m_mapSize;//マップの直径
		float m_mapMagnification;//マップの倍率
	public:
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void CreateWall();//ミニマップの壁を生成する
		void CreateItem();//ミニマップのアイテムを生成する
		void CreateManhole();//ミニマップのマンホールを生成する
		void CreateEnemy();//ミニマップの敵を生成する

		Vec3 GetStartPos();//ミニマップの原点を渡す
	};

}
//end basecross
