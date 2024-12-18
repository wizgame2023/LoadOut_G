/*!
@file AStar.cpp
@brief 経路探査処理
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	AStar::AStar(shared_ptr<Stage>& stagePtr,Vec3 startPos,Vec3 goalPos) :
		GameObject(stagePtr),
		m_startPos(startPos),
		m_goalPos(goalPos)
	{

	}

	//デストラクタ
	AStar::~AStar()
	{

	}

	//作成
	void AStar::OnCreate()
	{

	}

	//更新
	void AStar::OnUpdate()
	{

	}

	bool AStar::LookAround(shared_ptr<Node> parent, Vec2 goalPos)
	{
		Vec2 originPos = Vec2(parent->x, parent->y);
		auto cost = parent->Parent ? parent->Cost + 1 : 1;//コストの計算

		//右左上下に壁があるかどうかを見る
		for (int pushy = -1; pushy < 2; pushy++)
		{
			for (int pushx = -1; pushx < 2; pushx++)
			{
				int lookX = pushx + originPos.x;
				int lookY = pushy + originPos.y;
				auto test = m_unityMap.size();

				//確認する座標が親座標から見て左右上下以外なら確認しない
				if (pushy == 0 && pushx == 0 || pushy != 0 && pushx != 0) continue;
				//配列の範囲外なら確認しない
				if ((lookY < 0 || lookY >= (m_unityMap.size())) || (lookX < 0 || lookX >= (m_unityMap.size()))) continue;
				//読み込んだマップの場所が壁ががあるかないかみて周囲探索済みか見る
				if (m_unityMapCSV[lookY][lookX] == 1 || m_unityMap[lookY][lookX]->Status == Status_Closed) continue;

				//壁を確認したので床のマスに対して評価する//////////////////////////////////////////////////////////////////////
				lookX = (pushx * 2) + originPos.x;
				lookY = (pushy * 2) + originPos.y;

				if (lookX < 0 || lookX>m_unityMap.size() - 1)
				{
					auto test = 0;
				}
				if (lookY < 0 || lookY>m_unityMap.size() - 1)
				{
					auto test = 0;
				}

				if (m_unityMap[lookY][lookX]->Status == Status_None)//探索したことがないなら
				{

					m_unityMap[lookY][lookX]->Status = Status_Open;
					auto lookCost = m_unityMap[lookY][lookX]->Cost = cost;//コストの変数まだ作ってない
					auto lookHCost = m_unityMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - lookX) + abs(goalPos.y - lookY);
					m_unityMap[lookY][lookX]->Score = lookCost + lookHCost;
					m_unityMap[lookY][lookX]->Parent = m_unityMap[originPos.y][originPos.x];
				}
				if (m_unityMap[lookY][lookX]->Status == Status_Open)//探索済みなら
				{
					auto Cost = m_unityMap[lookY][lookX]->Cost = cost;
					m_unityMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - (lookX)) + abs(goalPos.y - (lookY));
					auto score = m_unityMap[lookY][lookX]->Score = m_unityMap[lookY][lookX]->Cost + m_unityMap[lookY][lookX]->HeuristicCost;

					if (m_unityMap[lookY][lookX]->Score > score)//スコアが前よりも少なかったら
					{
						m_unityMap[lookY][lookX]->Status = Status_Open;
						m_unityMap[lookY][lookX]->Cost = cost;
						m_unityMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - (lookX)) + abs(goalPos.y - (lookY));
						m_unityMap[lookY][lookX]->Score = score;
						m_unityMap[lookY][lookX]->Parent = m_unityMap[originPos.y][originPos.x];
					}
				}



			}
		}

		//マップのすべてを見てPlayerの距離が０なところがあるか確認する
		for (auto map : m_unityMap)
		{
			for (auto mapline : map)
			{
				if (mapline->HeuristicCost == 0)
				{
					return true;
				}
			}
		}

		//周囲探索が終わったならステータスがOpenからClosedへ変わる
		m_unityMap[originPos.y][originPos.x]->Status = Status_Closed;

		return false;
	}


}
//end basecross
