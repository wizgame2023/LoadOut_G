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
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Manhole");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする

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

		//m_mapManager.lock()->MapDataUpdate(m_pos, 1);//今いるセル座標はマンホールのデータということを伝える
		//セル座標にアイテムを設置した情報があったら
		auto test = m_charen;
		auto a = 0;
		if (m_mapManager.lock()->SelMapNow(m_pos)==2&&m_charen==0)
		{
			m_charen = 1;//アイテムが置かれている状態
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"Red");//自分自身にアイテムが置かれていると分かりやすくする
		}

		//通行禁止になる時の処理
		if (m_mapManager.lock()->SelMapNow(m_pos) == 3 && m_charen == 1)
		{
			m_charen = 2;//通行禁止になっている状態
			Vec3 clearPos = m_pos;
			clearPos.y += 5.0f;
			m_clearObject = GetStage()->AddGameObject<ClearObject>(clearPos, Vec3(0.0f, 0.0f, 0.0f));

			//水柱が発生する
			m_waterPillar = GetStage()->AddGameObject<WaterPillar>(clearPos, Vec3(0.0f, 0.0f, 0.0f),Vec3(10.0f,10.0f,10.0f));
		}

		//通行禁止の時の際の処理
		if (m_charen == 2)
		{
			//クールタイム過ぎたら通れるようにする
			m_time += delta;
			if (m_time > 10.0f)//時間が過ぎたら
			{
				m_time = 0;//クールタイムリセット
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//自分自身にアイテムが置かれていると分かりやすくする
				m_mapManager.lock()->MapDataUpdate(m_pos, 1);//マップマネージャーに通れる状態だと返す
				stage->RemoveGameObject<ClearObject>(m_clearObject);//前生成した透明なオブジェクトを消す
				stage->RemoveGameObject<WaterPillar>(m_waterPillar);//前生成した水柱を消す
				m_charen = 0;
			}

		}


		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"時間 : " << m_time
		//	<< endl;
		//scene->SetDebugString(wss.str());

	}

	void Manhole::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto test = m_mapManager.lock(); //->SelMapNow(m_pos) == 2
		auto enemy = dynamic_pointer_cast<Enemy>(other);


		if (test->SelMapNow(m_pos) == 2)
		{//もし当たったオブジェクトが敵ならば
			if (enemy)
			{
				GetStage()->RemoveGameObject<Enemy>(enemy);
				test->MapDataUpdate(m_pos, 3);//現在はその道は通れないようにする
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");

				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//ゲームクリアに移動する(仮で敵は1人しかないから)

			}
		}
	}

}
//end basecross
