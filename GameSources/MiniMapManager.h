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

		int m_beforeItemNum;//前のアイテムの個数
		int m_beforeEnemyNum;//前の敵の数

		float m_mapSize;//マップの直径
		float m_mapMagnification;//マップの倍率
	public:
		MiniMapManager(shared_ptr<Stage>& stage, float mapSize);
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void CreateWall();//ミニマップの壁を生成する
		void CreateBattery();//ミニマップのアイテムを生成する
		void CreateManhole();//ミニマップのマンホールを生成する
		//void CreateWall();//ミニマップの壁を生成する
		void CreateEnemy();//ミニマップの敵を生成する
		void CreatePlayer();//ミニマップのプレイヤーを生成する

		void UpdateBattery();//ミニマップのアイテム表示(Update版)
		void UpdateEnemy();//ミニマップの敵表示(Update版)

		Vec3 GetStartPos();//ミニマップの原点を渡す
	};

}
//end basecross
