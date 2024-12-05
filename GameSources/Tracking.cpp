/*!
@file Tracking.cpp
@brief 追跡
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//追跡ステートの最初の処理
	void Tracking::OnStart()
	{
	}

	//追跡ステートの更新処理
	void Tracking::OnUpdate()
	{	
		//playerを追いかける処理
		auto app = App::GetApp;
		Math math;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のポジションを取得
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//playerを取得
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//playerのポジションを取得
		m_playerRay = m_Owner->GetPlayerRay();
		float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//所有者(Enemy)を中心にplayerの方向を計算
		m_ownerRot.y = rad;//playerの方向に向く

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		//Playerの位置をAStarの座標にする
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);//ワールド座標からセル座標にしてから
		auto playerAStarPos = mapManager->ConvertAStarMap(playerSelPos);//A*の座標に変える

		//A*の処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//プレイヤーのA*座標がが変わっていたらA*処理をもう一度やる
		if (playerAStarPos != m_beforPlayerAStar)
		{
			m_ownerPos;

			m_aStarMap.clear();
			m_roodCount = 0;
			m_beforPlayerAStar = playerAStarPos;
			//MoveCost();
			m_tagetRootPos = AStar();
		}
		//auto cost = MoveCost();
		//m_directionRad = math.GetAngle(m_ownerPos,cost);
		//目的地に移動したとみなす
		if (abs(m_ownerPos.x - m_tagetRootPos[m_roodCount].x) <= 0.5f && abs(m_ownerPos.z - m_tagetRootPos[m_roodCount].z) <= 0.5f)
		{
			m_ownerPos = m_tagetRootPos[m_roodCount];
			m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新
			if (m_roodCount < m_tagetRootPos.size())//この先に進まないといけない先がある場合
			{
				m_roodCount++;//目的地を変える
			}
		}
		m_directionRad = math.GetAngle(m_ownerPos,m_tagetRootPos[m_roodCount]);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//m_ownerRot.y = m_directionRad;

		m_ownerPos.x += -sin(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//playerに向かって移動
		m_ownerPos.z += -cos(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		m_ownerPos.y = 2.5f;
		
		auto CircleRange = math.GetCircleRange(60, m_ownerPos, m_playerPos);
		if (CircleRange)
		{
			m_time = 0;
		}
		else
		{
			m_time += app()->GetElapsedTime();
		}


		if (m_time >= 3)
		{
			m_Owner->ChangeState<Patrol>();
		}

		if (m_Owner->GetDistance(m_ownerPos, m_playerPos) < 7)
		{
			m_Owner->ChangeState<Attack>();
		}
		//auto a = m_posVec[m_count-1];

		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;
		auto AStar = mapMgr->GetAStarMap();
		auto sellPos = mapMgr->ConvertSelMap(pos);
		auto AStarPos = mapMgr->ConvertAStarMap(sellPos);

		m_trans->SetRotation(m_ownerRot);//所有者(Enemy)のローテーションの更新
		m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新
		m_Owner->SetAngle(m_directionRad + XM_PI * 0.5f);

		float deg = m_directionRad * 180 / XM_PI;//ラジアンをディグリーに変換（デバック用）

		//デバックログ
		auto scene = App::GetApp()->GetScene<Scene>();
		//wss /*<< L"プレイヤーPos.x : " << m_playerPos.x
		//	<< L"\nプレイヤーPos.z : " << m_playerPos.z*/
		//	<< L"\n敵の回転.y : " << m_ownerRot.y
		//	<< L"\n敵の回転（deg）" << deg
		//	<< L"\n敵のPos.x : " << m_ownerPos.x
		//	<< L"\n敵のPos.z : " << m_ownerPos.z
		//	<< L"\n右コスト : " << m_costRight
		//	<< L"\n左コスト : " << m_costLeft
		//	<< L"\n前コスト : " << m_costFod
		//	<< L"\n後コスト : " << m_costDown
		//	<< L"\nAStarPos.x : " << AStarPos.x
		//	<< L"\nAStarPos.y : " << AStarPos.y
		//	//<< L"\na.x : " << a.x
		//	//<< L"\na.y : "<<a.y
		//	//<<L"\na.z : "<<a.z
		//	<< endl;
		//scene->SetDebugString(wss.str());

		//デバック用/////////////////////////////////////////////////////////////
		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーの取得
		auto m_controler = inputDevice.GetControlerVec()[0];
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)//Bボタンを押したとき
		{
			mapManager->MapDataUpdate(pos, 5);//脱出状態にする

		}
		////////////////////////////////////////////////////////////////////////

	}
	//追跡ステートの最後の処理
	void Tracking::OnExit()
	{

	}

	void Tracking::nextSelLook(int right,int left,int up,int down,Vec2 enemyAStarPos,Vec2 playerAStarPos)
	{

		//隣の座標が1(つまり壁があれば通らない)処理を書く
		if (right == 1)
		{
			m_rightFlag = false;
			m_costRWall = 999;
		}
		//壁がなければ処理をする
		if (right == 0)
		{
			m_rightFlag = true;
			//右に行ってからのEnemyとPlayerの距離を測る
			auto distance = abs((enemyAStarPos.x + 1) - playerAStarPos.x) + abs(enemyAStarPos.y - playerAStarPos.y);
			auto addDistance = 1;//進んだ距離
			m_costRWall = distance;//コストを入れる

		}

		if (left == 1)
		{
			m_leftFlag = false;
			m_costLWall = 999;
		}
		if (left == 0)
		{
			m_leftFlag = true;
			//左に行ってからのEnemyとPlayerの距離を測る
			auto distance = abs((enemyAStarPos.x - 1) - playerAStarPos.x) + abs(enemyAStarPos.y - playerAStarPos.y);
			auto addDistance = 1;//進んだ距離
			m_costLWall = distance;//コストを入れる
		}

		if (up == 1)
		{
			m_upFlag = false;
			m_costFWall = 999;//コストを入れる
		}
		if (up == 0)
		{
			m_upFlag = true;
			//上に行ってからのEnemyとPlayerの距離を測る
			auto distance = abs(enemyAStarPos.x - playerAStarPos.x) + abs((enemyAStarPos.y - 1) - playerAStarPos.y);
			auto addDistance = 1;//進んだ距離
			m_costFWall = distance;//コストを入れる
		}

		if (down == 1)
		{
			m_downFlag = false;
			m_costDWall = 999;//コストを入れる
		}
		if (down == 0)
		{
			m_downFlag = true;
			//上に行ってからのEnemyとPlayerの距離を測る
			auto distance = abs(enemyAStarPos.x - playerAStarPos.x) + abs((enemyAStarPos.y + 1) - playerAStarPos.y);
			auto addDistance = 1;//進んだ距離
			m_costDWall = distance;//コストを入れる
		}
	}

	vector<Vec3> Tracking::AStar()
	{		
		vector<Vec2> aStarRood;//移動遷移

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		m_aStarMapCSV = mapManager->GetAStarMap();//AStarマップ取得
		//vector<vector<shared_ptr<Node>>> aStarMap;//マップのノード配列
		vector<shared_ptr<Node>> aStarMapline;
		//AStarマップの配列と同じ配列の大きさのノードを作る
		for (int y=0; y < m_aStarMapCSV.size(); y++)
		{
			for (int x=0; x < m_aStarMapCSV[0].size(); x++)
			{
				aStarMapline.push_back(make_shared<Node>(Node(x, y, Status_None, 999, 999, 999, NULL)));
			}
			m_aStarMap.push_back(aStarMapline);
			aStarMapline.clear();//リセット
		}
		auto test=0;
		
		//初期位置を決める自分自身(Enemy)の現在地点
		auto enemySelPos = mapManager->ConvertSelMap(m_ownerPos);//セルに変える
		auto enemyAStarPos = mapManager->ConvertAStarMap(enemySelPos);
		auto originPos = enemyAStarPos;
		m_aStarMap[originPos.y][originPos.x]->Status = Status_Open;
		auto cost = 1;
		//ゴール地点(Player)
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);
		auto playerASterPos = mapManager->ConvertAStarMap(playerSelPos);
		auto goalPos = playerASterPos;
		bool root = false;//経路が見つかったかどうか

		//経路が見つかるまでループする
		while (!root)
		{				
			//周りに何があるか確認する //右左上下の床のセルに経路の評価する処理が出来てません 今、評価している場所が壁のセルになっています
			root = LookAround(m_aStarMap[originPos.y][originPos.x],goalPos);
	
			//検索の中心点を探す
			auto openScore = 0;
			auto minScore = 999;
			for (auto map : m_aStarMap)
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


			auto a = 0;
			//m_aStarMap[originPos.y][originPos.x]->Status = Status_Closed;//閉じる
			//cost++;
		}

		//ルートが見つかったらどう進めばいいかを伝える
		vector<Vec3> rootVec;
		//まず、AStarの座標をワールド座標に戻す作業をする
		rootVec.push_back(m_playerPos);
		auto parentSel = m_aStarMap[goalPos.y][goalPos.x]->Parent;
		while (parentSel != NULL)
		{
			Vec2 AStarPos = Vec2(parentSel->x, parentSel->y);
			Vec2 SelPos = mapManager->ConvertA_S(AStarPos);
			Vec3 worldPos = mapManager->ConvertWorldMap(SelPos);
			rootVec.push_back(worldPos);
			parentSel = parentSel->Parent;
		}
		vector<Vec3> rootReverse;
		for (int i = rootVec.size()-1; i >= 0(); i--)
		{
			rootReverse.push_back(rootVec[i]);
		}
		m_ownerPos;
		return rootReverse;

	}

	bool Tracking::LookAround(shared_ptr<Node> parent,Vec2 goalPos)
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

				//確認する座標が親座標から見て左右上下以外なら確認しない
				if (pushy == 0 && pushx == 0 || pushy != 0 && pushx != 0) continue;	
				//読み込んだマップの場所が壁ががあるかないかみて周囲探索済みか見る
				if (m_aStarMapCSV[lookY][lookX] == 1 || m_aStarMap[lookY][lookX]->Status == Status_Closed) continue;
				//壁を確認したので床のマスに対して評価する
				lookX = (pushx * 2) + originPos.x;
				lookY = (pushy * 2) + originPos.y;	
				//配列の範囲外なら確認しない	
				if ((lookY <= 0 || lookY >= (m_aStarMap.size() - 1)) || (lookX <= 0 || lookX >= (m_aStarMap.size() - 1))) continue;

				if (lookX < 0||lookX>m_aStarMap.size()-1)
				{
					auto test=0;
				}
				if (lookY < 0||lookY>m_aStarMap.size()-1)
				{
					auto test = 0;
				}

				if (m_aStarMap[lookY][lookX]->Status == Status_None)//探索したことがないなら
				{
					m_aStarMap[lookY][lookX]->Status = Status_Open;
					auto lookCost = m_aStarMap[lookY][lookX]->Cost = cost;//コストの変数まだ作ってない
					auto lookHCost = m_aStarMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - lookX) + abs(goalPos.y - lookY);
					m_aStarMap[lookY][lookX]->Score = lookCost + lookHCost;
					m_aStarMap[lookY][lookX]->Parent = m_aStarMap[originPos.y][originPos.x];
				}
				if (m_aStarMap[lookY][lookX]->Status == Status_Open)//探索済みなら
				{
					auto Cost = m_aStarMap[lookY][lookX]->Cost = cost;
					m_aStarMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - (lookX)) + abs(goalPos.y - (lookY));
					auto score = m_aStarMap[lookY][lookX]->Score = m_aStarMap[lookY][lookX]->Cost + m_aStarMap[lookY][lookX]->HeuristicCost;

					if (m_aStarMap[lookY][lookX]->Score > score)//スコアが前よりも少なかったら
					{
						m_aStarMap[lookY][lookX]->Status = Status_Open;
						m_aStarMap[lookY][lookX]->Cost = cost;
						m_aStarMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - (lookX)) + abs(goalPos.y - (lookY));
						m_aStarMap[lookY][lookX]->Score = score;
						m_aStarMap[lookY][lookX]->Parent = m_aStarMap[originPos.y][originPos.x];
					}
				}

				if (m_aStarMap[lookY][lookX]->HeuristicCost == 0)
				{
					return true;
				}
			}
		}

		//周囲探索が終わったならステータスがOpenからClosedへ変わる
		m_aStarMap[originPos.y][originPos.x]->Status = Status_Closed;

		return false;
	}

	//Vec3 Tracking::MoveCost()
	//{
	//	Math math;
	//	auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
	//	Vec3 pos = m_ownerPos;
	//	Vec3 playerPos = m_playerPos;
	//	Vec3 direction;
	//	auto AStar = mapMgr->GetAStarMap();//A*のマップ配列取得
	//	auto sellPos = mapMgr->ConvertSelMap(pos);//Enemyの位置をセル座標に変更
	//	auto AStarPos = mapMgr->ConvertAStarMap(sellPos);//セル座標からAStar座標に変更

	//	auto rightAStar = AStar[AStarPos.y][AStarPos.x + 1];
	//	auto leftAStar = AStar[AStarPos.y][AStarPos.x - 1];
	//	auto fodAStar = AStar[AStarPos.y - 1][AStarPos.x];
	//	auto downAStar = AStar[AStarPos.y + 1][AStarPos.x];


	//	auto rightASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x + 2, AStarPos.y));
	//	auto leftASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x - 2, AStarPos.y));
	//	auto fodASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x, AStarPos.y - 2));
	//	auto downASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x, AStarPos.y + 2));


	//	auto rightWPos = mapMgr->ConvertWorldMap(rightASPos);
	//	auto leftWPos = mapMgr->ConvertWorldMap(leftASPos);
	//	auto fodWPos = mapMgr->ConvertWorldMap(fodASPos);
	//	auto downWPos = mapMgr->ConvertWorldMap(downASPos);


	//	auto rightVec = math.GetDistance(rightWPos, m_playerPos);
	//	auto liftVec = math.GetDistance(leftWPos, m_playerPos);
	//	auto fodVec = math.GetDistance(fodWPos, m_playerPos);
	//	auto downVec = math.GetDistance(downWPos, m_playerPos);


	//	if (rightAStar == 1)
	//	{
	//		m_costRWall += 1000;
	//	}
	//	else if(rightAStar == 0)
	//	{
	//		m_costRWall = 0;
	//	}
	//	if (leftAStar == 1)
	//	{
	//		m_costLWall = 1000;
	//	}
	//	else if (leftAStar == 0)
	//	{
	//		m_costLWall = 0;
	//	}
	//	if (fodAStar == 1)
	//	{
	//		m_costFWall += 1000;
	//	}
	//	else if (fodAStar == 0)
	//	{
	//		m_costFWall = 0;
	//	}
	//	if (downAStar == 1)
	//	{
	//		m_costDWall += 1000;
	//	}
	//	else if (downAStar == 0)
	//	{
	//		m_costDWall = 0;
	//	}



	//	int min_value[] =
	//	{
	//		{rightVec + m_costRight+m_costRWall},
	//		{liftVec + m_costLeft+m_costLWall},
	//		{fodVec + m_costFod+m_costFWall},
	//		{downVec + m_costDown+m_costDWall},
	//	};
	//	int min = min_value[0];
	//	for (int i = 0; i < 4; i++)
	//	{
	//		if (min_value[i] < min)
	//		{
	//			min = min_value[i];
	//		}
	//	}

	//	if (min == min_value[0])
	//	{
	//		direction = rightWPos;
	//	}
	//	if (min == min_value[1])
	//	{
	//		direction = leftWPos;
	//	}
	//	if (min == min_value[2])
	//	{
	//		direction = fodWPos;
	//	}
	//	if (min == min_value[3])
	//	{
	//		direction = downWPos;
	//	}
	//	while (direction != m_playerPos)
	//	{
	//		if (m_count >= 0)
	//		{
	//			//m_posVec[m_count] = direction;
	//			m_posVec.push_back(direction);

	//		}

	//		if (m_count > 0)
	//		{
	//			if (playerPos==m_playerPos)
	//			{
	//				if (rightWPos == m_posVec[m_count - 1])
	//				{
	//					m_costLeft += 100;
	//					m_costRight = 0;
	//				}
	//				if (leftWPos == m_posVec[m_count - 1])
	//				{
	//					m_costRight += 100;
	//					m_costLeft = 0;
	//				}
	//				if (fodWPos == m_posVec[m_count - 1])
	//				{
	//					m_costDown += 1;
	//					m_costFod = 0;
	//				}
	//				if (downWPos == m_posVec[m_count - 1])
	//				{
	//					m_costFod += 1;
	//					m_costDown = 0;
	//				}
	//			}
	//		}
	//		if (m_costRight < 0)
	//		{
	//			m_costRight = 0;
	//		}
	//		if (m_costRight > 100)
	//		{
	//			m_costRight = 100;
	//		}
	//		if (m_costLeft < 0)
	//		{
	//			m_costLeft = 0;
	//		}
	//		if (m_costLeft > 100)
	//		{
	//			m_costLeft = 100;
	//		}
	//		if(m_costFod < 0)
	//		{
	//			m_costFod = 0;
	//		}
	//		if (m_costFod > 100)
	//		{
	//			m_costFod = 100;
	//		}
	//		if (m_costDown < 0)
	//		{
	//			m_costDown = 0;
	//		}
	//		if (m_costDown > 100)
	//		{
	//			m_costDown = 100;
	//		}
	//		m_count++;
	//		
	//		return m_posVec[m_count - 1];
	//	}

	//}

	

}

//end basecross
