/*!
@file AStar.h
@brief 経路探査処理
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class AStar :GameObject
	{
	private:
		Vec3 m_startPos;//最初のポジション
		Vec3 m_goalPos;//ゴールするポジション
	public:
		AStar(shared_ptr<Stage>& stagePtr,Vec3 startPos,Vec3 goalPos);//コンストラクタ
		~AStar();//デストラクタ

		void OnCreate() override;//作成
		void OnUpdate() override;//更新
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
