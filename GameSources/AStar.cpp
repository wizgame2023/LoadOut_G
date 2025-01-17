/*!
@file AStar.cpp
@brief 経路探査処理
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	AStar::AStar(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
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


	//経路探査処理
	vector<Vec3> AStar::RouteSearch(Vec3 startWPos,Vec3 goalWPos)
	{
		//初期化をする
		m_unityMap.clear();

		vector<Vec2> aStarRood;//移動遷移

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");


		m_unityMapCSV = mapManager->GetUnityMap();//AStarマップ取得
		//vector<vector<shared_ptr<Node>>> aStarMap;//マップのノード配列
		vector<shared_ptr<Node>> aStarMapline;
		//AStarマップの配列と同じ配列の大きさのノードを作る
		for (int y = 0; y < m_unityMapCSV.size(); y++)
		{
			for (int x = 0; x < m_unityMapCSV[0].size(); x++)
			{
				aStarMapline.push_back(make_shared<Node>(Node(x, y, Status_None, 999, 999, 999, NULL)));
			}
			m_unityMap.push_back(aStarMapline);
			aStarMapline.clear();//リセット
		}
		auto test = 0;

		//初期位置を決める自分自身(Enemy)の現在地点
		auto enemySelPos = mapManager->ConvertSelMap(startWPos);//セルに変える
		auto enemyAStarPos = mapManager->ConvertUnityMap(enemySelPos);
		auto originPos = enemyAStarPos;
		m_unityMap[originPos.y][originPos.x]->Status = Status_Open;
		auto cost = 0;
		//ゴール地点(Player)	
		auto playerSelPos = mapManager->ConvertSelMap(goalWPos);
		auto playerASterPos = mapManager->ConvertUnityMap(playerSelPos);
		auto goalPos = playerASterPos;
		bool root = false;//経路が見つかったかどうか

		//一番最初のPlayerとの距離を確認する
		m_unityMap[originPos.y][originPos.x]->Status = Status_Open;
		auto lookCost = m_unityMap[originPos.y][originPos.x]->Cost = cost++;//コストの変数まだ作ってない
		auto lookHCost = m_unityMap[originPos.y][originPos.x]->HeuristicCost = abs(goalPos.x - originPos.x) + abs(goalPos.y - originPos.y);
		m_unityMap[originPos.y][originPos.x]->Score = lookCost + lookHCost;

		//経路が見つかるまでループする
		while (!root)
		{
			//周りに何があるか確認する //右左上下の床のセルに経路の評価する処理が出来てません 今、評価している場所が壁のセルになっています
			root = LookAround(m_unityMap[originPos.y][originPos.x], goalPos);

			//検索の中心点を探す
			auto openScore = 0;
			auto minScore = 999;
			for (auto map : m_unityMap)
			{
				for (auto mapline : map)
				{
					if (mapline->Status == Status_Open)//Open状態のスコアを取得する
					{
						openScore = mapline->Score;//スコアを取得
						if (openScore <= minScore)//最新の最少スコアよりも今のスコアの方が低ければ渡す
						{
							minScore = openScore;
							originPos.x = mapline->x;//検索の中心点を変更する
							originPos.y = mapline->y;//検索の中心点を変更する

						}
					}
				}
			}

		}

		//ルートが見つかったらどう進めばいいかを伝える
		vector<Vec3> rootVec;
		//まず、AStarの座標をワールド座標に戻す作業をする
		rootVec.push_back(goalWPos);
		auto parentSel = m_unityMap[goalPos.y][goalPos.x]->Parent;
		while (parentSel != NULL)
		{
			Vec2 AStarPos = Vec2(parentSel->x, parentSel->y);
			Vec2 SelPos = mapManager->ConvertU_S(AStarPos);
			Vec3 worldPos = mapManager->ConvertWorldMap(SelPos);
			rootVec.push_back(worldPos);
			parentSel = parentSel->Parent;
		}
		vector<Vec3> rootReverse;
		for (int i = rootVec.size() - 1; i >= 0(); i--)
		{
			rootReverse.push_back(rootVec[i]);
		}
		auto a = mapManager->ConvertUnityMap(Vec2(6, 6));
		return rootReverse;
	}


	//探しているセルがゴールからどれくらい遠いか確認する
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

				//読み込んだマップの場所が壁ががあるかないかみて周囲探索済みか見る
				if (m_unityMapCSV[lookY][lookX] == 3)
				{
					//応急処置　目的地がマンホールなら無視する
					if (goalPos != Vec2(lookX, lookY))
					{
						continue;
					}
				}


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

	//AStar用の移動処理
	void AStar::MoveActor(shared_ptr<Actor> actor, vector<Vec3> routePos,int& routeCount,float speed)
	{
		auto trans = actor->GetComponent<Transform>();
		auto pos = trans->GetPosition();

		if (routePos.size() > 2&&routeCount == 0)
		{
			auto one = routePos[0];
			auto two = routePos[1];
			//現在地が１番目よりも、２番目の距離に近かったら１番目の移動処理を無視する
			if (abs(two.x - pos.x) + abs(two.z - pos.z) <= abs(two.x - one.x) + abs(two.z - one.z))
			{
				routeCount++;
			}

		}

		//目的地に移動したとみなす
		if (abs(pos.x - routePos[routeCount].x) <= 1.0f && abs(pos.z - routePos[routeCount].z) <= 1.0f)
		{
			pos = routePos[routeCount];
			trans->SetPosition(pos);//所有者(Enemy)のポジションの更新
			if (routeCount < routePos.size() - 1)//この先に進まないといけない先がある場合
			{
				routeCount++;//目的地を変える
			}
		}
		auto delta = App::GetApp()->GetElapsedTime();
		Math math;	
		auto angle = math.GetAngle(pos, routePos[routeCount]);

		//移動処理
		pos.x += -sin(angle) * speed * delta;
		pos.z += -cos(angle) * speed * delta;
		trans->SetPosition(pos);		
		
		//回転を進む方向に合わせる
		auto quat = trans->GetQuaternion();
		quat = Quat(0.0f, sin((angle) / 2.0f), 0.0f, cos((angle) / 2.0f));
		trans->SetQuaternion(quat);

		//角度を渡す
		actor->SetAngle(angle + XMConvertToRadians(90.0f));

	}

}
//end basecross
