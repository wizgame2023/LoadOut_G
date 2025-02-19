/*!
@file AStar.h
@brief 経路探査処理
*/

#pragma once
#include "stdafx.h"
#include "MapManager.h"

namespace basecross {
	class Node;
	class AStar
	{
	private:
		bool m_aStarFirst;//AStarの移動処理が始めてか保存する変数
		bool m_XorZ;//X(false)方向に進んでいるかZ(true)方向に進んでいるかの変数

		int m_roopCount;//経路探査した回数を数える変数

		Vec3 m_targetPos;//目的地のワールド座標
		Vec3 m_movePos;//どう移動するか覚える変数(中の変数は-1か1,0のみ入れて良いものとする)

		vector<vector<shared_ptr<Node>>> m_unityMap;//マップのノード配列
		vector<vector<int>> m_unityMapCSV;//AStarMapのCSVデータ
		vector<Vec3> m_tagetRootPos;//通る道の配列

		weak_ptr<MapManager> m_mapManager;//マップマネージャー

	public:
		AStar();//コンストラクタ
		~AStar();//デストラクタ

		vector<Vec3> RouteSearch(Vec3 startPos,Vec3 goalPos);//経路探査
		bool MoveActor(shared_ptr<Actor> actor,vector<Vec3> routePos,int& routeCount,float speed);//移動処理
		bool LookAround(shared_ptr<Node> parent, Vec2& goalPos);//周りを確認する処理
		bool GetMoveXorZ();//今X,Zのどっちの方向に進んでいるか渡す関数
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
