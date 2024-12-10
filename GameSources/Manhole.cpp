/*!
@file Manhole.cpp
@brief マンホール
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Manhole::Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos) :
		GameObject(stagePtr),
		m_pos(pos)
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

	}

	//マンホールの遷移
	void Manhole::ManholeTransition()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto stage = GetStage();//ステージ取得

		//セル座標にアイテムを設置した情報があったら
		if (m_mapManager.lock()->SelMapNow(m_pos) == 2 && m_charen == 0)
		{
			m_charen = 1;//アイテムが置かれている状態
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"RedManhole");//自分自身にアイテムが置かれていると分かりやすくする
		}

		//クールタイム過ぎたら電池の抗力が切れてマンホールが上がらないようにする
		if (m_charen == 1)//電池を入れている状態
		{
			m_stanbyTime += delta;
			//3秒経ったら点滅する
			if (m_stanbyTime > 3.0f)
			{
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
			}
			//スタンバイ状態を終える
			if (m_stanbyTime > 5.0f)
			{
				m_stanbyTime = 0;//クールタイムリセット
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//自分自身にアイテムが置かれていない状態だと分かりやすくする
				m_mapManager.lock()->MapDataUpdate(m_pos, 3);//上げるようにする
			}

		}

		//通行禁止になる時の処理
		if (m_mapManager.lock()->SelMapNow(m_pos) == 3 && m_charen == 1)
		{
			m_charen = 2;//通行禁止になっている状態
			Vec3 clearPos = m_pos;
			clearPos.y += 5.0f;
			m_clearObject = GetStage()->AddGameObject<ClearObject>(clearPos, Vec3(0.0f, 0.0f, 0.0f));
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");
			m_blinkingTime = 0;//点滅のクールタイムをリセットする

			//水柱が発生する
			m_waterPillar = GetStage()->AddGameObject<WaterPillar>(clearPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(10.0f, 10.0f, 10.0f));
		}

		//通行禁止の時の際の処理
		if (m_charen == 2)
		{
			//クールタイム過ぎたら通れるようにする
			m_coolTime += delta;
			if (m_coolTime > 10.0f)//時間が過ぎたら
			{
				m_coolTime = 0;//クールタイムリセット
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//自分自身にアイテムが置かれていると分かりやすくする
				m_mapManager.lock()->MapDataUpdate(m_pos, 1);//マップマネージャーに通れる状態だと返す
				stage->RemoveGameObject<ClearObject>(m_clearObject);//前生成した透明なオブジェクトを消す
				stage->RemoveGameObject<WaterPillar>(m_waterPillar);//前生成した水柱を消す
				m_charen = 0;
				m_blinkingTime = 0;
				m_stanbyTime = 0;
			}

		}

	}

	void Manhole::OnCollisionEnter(shared_ptr<GameObject>& other)
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
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");

				GetStage()->AddGameObject<MovieUpEnemy>(enemy);//打ちあがる時の敵のムービー
				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//ゲームクリアに移動する(仮で敵は1人しかないから)

			}
			if (player)//プレイヤーなら
			{
				GetStage()->AddGameObject<MovieUpPlayer>();//Playerが上がってしまうムービが出る
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


}
//end basecross
