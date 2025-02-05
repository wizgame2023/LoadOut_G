/*!
@file Character.cpp
@brief フラグ管理用のアイテム
       このアイテムを拾うことによってマンホールを上げて攻撃することができる
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Battery::Battery(shared_ptr<Stage>& stagePtr,Vec3 pos,Vec3 rot) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rot(rot),
		m_updateFlag(true)
	{

	}
	Battery::~Battery()
	{
	}

	void Battery::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(3.0f, 3.0f, 3.0f);

		//Transformに対しての等差数列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//メッシュ生成
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Battry");
		ptrDraw->AddAnimation(L"Defalt", 0, 30, true, 30.0f);
		//ptrDraw->SetTextureResource(L"Bule");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		//ptrColl->SetFixed(false);
		//ptrColl->SetSleepActive(false);//ぶつからない限りスリープ状態になる
		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Battery");//アイテム用のタグ

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");
		mapManager->MapDataUpdate(m_pos, 6);//電池が置かれたことを表す

	}

	void Battery::OnUpdate()
	{
		//オンならアップデートする
		if (!m_updateFlag) return;

		auto delta = App::GetApp()->GetElapsedTime();
		//アニメーション再生
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(delta);
	}

	//Playerにぶつかった際にカウントをプラスする
	void Battery::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto player = dynamic_pointer_cast<Player>(other);
		auto stage = GetStage();

		if (player)
		{
			if (other->FindTag(L"Player"))//もし、タグがPlayerなら
			{
				//SE
				auto SE = App::GetApp()->GetXAudio2Manager();
				SE->Start(L"ItemGet", 0, 0.9f);

				player->AddCount(1);//カウントをプラスする
				stage->RemoveGameObject<Battery>(GetThis<Battery>());//自分自身を削除
			}
		}
	}

	//削除されたときの処理
	void Battery::OnDestroy()
	{
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");
		mapManager->MapDataUpdate(m_pos, 0);//電池がなくなったことを表す
	}

	void Battery::SetUpdateSwitch(bool onOff)
	{
		m_updateFlag = onOff;
	}

}
//end basecross
