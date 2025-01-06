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
		vector<vector<int>> m_upWallMap;
		vector<vector<int>> m_rightWallMap;
		vector<vector<int>> m_unityMap;//A*のマップ
		vector<int> m_unityLine;//A*のマップの一行
		wstring m_stageName;//ステージの名前

		float m_mapSize;//マップのサイズ(直径)
		float m_push;//一気にオブジェクト生成する際にエクセルの座標と合わせるための数値

		bool m_UpdetaUnityMapFlag;//UnityMapの更新

	public:
		enum SelMapCount
		{
			Map_None = 0,
			Map_Manhole,
			Map_ManholeSet,
			Map_ManholeOpen,
			Map_ExitNone,
			Map_ExitOpen,
			Map_Item
		};
		MapManager(shared_ptr<Stage>& stagePtr,wstring stageName=L"Stage01/");//コンストラクタ
		~MapManager();//デストラクタ

		void OnCreate()override;//生成
		void OnUpdate()override;//更新

		Vec2 ConvertSelMap(Vec3 worldPosition);//ワールド座標からセル座標に変える
		Vec3 ConvertWorldMap(Vec2 selPosition);
		Vec2 ConvertUnityMap(Vec2 selPosition);
		Vec2 ConvertU_S(Vec2 AStarPosition);//AStarからセルマップに変える

		void MapDataUpdate(Vec3 worldPosition,int change);
		int SelMapNow(Vec3 worldPosition);//今のセル座標に何があるのかを返す

		void StageMapLoad();
		void WallMapLoad();
		void UnityMapCreate();//A*マップの作成
		void WallCreate();//壁を生成
		void AddExctraUnity(int addArray);//余分にA*に配列を入れる処理
		void AddArray(int loop,int num);//配列に数値を入れる処理

		void SetUpdataUnityMapFlag(bool flag);

		float GetMapSize();//マップのサイズを渡す処理

		vector<vector<int>> TestAStar();//A*のテスト用のマップ取得

		vector<vector<int>> GetUnityMap();//A*マップの取得
	};


}
//end basecross
