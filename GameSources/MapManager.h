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
		vector<vector<int>> m_stageMap;
		vector<vector<int>> m_aStarMap;//A*のマップ
		vector<int> m_aStarLine;//A*のマップの一行

	public:
		MapManager(shared_ptr<Stage>& stagePtr);//コンストラクタ
		~MapManager();//デストラクタ

		void OnCreate()override;//生成
		void OnUpdate()override;//更新

		Vec2 ConvertSelMap(Vec3 worldPosition);

		void MapDataUpdate(Vec3 worldPosition,int change);
		int SelMapNow(Vec3 worldPosition);//今のセル座標に何があるのかを返す

		void StageMapLoad();
		void WallMapLoad();
		void WallCreateKari();//仮の壁を生成しよう
		void AddExctraAStar(int addArray);//余分にA*に配列を入れる処理
		void AddArray(int loop,int num);//配列に数値を入れる処理

		vector<vector<int>> GetAStarMap();//A*マップの取得
	};


}
//end basecross
