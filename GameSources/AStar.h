/*!
@file AStar.h
@brief 経路探査処理
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Node;
	class AStar :public GameObject
	{
	private:
		//前のPlayerのAStar座標
		Vec2 m_beforPlayerUnity;

		vector<vector<shared_ptr<Node>>> m_unityMap;//マップのノード配列
		vector<vector<int>> m_unityMapCSV;//AStarMapのCSVデータ

	public:
		AStar(shared_ptr<Stage>& stagePtr);//コンストラクタ
		~AStar();//デストラクタ

		void OnCreate() override;//作成
		void OnUpdate() override;//更新

		vector<Vec3> RouteSearch(Vec3 startPos,Vec3 goalPos);//経路探査
		void MoveActor(shared_ptr<Actor> actor,vector<Vec3> routePos,int& routeCount,float speed);//移動処理
		bool LookAround(shared_ptr<Node> parent, Vec2 goalPos);//周りを確認する処理
	};

	enum STATUS//ステータス
	{
		Status_None,
		Status_Open,
		Status_Closed
	};

	//ノードデータ
	class Node
	{
	public:
		int x;
		int y;
		int Status;//ステータス
		int Cost;//コスト
		int HeuristicCost;//ヒューリスティックコスト
		int Score;//スコア
		shared_ptr<Node> Parent;//親のポインタ

		Node(int x, int y, int Status, int Cost, int HeuristicCost, int Score, shared_ptr<Node> parent) :
			x(x),
			y(y),
			Status(Status),
			Cost(Cost),
			HeuristicCost(HeuristicCost),
			Score(Score),
			Parent(parent)
		{

		}
		~Node()
		{
		}
	};

}
//end basecross
