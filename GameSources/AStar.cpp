/*!
@file AStar.cpp
@brief 経路探査処理
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	AStar::AStar() :
		m_unityMap(vector<vector<shared_ptr<Node>>>()),
		m_unityMapCSV(vector<vector<int>>()),//AStarMapのCSVデータ
		m_roopCount(0),//経路探査した回数を数える変数
		m_mapManager(weak_ptr<MapManager>())
	{
		//m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManaegr");
	}

	//デストラクタ
	AStar::~AStar()
	{

	}

	//経路探査処理
	vector<Vec3> AStar::RouteSearch(Vec3 startWPos,Vec3 goalWPos)
	{
		//初期化をする
		m_unityMap.clear();
		m_roopCount = 0.0f;
		vector<Vec2> aStarRood;//移動遷移

		//メンバ必須
		m_mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		auto mapManager = m_mapManager.lock();


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

			//無限ループしてしまったら
			if (m_roopCount >= 99)
			{
				//目的地を現在地にする
				goalPos = originPos;
				root = true;
			}

		}

		//ルートが見つかったらどう進めばいいかを伝える
		vector<Vec3> rootVec;
		//まず、目標地点であるPlayerのセル座標をワールド座標に変更する
		auto goalwolrdPos = m_mapManager.lock()->ConvertWorldMap(playerSelPos);
		rootVec.push_back(goalwolrdPos);
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
		m_aStarFirst = true;//AStarを更新したことを伝える
		return rootReverse;
	}


	//探しているセルがゴールからどれくらい遠いか確認する
	bool AStar::LookAround(shared_ptr<Node> parent, Vec2& goalPos)
	{
		m_roopCount++;//経路探索を何回しているか数える
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
					//目的地がマンホールなら前の移動地点を目的地にする
					if (goalPos == Vec2(lookX, lookY))
					{
						goalPos = originPos;
						return true;
					}
					continue;
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
	bool AStar::MoveActor(shared_ptr<Actor> actor, vector<Vec3> routePos,int& routeCount,float speed)
	{
		auto trans = actor->GetComponent<Transform>();
		auto pos = trans->GetPosition();

		if (routePos.size() >= 2 && routeCount == 0)
		{
			auto one = routePos[0];
			auto two = routePos[1];

			//現在地が１番目よりも、２番目の距離に近かったら１番目の移動処理を無視する
			if (abs(two.x - pos.x) + abs(two.z - pos.z) <= abs(two.x - one.x) + abs(two.z - one.z))
			{
				routeCount++;
			}

		}

		////目的地に移動したとみなす処理１
		//if (abs(pos.x - routePos[routeCount].x) <= 1.0f && abs(pos.z - routePos[routeCount].z) <= 1.0f)
		//{
		//	pos = routePos[routeCount];
		//	trans->SetPosition(pos);//所有者(Enemy)のポジションの更新
		//	if (routeCount < routePos.size() - 1)//この先に進まないといけない先がある場合
		//	{
		//		routeCount++;//目的地を変える
		//	}
		//}

		//目的地に移動したとみなす処理２複数敵が出ると瞬間移動してしまうバグ発生中
		if (routePos.size() - 1 >= routeCount + 1)//指定する配列数が配列範囲内であるか確認する
		{
			//ルートサーチを最初にした場合の移動方法の検索処理
			if (m_aStarFirst)
			{
				m_movePos = routePos[routeCount] - pos;//現在の座標と目的地の差を確認する
				m_aStarFirst = false;//ルートサーチの一番最初の状態ではなくなった
			}

			//数値を１やー１に固定化する 三項演算子は０の場合だと問題になるため使わない
			if (m_movePos.x > 0)//正の数なら
			{
				m_movePos.x = 1;//１にする
			}
			if (m_movePos.x < 0)//負の数なら
			{
				m_movePos.x = -1;//-１にする
			}
			if (m_movePos.z > 0)//正の数なら
			{
				m_movePos.z = 1;//１にする
			}
			if (m_movePos.z < 0)//負の数なら
			{
				m_movePos.z = -1;//-１にする
			}

			//次移動するのがx移動の場合
			if (routePos[routeCount].x - routePos[routeCount + 1].x != 0)
			{
				//今x移動中なら
				switch ((int)m_movePos.x)
				{
				case 1://右方向に進んでいるなら
					//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
					if (pos.x >= routePos[routeCount].x)
					{
						m_movePos = routePos[routeCount + 1] - routePos[routeCount];//新たにどう移動すればいいか計算する

						routeCount++;//目的地を変える
						m_targetPos = routePos[routeCount];//目的地を更新
					}
					break;
				case -1://左方向に進んでいるなら
					//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
					if (pos.x <= routePos[routeCount].x)
					{
						m_movePos = routePos[routeCount + 1] - routePos[routeCount];//新たにどう移動すればいいか計算する

						routeCount++;//目的地を変える
						m_targetPos = routePos[routeCount];//目的地を更新
					}
					break;
				default:
					break;
				}

				//今z移動中なら
				switch ((int)m_movePos.z)
				{
				case 1://上に進んでいるなら
					if (pos.z >= routePos[routeCount].z)
					{
						m_movePos = routePos[routeCount + 1] - routePos[routeCount];//新たにどう移動すればいいか計算する

						pos = routePos[routeCount];//瞬間移動

						routeCount++;//目的地を変える
						m_targetPos = routePos[routeCount];//目的地を更新
					}
					break;
				case -1://下に進んでいるなら
					if (pos.z <= routePos[routeCount].z)
					{
						m_movePos = routePos[routeCount + 1] - routePos[routeCount];//新たにどう移動すればいいか計算する

						pos = routePos[routeCount];//瞬間移動

						routeCount++;//目的地を変える
						m_targetPos = routePos[routeCount];//目的地を更新
					}
					break;
				default:
					break;
				}
			}
			else if (routePos[routeCount].z - routePos[routeCount + 1].z != 0)//次移動するのがz移動の場合
			{
				//今x移動中なら
				switch ((int)m_movePos.x)//xをどの方向に移動しているか確認する
				{
				case 1://右方向に進んでいるなら
					//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
					if (pos.x >= routePos[routeCount].x)
					{
						m_movePos = routePos[routeCount + 1] - routePos[routeCount];//新たにどう移動すればいいか計算する

						pos = routePos[routeCount];//瞬間移動

						routeCount++;//目的地を変える
						m_targetPos = routePos[routeCount];//目的地を更新
					}
					break;
				case -1://左方向に進んでいるなら
					//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
					if (pos.x <= routePos[routeCount].x)
					{
						m_movePos = routePos[routeCount + 1] - routePos[routeCount];//新たにどう移動すればいいか計算する

						pos = routePos[routeCount];//瞬間移動

						routeCount++;//目的地を変える
						m_targetPos = routePos[routeCount];//目的地を更新
					}
					break;
				default:
					break;
				}

				//今z移動中なら
				switch ((int)m_movePos.z)
				{
				case 1://上に進んでいるなら
					if (pos.z >= routePos[routeCount].z)
					{
						m_movePos = routePos[routeCount + 1] - routePos[routeCount];//新たにどう移動すればいいか計算する

						routeCount++;//目的地を変える
						m_targetPos = routePos[routeCount];//目的地を更新
					}
					break;
				case -1://下に進んでいるなら
					if (pos.z <= routePos[routeCount].z)
					{
						m_movePos = routePos[routeCount + 1] - routePos[routeCount];//新たにどう移動すればいいか計算する

						routeCount++;//目的地を変える
						m_targetPos = routePos[routeCount];//目的地を更新
					}
					break;
				default:
					break;
				}
			}
		}
		else//移動処理がこれで最後の場合
		{
			//数値を１やー１に固定化する 三項演算子は０の場合だと問題になるため使わない
			if (m_movePos.x > 0)//正の数なら
			{
				m_movePos.x = 1;//１にする
			}
			if (m_movePos.x < 0)//負の数なら
			{
				m_movePos.x = -1;//-１にする
			}
			if (m_movePos.z > 0)//正の数なら
			{
				m_movePos.z = 1;//１にする
			}
			if (m_movePos.z < 0)//負の数なら
			{
				m_movePos.z = -1;//-１にする
			}


			//今x移動中なら
			switch ((int)m_movePos.x)
			{
			case 1://右方向に進んでいるなら
				//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
				if (pos.x >= routePos[routeCount].x)
				{
					pos = routePos[routeCount];//瞬間移動
					trans->SetPosition(pos);
					return true;//移動が終わったことを伝える
				}
				break;
			case -1://左方向に進んでいるなら
				//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
				if (pos.x <= routePos[routeCount].x)
				{
					pos = routePos[routeCount];//瞬間移動
					trans->SetPosition(pos);
					return true;//移動が終わったことを伝える
				}
				break;
			default:
				break;
			}

			//今z移動中なら
			switch ((int)m_movePos.z)
			{
			case 1://上に進んでいるなら
				if (pos.z >= routePos[routeCount].z)
				{
					pos = routePos[routeCount];//瞬間移動
					trans->SetPosition(pos);
					return true;//移動が終わったことを伝える
				}
				break;
			case -1://下に進んでいるなら
				if (pos.z <= routePos[routeCount].z)
				{
					pos = routePos[routeCount];//瞬間移動
					trans->SetPosition(pos);
					return true;//移動が終わったことを伝える
				}
				break;
			default:
				break;
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

		return false;//目的地にたどり着けてなかったらfalse
	}

}
//end basecross
