/*!
@file RandomItem.cpp
@brief ��ɓ����ƃ����_���ɃC�x���g����������A�C�e��
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

	//�쐬
	void RandomItem::OnCreate()
	{
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		trans->SetScale(10.0f, 10.0f, 10.0f);

		//�h���[���b�V���ݒ�
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//�R���W�����ݒ�
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);
		
	}

	void RandomItem::OnCollisionEnter(shared_ptr<GameObject>& obj)
	{
		auto player = dynamic_pointer_cast<Player>(obj);
		//�������������̂��v���C���[�Ȃ烉���_���ɃC�x���g����������
		if (player)
		{
			auto randam = rand() % 4;
			randam = 3;
			switch (randam)
			{
			case 0:
				player->AddCount(2);
				break;
			case 1:
				player->AddCount(3);
				break;
			case 2:
				//Player�̃X�s�[�h��x������
				player->SetPushSpeed(-5.0f);
				break;
			case 3:
				//Player�̃X�s�[�h�𑬂�����
				player->SetPushSpeed(5.0f);
				break;
			default:
				break;
			}

			GetStage()->RemoveGameObject<RandomItem>(GetThis<RandomItem>());
		}
	}

}
//end basecross
