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
		auto app = App::GetApp;
		float delta = App::GetApp()->GetElapsedTime();
		Math math;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のポジションを取得

		m_anger = m_Owner->GetAnger();//怒り値を取得
		//怒り値によってトラッキング時のスピードを変更する
		AngerSpeed(m_anger);

		AStarMove();//Aスター処理

		//m_targetPos = m_tagetRootPos[m_roodCount];//現在の目的地

		//移動処理
		m_directionRad = math.GetAngle(m_ownerPos, m_tagetRootPos[m_roodCount]);

		m_ownerRot.y = m_directionRad;

		m_ownerPos.x += -sin(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//playerに向かって移動
		m_ownerPos.z += -cos(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		
		//移動更新
		m_trans->SetRotation(m_ownerRot);//所有者(Enemy)のローテーションの更新
		m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新
		m_Owner->SetAngle(m_directionRad + XM_PI * 0.5f);
	}

	//追跡ステートの更新処理
	void Tracking::OnUpdate()
	{	
		//playerを追いかける処理
		auto app = App::GetApp;
		float delta = App::GetApp()->GetElapsedTime();
		m_delta = App::GetApp()->GetElapsedTime();

		Math math;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のポジションを取得
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//playerを取得
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//playerのポジションを取得
		m_playerRay = m_Owner->GetPlayerRay();
		//float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//所有者(Enemy)を中心にplayerの方向を計算
		//m_ownerRot.y = rad;//playerの方向に向く

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		//Playerの位置をAStarの座標にする
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);//ワールド座標からセル座標にしてから
		auto playerAStarPos = mapManager->ConvertUnityMap(playerSelPos);//A*の座標に変える
		//A*の処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//m_aStar = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<AStar>(L"AStar");//AStar処理取得
		//プレイヤーのA*座標がが変わっていたらA*処理をもう一度やる
		bool aStarStart = false;//AStarの再計算処理がされているか見る変数
		if (playerAStarPos != m_beforPlayerUnity)
		{
			aStarStart = true;//AStarの再計算がされている
			AStarMove();
		}
		//一定時間たったらA*処理をする
		m_aStarTime += delta;
		if (m_aStarTime >= 0.3f)
		{
			m_aStarTime = 0.0f;//タイムリセット
			aStarStart = true;//AStarの再計算がされている
			AStarMove();
		}
		
		//auto cost = MoveCost();
		//m_directionRad = math.GetAngle(m_ownerPos,cost);
		//目的地に移動したとみなす
		//if (abs(m_ownerPos.x - m_tagetRootPos[m_roodCount].x) <= 1.0f && abs(m_ownerPos.z - m_tagetRootPos[m_roodCount].z) <= 1.0f)
		//{
		//	m_ownerPos = m_tagetRootPos[m_roodCount];
		//	m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新 
		//	if (m_roodCount < m_tagetRootPos.size()-1)//この先に進まないといけない先がある場合
		//	{
		//		m_roodCount++;//目的地を変える
		//	}
		//}
		
		////目的地に移動したとみなす処理２
		//if (m_tagetRootPos.size() - 1 >= m_roodCount + 1)//指定する配列数が配列範囲内であるか確認する
		//{
		//	//ルートサーチを最初にした場合の移動方法の検索処理
		//	if (aStarStart)
		//	{
		//		m_movePos = m_tagetRootPos[m_roodCount] - m_ownerPos;//現在の座標と目的地の差を確認する
		//		aStarStart = false;//ルートサーチの一番最初の状態ではなくなった
		//	}

		//	//数値を１やー１に固定化する 三項演算子は０の場合だと問題になるため使わない
		//	if (m_movePos.x > 0)//正の数なら
		//	{
		//		m_movePos.x = 1;//１にする
		//	}
		//	if (m_movePos.x < 0)//負の数なら
		//	{
		//		m_movePos.x = -1;//-１にする
		//	}
		//	if (m_movePos.z > 0)//正の数なら
		//	{
		//		m_movePos.z = 1;//１にする
		//	}
		//	if (m_movePos.z < 0)//負の数なら
		//	{
		//		m_movePos.z = -1;//-１にする
		//	}

		//	//次移動するのがx移動の場合
		//	if (m_tagetRootPos[m_roodCount].x - m_tagetRootPos[m_roodCount + 1].x != 0)
		//	{
		//		//今x移動中なら
		//		switch ((int)m_movePos.x)
		//		{
		//		case 1://右方向に進んでいるなら
		//			//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
		//			if (m_ownerPos.x >= m_tagetRootPos[m_roodCount].x)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//新たにどう移動すればいいか計算する

		//				m_roodCount++;//目的地を変える
		//				m_targetPos = m_tagetRootPos[m_roodCount];//目的地を更新
		//			}
		//			break;
		//		case -1://左方向に進んでいるなら
		//			//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
		//			if (m_ownerPos.x <= m_tagetRootPos[m_roodCount].x)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//新たにどう移動すればいいか計算する

		//				m_roodCount++;//目的地を変える
		//				m_targetPos = m_tagetRootPos[m_roodCount];//目的地を更新
		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//		//今z移動中なら
		//		switch ((int)m_movePos.z)
		//		{
		//		case 1://上に進んでいるなら
		//			if (m_ownerPos.z >= m_tagetRootPos[m_roodCount].z)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//新たにどう移動すればいいか計算する

		//				m_ownerPos = m_tagetRootPos[m_roodCount];//瞬間移動

		//				m_roodCount++;//目的地を変える
		//				m_targetPos = m_tagetRootPos[m_roodCount];//目的地を更新
		//			}
		//			break;
		//		case -1://下に進んでいるなら
		//			if (m_ownerPos.z <= m_tagetRootPos[m_roodCount].z)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//新たにどう移動すればいいか計算する

		//				m_ownerPos = m_tagetRootPos[m_roodCount];//瞬間移動

		//				m_roodCount++;//目的地を変える
		//				m_targetPos = m_tagetRootPos[m_roodCount];//目的地を更新
		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//	}
		//	else if (m_tagetRootPos[m_roodCount].z - m_tagetRootPos[m_roodCount + 1].z != 0)//次移動するのがz移動の場合
		//	{
		//		//今x移動中なら
		//		switch ((int)m_movePos.x)//xをどの方向に移動しているか確認する
		//		{
		//		case 1://右方向に進んでいるなら

		//			//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
		//			if (m_ownerPos.x >= m_tagetRootPos[m_roodCount].x)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//新たにどう移動すればいいか計算する

		//				m_ownerPos = m_tagetRootPos[m_roodCount];//瞬間移動

		//				m_roodCount++;//目的地を変える
		//				m_targetPos = m_tagetRootPos[m_roodCount];//目的地を更新
		//			}
		//			break;
		//		case -1://左方向に進んでいるなら

		//			//今いる位置が目的地を通り過ぎた場合目的地に移動したとみなし次の目的地に変更する
		//			if (m_ownerPos.x <= m_tagetRootPos[m_roodCount].x)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//新たにどう移動すればいいか計算する

		//				m_ownerPos = m_tagetRootPos[m_roodCount];//瞬間移動

		//				m_roodCount++;//目的地を変える
		//				m_targetPos = m_tagetRootPos[m_roodCount];//目的地を更新
		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//		//今z移動中なら
		//		switch ((int)m_movePos.z)
		//		{
		//		case 1://上に進んでいるなら
		//			if (m_ownerPos.z >= m_tagetRootPos[m_roodCount].z)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//新たにどう移動すればいいか計算する

		//				m_roodCount++;//目的地を変える
		//				m_targetPos = m_tagetRootPos[m_roodCount];//目的地を更新
		//			}
		//			break;
		//		case -1://下に進んでいるなら
		//			if (m_ownerPos.z <= m_tagetRootPos[m_roodCount].z)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//新たにどう移動すればいいか計算する

		//				m_roodCount++;//目的地を変える
		//				m_targetPos = m_tagetRootPos[m_roodCount];//目的地を更新
		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//	}
		//}

		//m_directionRad = math.GetAngle(m_ownerPos,m_tagetRootPos[m_roodCount]);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//m_ownerRot.y = m_directionRad;
		//auto speedtest = m_Owner->GetSpeed();
		//m_ownerPos.x += -sin(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//playerに向かって移動
		//m_ownerPos.z += -cos(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		
		//AStarを使った移動処理
		MoveActor(m_Owner, m_tagetRootPos, m_roodCount, m_Owner->GetSpeed());
		
		auto CircleRange = math.GetCircleRange(40, m_ownerPos, m_playerPos);
		if (CircleRange)
		{
			m_time = 0;
		}
		else
		{
			m_time += app()->GetElapsedTime();
		}


		if (m_time >= 1)
		{
			//Playerを見失った処理に変更
			m_Owner->ChangeState<TargetLost>();
		}

		if (m_Owner->GetDistance(m_ownerPos, m_playerPos) < 7)
		{
			m_Owner->ChangeState<Attack>();
		}
		//auto a = m_posVec[m_count-1];

		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;
		auto RouteSearch = mapMgr->GetUnityMap();
		auto sellPos = mapMgr->ConvertSelMap(pos);
		auto AStarPos = mapMgr->ConvertUnityMap(sellPos);

		//m_trans->SetRotation(m_ownerRot);//所有者(Enemy)のローテーションの更新
		//m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新
		//m_Owner->SetAngle(m_directionRad + XM_PI * 0.5f);

		float deg = m_directionRad * 180 / XM_PI;//ラジアンをディグリーに変換（デバック用）

		//ラッシュの処理
		auto ability = m_Owner->GetAbility();

		if (ability==rush)
		{			
			if (m_rushMoveFlag == false)
			{
				m_rushMoveFlag = RushMoveChack(m_ownerPos, 2);
			}

			m_waitTime+= app()->GetElapsedTime();
			RushMove(m_rushMoveFlag);

		}

		////デバックログ
		//auto scene = App::GetApp()->GetScene<Scene>();
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


	}
	//追跡ステートの最後の処理
	void Tracking::OnExit()
	{

	}

	//AStarを使う移動処理
	void Tracking::AStarMove()
	{
		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		//Playerの位置をAStarの座標にする
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);//ワールド座標からセル座標にしてから
		auto playerAStarPos = mapManager->ConvertUnityMap(playerSelPos);//A*の座標に変える
		m_unityMap.clear();
		m_roodCount = 0;
		m_beforPlayerUnity = playerAStarPos;
		m_tagetRootPos = RouteSearch(m_ownerPos, m_playerPos);//経路探索
		if (m_tagetRootPos.size() >= 2)
		{
			auto one = m_tagetRootPos[0];
			auto two = m_tagetRootPos[1];
			//現在地が１番目よりも、２番目の距離に近かったら１番目の移動処理を無視する
			if (abs(two.x - m_ownerPos.x) + abs(two.z - m_ownerPos.z) <= abs(two.x - one.x) + abs(two.z - one.z))
			{
				m_roodCount++;
			}
		}

	}

	//使わない処理です消します
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

	//もう使わない
	vector<Vec3> Tracking::RouteSearchNotA()
	{		
		vector<Vec2> aStarRood;//移動遷移

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		

		m_unityMapCSV = mapManager->GetUnityMap();//AStarマップ取得
		//vector<vector<shared_ptr<Node>>> aStarMap;//マップのノード配列
		vector<shared_ptr<Node>> aStarMapline;
		//AStarマップの配列と同じ配列の大きさのノードを作る
		for (int y=0; y < m_unityMapCSV.size(); y++)
		{
			for (int x=0; x < m_unityMapCSV[0].size(); x++)
			{
				aStarMapline.push_back(make_shared<Node>(Node(x, y, Status_None, 999, 999, 999, NULL)));
			}
			m_unityMap.push_back(aStarMapline);
			aStarMapline.clear();//リセット
		}
		auto test=0;
		
		//初期位置を決める自分自身(Enemy)の現在地点
		auto enemySelPos = mapManager->ConvertSelMap(m_ownerPos);//セルに変える
		auto enemyAStarPos = mapManager->ConvertUnityMap(enemySelPos);
		auto originPos = enemyAStarPos;
		m_unityMap[originPos.y][originPos.x]->Status = Status_Open;
		auto cost = 0;
		//ゴール地点(Player)	
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);
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
			root = LookAround(m_unityMap[originPos.y][originPos.x],goalPos);
	
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
		rootVec.push_back(m_playerPos);
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

				if (lookX < 0||lookX>m_unityMap.size()-1)
				{
					auto test=0;
				}
				if (lookY < 0||lookY>m_unityMap.size()-1)
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

	//RushMoveの処理
	void Tracking::RushMove(bool onOff)
	{
		//RushMoveしていい場合の処理(２回目以降の処理)
		if (onOff && m_rushFlow == Rush_Continue)
		{
			//進む方向が別になっていたらラッシュ状態をやめる
			if (m_XorZBefor != GetMoveXorZ())
			{
				m_rushMoveFlag = false;//ラッシュ状態をやめる
				AngerSpeed(m_anger);
				m_rushFlow = Rush_Start;//リセットする
				m_rushSetSpeedCountTime = 0.0f;//ラッシュ状態の待機時間もリセット
			}
		}
		else if (onOff && m_rushFlow == Rush_SetSpeed)//加速処理(一番最初の処理)
		{
			m_rushSetSpeedCountTime += m_delta;

			if(m_rushSetSpeedCountTime >= 0.15f)
			{
				AngerSpeed(m_anger);
				m_Owner->SetSpeed(m_Owner->GetSpeed() * 2.0f);//ラッシュ状態の待機状態にする
				m_rushFlow = Rush_Continue;//この処理を終わらせたら継続処理に遷移する
			}
		}
		else if (onOff && m_rushFlow == Rush_Start)//RushMoveしていい場合の処理(一番最初の処理)
		{
			//いま走っている方向を覚える
			m_XorZBefor = GetMoveXorZ();
			m_Owner->SetSpeed(0.0f);//ラッシュ状態の待機状態にする
			
			m_rushFlow = Rush_SetSpeed;//この処理を終わらせたら加速する処理に遷移する
		}

		//RushMove出来なくなったとき
		if (!onOff && m_rushFlow == Rush_Continue)
		{
			m_Owner->SetSpeed(21.0f);
			m_rushFlow = Rush_Start;//リセットする
			m_rushSetSpeedCountTime = 0.0f;//ラッシュ状態の待機時間もリセット
		}
	}

	//RushMoveしていいか確認する関数
	bool Tracking::RushMoveChack(Vec3 pos, int vision)
	{
		Vec3 n_pos = pos;

		int n_vision = vision;
		int lineRootCount = 0;//直線の道がどのくらい続いているか記録する変数

		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		auto angle = m_Owner->GetAngle();

		//x方向に進んでいるかz方向に進んでいるか確認する falseがx,trueがz
		bool XorZ=false;
		//前回はx方向に進んでいるかz方向に進んでいるか確認する falseがx,trueがz
		bool XorZBetor = false;
		//まっすく進んでいる経路か確認する変数
		bool straightLine = true;


		//突進するのに現在の進む経路が距離が足りているか
		if (m_roodCount + vision < m_tagetRootPos.size())
		{		
			//経路探索の方向と今進んでいる方向が同じか確認する
			bool XorZ = GetMoveXorZ();
			Vec3 rootVec = m_tagetRootPos[0] - m_tagetRootPos[1];
			if (!XorZ)//x方向に進んでいるなら
			{
				//経路探索では次どの方向に進むか確認する
				if (rootVec.x == 0) return false;
			}
			if (XorZ)//z方向に進んでいるなら
			{
				//経路探索では次どの方向に進むか確認する
				if (rootVec.z == 0) return false;
			}

			//今進む経路はvisionの数値程直線が続いているか確認する
			for (int i = 0; i <= vision; i++)
			{
				//今の座標と目標地点の座標の差を測る変数
				Vec3 distance = Vec3(0.0f, 0.0f, 0.0f);
				if (i == 0)
				{
					distance = m_tagetRootPos[m_roodCount+i] - m_ownerPos;
				}
				if (i > 0)
				{
					distance = m_tagetRootPos[m_roodCount + i] - m_tagetRootPos[m_roodCount + lineRootCount];
				}

				//xかz方向どっちに進んでいるか見る
				if (distance.x != 0.0f)
				{
					XorZ = true;
				}
				if (distance.z != 0.0f)
				{
					XorZ = false;
				}

				//１回目ならX方向Z方向どっちに進んでいるか保存する
				if (i == 0)
				{
					XorZBetor = XorZ;
				}
				//2回目以降はXとZの進む方向が違うなら突進をしない
				if (i > 0)
				{
					if (XorZBetor != XorZ)//違うのであれば突進しない
					{
						return false;//突進できない
					}
				}

				lineRootCount = i;
			}

			//直線の道が最低限ラッシュをするために必要な距離があればやる
			if (lineRootCount == vision)
			{
				return true;//突進して良い
			}
		}

		return false;//違うのであれば突進しない
	}

	//怒り値によってスピードを決める処理
	void Tracking::AngerSpeed(int anger)
	{
		switch (anger)
		{
		case ANGER_NONE://怒ってない
			m_Owner->SetSpeed(21.0f);
			break;
		case ANGER_LOW://怒ってる(弱)
			m_Owner->SetSpeed(21.0f * 1.065f);
			break;
		case ANGER_MIDDLE://怒ってる(中)
			m_Owner->SetSpeed(21.0f * 1.25f);
			break;
		case ANGER_HI://怒ってる(強)
			m_Owner->SetSpeed(21.0f * 1.5f);
			break;
		default:
			break;
		}
	}

}

//end basecross
