/*!
@file Character.cpp
@brief フラグ管理用のアイテム
       このアイテムを拾うことによってマンホールを上げて攻撃することができる
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Item::Item(shared_ptr<Stage>& stagePtr,Vec3 pos,Vec3 rot) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rot(rot)
	{

	}
	Item::~Item()
	{
	}

	void Item::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(3.0f, 3.0f, 3.0f);

		//Transformに対しての等差数列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//メッシュ生成
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Bule");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(false);
		ptrColl->SetSleepActive(false);//ぶつからない限りスリープ状態になる
		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}

	void Item::OnUpdate()
	{

	}

	//Playerにぶつかった際にカウントをプラスする
	void Item::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto player = dynamic_pointer_cast<Player>(other);
		auto stage = GetStage();

		if (player)
		{
			if (other->FindTag(L"Player"))//もし、タグがPlayerなら
			{
				player->AddCount(1);//カウントをプラスする
				stage->RemoveGameObject<Item>(GetThis<Item>());//自分自身を削除
			}
		}
	}

}
//end basecross
