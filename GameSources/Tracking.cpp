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
		//float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//所有者(Enemy)を中心にplayerの方向を計算
		//m_ownerRot.y = rad;//playerの方向に向く


		MoveCost();
		//auto cost = MoveCost();
		//m_directionRad = math.GetAngle(m_ownerPos,cost);
		m_directionRad = math.GetAngle(m_ownerPos,m_tagetPos);

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
			//m_time += app()->GetElapsedTime();
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
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss /*<< L"プレイヤーPos.x : " << m_playerPos.x
			//<< L"\nプレイヤーPos.z : " << m_playerPos.z*/
			//<< L"\n敵の回転.y : " << m_ownerRot.y
			//<< L"\n敵の回転（deg）" << deg
			//<< L"\n敵のPos.x : " << m_ownerPos.x
			//<< L"\n敵のPos.z : " << m_ownerPos.z
			//<< L"\n右コスト : " << m_costRight
			//<< L"\n左コスト : " << m_costLeft
			//<< L"\n前コスト : " << m_costFod
			//<< L"\n後コスト : " << m_costDown
			//<< L"\nAStarPos.x : " << AStarPos.x
			//<< L"\nAStarPos.y : " << AStarPos.y
			//<< L"\na.x : " << a.x
			//<< L"\na.y : "<<a.y
			//<<L"\na.z : "<<a.z
			//<< endl;
		//scene->SetDebugString(wss.str());
	}
	//追跡ステートの最後の処理
	void Tracking::OnExit()
	{

	}

	////ここでA*の処理をします
	Vec3 Tracking::MoveCost()
	{
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;

		auto aStarMap = mapManager->GetAStarMap();//Aスター取得
		//if()

		//自分自身の位置をAStarの座標にする
		auto EnemySelPos = mapManager->ConvertSelMap(m_ownerPos);
		auto EnemyAStarPos = mapManager->ConvertAStarMap(EnemySelPos);

		auto test = mapManager->ConvertA_S(EnemyAStarPos);
		auto test2 = mapManager->ConvertWorldMap(test);

		//Playerの位置をAStarの座標にする
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);//ワールド座標からセル座標にしてから
		auto playerAStarPos = mapManager->ConvertAStarMap(playerSelPos);//A*の座標に変える

		aStarMap[playerAStarPos.y][playerAStarPos.x] = 2;//AMapにここが目的地と伝える
		auto a = 0;

		//チェックする配列
		//vector<Vec2> charkVec;
		//vector<Vec2> direction;//方向

		////右の座標
		auto right = aStarMap[EnemyAStarPos.y][EnemyAStarPos.x + 1];//後々、個々の引数はEnemyStarPosではなく調べたい座標の変数に変える
		//direction.push_back(Vec2(EnemyAStarPos.y, EnemyAStarPos.x + 1));//AStarの座標を取得
		////左の座標
		auto left = aStarMap[EnemyAStarPos.y][EnemyAStarPos.x - 1];
		//direction.push_back(Vec2(EnemyAStarPos.y, EnemyAStarPos.x - 1));//AStarの座標を取得
		////下の座標
		auto down = aStarMap[EnemyAStarPos.y + 1][EnemyAStarPos.x];
		//direction.push_back(Vec2(EnemyAStarPos.y+1, EnemyAStarPos.x));//AStarの座標を取得
		////上の座標
		auto up = aStarMap[EnemyAStarPos.y - 1][EnemyAStarPos.x];
		//direction.push_back(Vec2(EnemyAStarPos.y - 1, EnemyAStarPos.x));//AStarの座標を取得


		auto m_rightWall = false;
		auto m_leftWall = false;
		auto m_downWall = false;
		auto m_upWall = false;

		//隣の座標が1(つまり壁があれば通らない)
		if (right == 1)
		{
			m_rightWall = true;//隣に壁があったら処理をしない
			m_costRWall = 999;
		}
		//壁がなければ処理をする
		if (right == 0)
		{
			m_rightWall = false;
			//右に行ってからのEnemyとPlayerの距離を測る
			auto distance = abs((EnemyAStarPos.x+1) - playerAStarPos.x) + abs(EnemyAStarPos.y - playerAStarPos.y);
			auto addDistance = 1;//進んだ距離
			m_costRWall = distance;//コストを入れる

		}

		if (left == 1)
		{
			m_leftWall = true;
			m_costLWall = 999;
		}
		if (left == 0)
		{
			m_leftWall = false;
			//左に行ってからのEnemyとPlayerの距離を測る
			auto distance = abs((EnemyAStarPos.x-1) - playerAStarPos.x) + abs(EnemyAStarPos.y - playerAStarPos.y);
			auto addDistance = 1;//進んだ距離
			m_costLWall = distance;//コストを入れる
		}

		if (up == 1)
		{
			m_upWall = true;
			m_costFWall = 999;//コストを入れる
		}
		if (up == 0)
		{
			m_upWall = false;
			//上に行ってからのEnemyとPlayerの距離を測る
			auto distance = abs(EnemyAStarPos.x - playerAStarPos.x) + abs((EnemyAStarPos.y-1) - playerAStarPos.y);
			auto addDistance = 1;//進んだ距離
			m_costFWall = distance;//コストを入れる
		}

		if (down == 1)
		{
			m_downWall = true;
			m_costDWall = 999;//コストを入れる
		}
		if (down == 0)
		{
			m_downWall = false;
			//上に行ってからのEnemyとPlayerの距離を測る
			auto distance = abs(EnemyAStarPos.x - playerAStarPos.x) + abs((EnemyAStarPos.y + 1) - playerAStarPos.y);
			auto addDistance = 1;//進んだ距離
			m_costDWall = distance;//コストを入れる
		}

		vector<int> cost =
		{
			m_costLWall,//左
			m_costRWall,//右
			m_costFWall,//上
			m_costDWall//下
		};

		auto minCost = 999;//一番低いコストを保管する
		vector<int> minDirection;//方向を管理する変数
		//コストが一番低い方向を調べる
		for (int i = 0; i < cost.size(); i++)
		{
			auto nowCost = cost[i];//現在のコスト
			if (minCost > nowCost)//今のコストが最小のコストよりも低いとき
			{
				minCost = nowCost;//最小コストを更新する
				minDirection.clear();//最小コストが更新されたので配列リセット
				minDirection.push_back(i);//これで一番低いコストの方向を確認する
			}
			else if (minCost == nowCost)//今のコストが最小のコストと同じ時
			{
				minDirection.push_back(i);//一番低いコストの方向を追加する
			}
		}

		//その後に一番低いコストの方向に進む処理をかく、もし一番低いコストの方向方向が複数あれば同時にやる
		//まずは一番低いコストの方向が１つだけの処理を書く、その後に関数化させて複数処理をする 複数処理できそう
		for (int i = 0; i < minDirection.size(); i++)
		{
			//もし、方向が左だったら
			if (minDirection[i] == 0)
			{
				auto AStarPos(Vec2(EnemyAStarPos.x-2, EnemyAStarPos.y));//AStarの座標を取得
				auto SelPos = mapManager->ConvertA_S(AStarPos);//Sel座標に変換
				m_tagetPos = mapManager->ConvertWorldMap(SelPos);//ワールド座標に変換
				auto a = 0;

			}
			//もし、方向が右だったら
			if (minDirection[i] == 1)
			{
				auto AStarPos(Vec2(EnemyAStarPos.x+2, EnemyAStarPos.y));//AStarの座標を取得
				auto SelPos = mapManager->ConvertA_S(AStarPos);//Sel座標に変換
				m_tagetPos = mapManager->ConvertWorldMap(SelPos);//ワールド座標に変換
				auto a = 0;
			}
			//もし、方向が上だったら
			if (minDirection[i] == 2)
			{
				auto AStarPos(Vec2(EnemyAStarPos.x, EnemyAStarPos.y-2));//AStarの座標を取得
				auto SelPos = mapManager->ConvertA_S(AStarPos);//Sel座標に変換
				m_tagetPos = mapManager->ConvertWorldMap(SelPos);//ワールド座標に変換
				auto a = 0;

			}
			//もし、方向が下だったら
			if (minDirection[i] == 3)
			{
				auto AStarPos(Vec2(EnemyAStarPos.x, EnemyAStarPos.y+2));//AStarの座標を取得
				auto SelPos = mapManager->ConvertA_S(AStarPos);//Sel座標に変換
				m_tagetPos = mapManager->ConvertWorldMap(SelPos);//ワールド座標に変換
				auto a = 0;

			}
		}





		//隣のマスが壁があるかどうか確認する
		//for (int i = -1; i <= 1; i += 2)
		//{
		//	//m_rightCost = 0;
		//}

		return Vec3(0,0,0);
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
