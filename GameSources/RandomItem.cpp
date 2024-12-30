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
		trans->SetScale(1.0f, 1.0f, 1.0f);

		//ドローメッシュ設定
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//コリジョン設定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);
		
	}

	void RandomItem::OnCollisionEnter(shared_ptr<GameObject>& obj)
	{
		auto player = dynamic_pointer_cast<Player>(obj);
		//もし当たったのがプレイヤーならランダムにイベントが発生する
		if (player)
		{
			auto randam = rand() % 10;

			switch (randam)
			{
			case 0:
				player->AddCount(2);
				break;
			case 1:
				player->AddCount(3);
				break;
			case 2:
				//Playerのスピードを遅くする
				break;
			case 3:
				//Playerのスピードを速くする
				break;
			default:
				break;
			}
		}
	}

}
//end basecross
