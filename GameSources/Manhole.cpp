/*!
@file Manhole.cpp
@brief マンホール
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Manhole::Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos) :
		GameObject(stagePtr),
		m_pos(pos),
		m_charen(Manhole_None),
		m_UpdateFlag(true)
	{

	}
	Manhole::~Manhole()
	{
	}

	void Manhole::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(0.0f,0.0f,0.0f);
		ptr->SetScale(10.0f*0.5f, 1.0f, 10.0f*0.5f);

		//Transformに対しての等差数列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(2.0f, 1.0f, 2.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//メッシュ生成
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CYLINDER");
		ptrDraw->SetTextureResource(L"Manhole");
		ptrDraw->SetOwnShadowActive(true); // 影の映り込みを反映させる
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする

		//ステージ取得
		m_stage = GetStage();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャーのポインタ取得

		AddTag(L"Manhole");//マンホール用のタグ

		//GetStage()->AddGameObject<BillBoard>();

		//ビルボードの生成
		m_billBoard = GetStage()->AddGameObject<BillBoard>(GetThis<GameObject>(), L"Clear",3, 13.0f, Vec3(0.0f, 0.0f, 0.0f));
		m_billBoardSecond = GetStage()->AddGameObject<BillBoardGauge>(GetThis<GameObject>(), L"Clear", 3, 18.0f, Vec3(0.0f, 0.0f, 0.0f));


		//水柱が発生するデバック用
		//m_waterPillar = GetStage()->AddGameObject<WaterPillar>(m_pos, Vec3(0.0f, 0.0f, 0.0f), Vec3(3.2f, 0.1f, 3.2f));


	}

	void Manhole::OnUpdate()
	{
		//オンならアップデートする
		if (!m_UpdateFlag) return;

		m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャーのポインタ取得
		m_lockMapManager = m_mapManager.lock();

		//マップマネージャーがちゃんと入っていなければアップデートできない
		if (!m_lockMapManager) return;

		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		//auto m_stage = GetStage();//ステージ取得

		ManholeTransition();//マンホールの遷移

		//マンホールに電池が設置されたときのビルボード処理
		if (m_mapManager.lock()->SelMapNow(m_pos) >= 2)
		{			
			m_billBoardTime += delta;
			if (m_billBoardTime < 0.8f)
			{
				m_billBoard->SetPushY(13.0f);
				m_billBoard->SetScale(Vec3(5.0f, 5.0f, 5.0f));
				m_billBoard->ChangeTexture(L"Manhole_BillBoard_Hit");
			}
			if (m_billBoardTime >= 0.8f)
			{
				m_billBoard->SetPushY(13.0f);
				m_billBoard->SetScale(Vec3(5.0f, 5.0f, 5.0f));
				m_billBoard->ChangeTexture(L"Manhole_BillBoard_Up");
			}
			if (m_billBoardTime >= 1.6f)
			{
				m_billBoardTime = 0.0f;
			}
		}

		if (m_charen == Manhole_Used)
		{
			//どのぐらいになったら通行禁止から元に戻るかのゲージ
			//ゲージカバー
			m_billBoard->SetPushY(20.0f);
			m_billBoard->ChangeTexture(L"GaugeCover");
			m_billBoard->SetScale(Vec3(5.0f, 1.0f, 3.0f));
			//ゲージバー
			m_billBoardSecond->SetPushY(20.0f);
			m_billBoardSecond->ChangeTexture(L"Gauge");
			m_billBoardSecond->SetScale(Vec3(5.0f, 1.0f, 3.0f));

		}

		//テクスチャリセット
		if (m_mapManager.lock()->SelMapNow(m_pos) < 2)
		{
			m_billBoard->SetScale(Vec3(0.0f, 0.0f, 0.0f));
			m_billBoard->ChangeTexture(L"Clear");
			m_billBoardSecond->SetScale(Vec3(0.0f, 0.0f, 0.0f));
			m_billBoardSecond->ChangeTexture(L"Clear");
		}

		//プレイヤーが設置したマンホールから離れた際に少しの間だけ無敵にする
		if (m_playerStanbyFlag&& m_playerUpTime<0.5f)
		{
			m_playerUpTime += delta;
		}

	}

	//マンホールの遷移
	void Manhole::ManholeTransition()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto stage = GetStage();//ステージ取得
		auto a = m_mapManager.lock()->SelMapNow(m_pos);
		//セル座標にアイテムを設置した情報があったら
		if (m_mapManager.lock()->SelMapNow(m_pos) == 2 && m_charen == Manhole_None)
		{
			m_charen = Manhole_Start;//アイテムが置かれている状態
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"RedManhole");//自分自身にアイテムが置かれていると分かりやすくする
		}

		//クールタイム過ぎたら電池の抗力が切れてマンホールが上がらないようにする
		if (m_charen == Manhole_Start)//電池を入れている状態
		{
			m_stanbyTime += delta;
			//3秒経ったら点滅する
			if (m_stanbyTime > 3.0f)
			{
				m_playerStanbyFlag = true;//プレイヤーがマンホールの上にいると打ちあがるようにする
				m_charen = Manhole_SoonUp;//もうすぐマンホールが上がる状態
			}
		}

		if (m_charen == Manhole_SoonUp)
		{
			m_stanbyTime += delta;
			m_blinkingTime += delta;

			if (m_blinkingTime < 0.1f)
			{
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");
			}
			if (m_blinkingTime > 0.2f)
			{
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"RedManhole");
			}
			if (m_blinkingTime > 0.3f)
			{
				m_blinkingTime = 0;
			}
			//スタンバイ状態を終える
			if (m_stanbyTime > 5.0f)
			{
				m_charen = Manhole_Up;//電池が上がった状態にする
				m_stanbyTime = 0;//クールタイムリセット
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//自分自身にアイテムが置かれていない状態だと分かりやすくする
				m_mapManager.lock()->MapDataUpdate(m_pos, 3);//上げるようにする
			}

		}

		//通行禁止になる時の処理
		if (m_mapManager.lock()->SelMapNow(m_pos) == 3 && (m_charen == Manhole_Up||m_charen == Manhole_Start||m_charen == Manhole_None))
		{
			m_mapManager.lock()->SetUpdataUnityMapFlag(true);//UnityMapデータ更新
			m_charen = Manhole_Used;//通行禁止になっている状態
			Vec3 clearPos = m_pos;
			clearPos.y += 0.0f;
			m_clearObject = GetStage()->AddGameObject<ClearObject>(clearPos, Vec3(0.0f, 0.0f, 0.0f));
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");
			m_blinkingTime = 0;//点滅のクールタイムをリセットする

			//水柱が発生する
			m_waterPillar = GetStage()->AddGameObject<WaterPillar>(clearPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f, 0.02f, 3.0f));
		}

		//通行禁止の時の際の処理
		if (m_charen == Manhole_Used)
		{

			//クールタイム過ぎたら通れるようにする
			m_coolTime += delta;

			m_billBoardSecond->SetPercent(m_coolTime / 10.0f);//クールタイムの進行度を渡している
			
			if (m_coolTime > 10.0f)//時間が過ぎたら
			{
				m_mapManager.lock()->SetUpdataUnityMapFlag(true);//UnityMapデータ更新
				m_coolTime = 0;//クールタイムリセット
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//自分自身にアイテムが置かれていると分かりやすくする
				m_mapManager.lock()->MapDataUpdate(m_pos, 1);//マップマネージャーに通れる状態だと返す
				stage->RemoveGameObject<ClearObject>(m_clearObject);//前生成した透明なオブジェクトを消す
				stage->RemoveGameObject<WaterPillar>(m_waterPillar);//前生成した水柱を消す
				m_charen = Manhole_None;
				m_blinkingTime = 0;
				m_stanbyTime = 0;
				m_playerUpTime = 0;
				m_playerStanbyFlag = false;
			}

		}

	}

	//入り続けているとき処理
	void Manhole::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		auto enemy = dynamic_pointer_cast<Enemy>(other);
		auto player = dynamic_pointer_cast<Player>(other);

		//マンホールが上がる処理
		CollisionUpManhole(enemy, player);
	}

	void Manhole::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto enemy = dynamic_pointer_cast<Enemy>(other);
		auto player = dynamic_pointer_cast<Player>(other);

		//マンホールが上がる処理
		CollisionUpManhole(enemy, player);
	}

	void Manhole::OnCollisionExit(shared_ptr<GameObject>& other)
	{
		auto mapManager = m_mapManager.lock();
		auto player = dynamic_pointer_cast<Player>(other);

		if (mapManager->SelMapNow(m_pos)==2)
		{
			//Playerが離れたらまたプレイヤが来るか待つフラグを立てる
			if (player)
			{
				m_playerStanbyFlag = true;
			}
		}

	}

	//コリジョンによってマンホールが上がる処理
	void Manhole::CollisionUpManhole(shared_ptr<Enemy> enemy, shared_ptr<Player> player)
	{
		if (m_lockMapManager->SelMapNow(m_pos) == 2)
		{//もし当たったオブジェクトが敵なら
			if (enemy)
			{
				m_lockMapManager->MapDataUpdate(m_pos, 3);//現在はその道は通れないようにする
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");//マンホールの蓋が出たテクスチャにする

				player = m_stage->GetSharedGameObject<Player>(L"Player");
				auto playerPos = m_stage->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
				auto playerSelPos = m_lockMapManager->ConvertSelMap(playerPos);
				auto selPos = m_lockMapManager->ConvertSelMap(m_pos);

				//ステージのオブジェクトを全て取得
				auto objVec = m_stage->GetGameObjectVec();
				//取得したオブジェクトがアイテムに変換できたら配列に入れる
				for (auto obj : objVec)
				{
					auto castEnemy = dynamic_pointer_cast<Enemy>(obj);//Enemyにキャストする

					//マンホールの座標から近ければ同じなら打ち上げる配列に入れる
					if (castEnemy)
					{
						Vec3 castEnemyPos = castEnemy->GetComponent<Transform>()->GetPosition();
						if (abs(m_pos.x - castEnemyPos.x) <= 8.0f && abs(m_pos.z - castEnemyPos.z) <= 8.0f)
						{
							m_upEnemyVec.push_back(castEnemy);
						}
					}
				}

				AddTag(L"MovieManhole");//ムービーの発生元のマンホールだと覚える
				//敵がマンホールを踏んでいる際にプレイヤーもマンホールを踏んでいる際にはプレイヤーと敵が打ちあがるムービーが出る
				if (playerSelPos.x == selPos.x && playerSelPos.y == selPos.y)
				{
					m_stage->AddGameObject<MovieUpEandP>(enemy, player);
				}
				else if (m_upEnemyVec.size() >= 2)//打ちあがる敵が２体以上いたら
				{
					m_stage->AddGameObject<MovieUpEnemyMulti>(m_upEnemyVec);//複数の敵が打ちあがる時のムービー
				}
				else//敵だけマンホールを踏んでいる映像
				{
					m_stage->AddGameObject<MovieUpEnemy>(enemy);//打ちあがる時の敵のムービー
				}

				m_upEnemyVec.clear();//使い終わったor使わないので削除する

			}
			else if (player)//プレイヤーなら
			{
				if (m_playerUpTime >= 0.5f)
				{
					m_lockMapManager->MapDataUpdate(m_pos, 3);//現在はその道は通れないようにする
					m_charen = Manhole_Up;//マンホールが上がる状態にする
					GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");
					AddTag(L"MovieManhole");//ムービーの発生元のマンホールだと覚える
					m_stage->AddGameObject<MovieUpPlayer>();//Playerが上がってしまうムービが出る
				}
			}
		}

	}

	//アップデートするかのセッター
	void Manhole::SetUpdateSwitch(bool onOff)
	{
		m_UpdateFlag = onOff;
	}

	int Manhole::GetState()
	{
		return m_charen;
	}


}
//end basecross
