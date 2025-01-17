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
		m_charen(Manhole_None)
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
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャーのポインタ取得

		AddTag(L"Manhole");//マンホール用のタグ

		//GetStage()->AddGameObject<BillBoard>();

		//ビルボードの生成
		m_billBoard = GetStage()->AddGameObject<BillBoard>(GetThis<GameObject>(), L"Clear", 13.0f, Vec3(5.0f, 5.0f, 5.0f));
		m_billBoardSecond = GetStage()->AddGameObject<BillBoardGauge>(GetThis<GameObject>(), L"Clear", 13.0f, Vec3(5.0f, 5.0f, 5.0f));


	}

	void Manhole::OnUpdate()
	{
		m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャーのポインタ取得
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto stage = GetStage();//ステージ取得

		ManholeTransition();//マンホールの遷移

		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"時間 : " << m_time
		//	<< endl;
		//scene->SetDebugString(wss.str());

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
			m_billBoard->ChangeTexture(L"Clear");
			m_billBoardSecond->ChangeTexture(L"Clear");
		}

		//プレイヤーが設置したマンホールから離れた際に少しの間だけ無敵にする
		if (m_playerStanbyFlag&& m_playerUpTime<0.3f)
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
			m_waterPillar = GetStage()->AddGameObject<WaterPillar>(clearPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(8.5f, 10.0f, 8.5f));
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
			}

		}

	}

	//入り続けているとき処理
	void Manhole::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		auto test = m_mapManager.lock(); //->SelMapNow(m_pos) == 2
		auto enemy = dynamic_pointer_cast<Enemy>(other);
		auto player = dynamic_pointer_cast<Player>(other);

		if (test->SelMapNow(m_pos) == 2)
		{//もし当たったオブジェクトが敵なら
			if (enemy)
			{
				//GetStage()->RemoveGameObject<Enemy>(enemy);//まだ敵をリムーブしない
				test->MapDataUpdate(m_pos, 3);//現在はその道は通れないようにする
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");//マンホールの蓋が出たテクスチャにする

				auto enemyStartPos = enemy->GetStartPos();//敵の初期位置を取得
				auto stageManager = GetStage()->GetSharedGameObject<StageManager>(L"StageManager");
				stageManager->SetRepopEnemyPos(enemyStartPos);//上の初期位置をStageManagerに渡す

				GetStage()->AddGameObject<MovieUpEnemy>(enemy);//打ちあがる時の敵のムービー

			}
			else if (player)//プレイヤーなら
			{
				if (m_playerUpTime > 0.3f)
				{
					test->MapDataUpdate(m_pos, 3);//現在はその道は通れないようにする
					GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");
					GetStage()->AddGameObject<MovieUpPlayer>();//Playerが上がってしまうムービが出る
				}
			}
		}

	}
	void Manhole::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto test = m_mapManager.lock(); //->SelMapNow(m_pos) == 2
		auto enemy = dynamic_pointer_cast<Enemy>(other);
		auto player = dynamic_pointer_cast<Player>(other);
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto stage = GetStage();
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");

		if (test->SelMapNow(m_pos) == 2)
		{//もし当たったオブジェクトが敵なら
			if (enemy)
			{
				//GetStage()->RemoveGameObject<Enemy>(enemy);//まだ敵をリムーブしない
				test->MapDataUpdate(m_pos, 3);//現在はその道は通れないようにする
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");//マンホールの蓋が出たテクスチャにする

				auto enemyStartPos = enemy->GetStartPos();//敵の初期位置を取得
				auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
				stageManager->SetRepopEnemyPos(enemyStartPos);//上の初期位置をStageManagerに渡す

				player = stage->GetSharedGameObject<Player>(L"Player");
				auto playerPos = stage->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
				auto playerSelPos = mapManager->ConvertSelMap(playerPos);
				auto selPos = mapManager->ConvertSelMap(m_pos);

				//敵がマンホールを踏んでいる際にプレイヤーもマンホールを踏んでいる際にはプレイヤーと敵が打ちあがるムービーが出る
				if (playerSelPos.x == selPos.x && playerSelPos.y == selPos.y)
				{
					stage->AddGameObject<MovieUpEandP>(enemy, player);
				}
				else//敵だけマンホールを踏んでいる映像
				{
					stage->AddGameObject<MovieUpEnemy>(enemy);//打ちあがる時の敵のムービー
				}

			}
			else if (player)//プレイヤーなら
			{
				if (m_playerUpTime > 0.3f)
				{
					test->MapDataUpdate(m_pos, 3);//現在はその道は通れないようにする
					GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");
					stage->AddGameObject<MovieUpPlayer>();//Playerが上がってしまうムービが出る
				}
			}
		}
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

	int Manhole::GetState()
	{
		return m_charen;
	}


}
//end basecross
