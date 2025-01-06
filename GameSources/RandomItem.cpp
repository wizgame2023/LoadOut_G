/*!
@file RandomItem.cpp
@brief 手に入れるとランダムにイベントが発生するアイテム
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RandomItem::RandomItem(const shared_ptr<Stage>& stagePtr, Vec3 pos) :
		GameObject(stagePtr),
		m_pos(pos)
	{

	}

	RandomItem::~RandomItem()
	{
	}

	//作成
	void RandomItem::OnCreate()
	{
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		trans->SetScale(3.0f, 3.0f, 3.0f);

		//Transformに対しての等差数列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//ドローメッシュ設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"MisteryBox");
		ptrDraw->AddAnimation(L"Defalt", 0, 15, true, 10.0f);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン設定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);
		
	}

	void RandomItem::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		//アニメーション再生
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(delta);
	}

	void RandomItem::OnCollisionEnter(shared_ptr<GameObject>& obj)
	{
		auto player = dynamic_pointer_cast<Player>(obj);
		//もし当たったのがプレイヤーならランダムにイベントが発生する
		if (player)
		{				
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			auto randam = rand() % 4;
			switch (randam)
			{
			case 0:
				SEManager->Start(L"ItemGet", 0, 0.9f);
				player->AddCount(2);
				break;
			case 1:
				SEManager->Start(L"ItemGet", 0, 0.9f);
				player->AddCount(3);
				break;
			case 2:
				//Playerのスピードを遅くする
				SEManager->Start(L"Status_Down", 0, 0.9f);
				player->SetPushSpeed(-2.0f);
				break;
			case 3:
				//Playerのスピードを速くする
				SEManager->Start(L"Status_Up", 0, 0.9f);
				player->SetPushSpeed(2.0f);
				break;
			default:
				break;
			}

			GetStage()->RemoveGameObject<RandomItem>(GetThis<RandomItem>());
			//リポップ予約
			auto stageManager = GetStage()->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetRepopRandomItemPos(m_pos);
		}
	}

}
//end basecross
