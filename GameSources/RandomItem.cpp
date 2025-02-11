/*!
@file RandomItem.cpp
@brief ��ɓ����ƃ����_���ɃC�x���g����������A�C�e��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RandomItem::RandomItem(shared_ptr<Stage>& stagePtr, Vec3 pos) :
		Actor(stagePtr),
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
		trans->SetScale(3.0f, 3.0f, 3.0f);

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//�h���[���b�V���ݒ�
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"MisteryBox");
		ptrDraw->AddAnimation(L"Defalt", 0, 15, true, 10.0f);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W�����ݒ�
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);

		//Map���X�V
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");
		mapManager->MapDataUpdate(m_pos, 7);//�����_���A�C�e���͂����ɏo�����邱�Ƃ�\���������Ƃ��ɂ����̐��l�͕ς��Ȃ�
		
	}

	void RandomItem::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�����Đ�
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(delta);
	}

	void RandomItem::OnCollisionEnter(shared_ptr<GameObject>& obj)
	{
		auto player = dynamic_pointer_cast<Player>(obj);
		//�������������̂��v���C���[�Ȃ烉���_���ɃC�x���g����������
		if (player)
		{				
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			auto randam = rand() % 4;
			//auto randam = 3;
			switch (randam)
			{
			case 0:
				SEManager->Start(L"ItemGet", 0, 0.9f);
				player->AddCount(1);
				break;
			case 1:
				SEManager->Start(L"ItemGet", 0, 0.9f);
				player->AddCount(2);
				break;
			case 2:
				//Player�̃X�s�[�h��x������
				SEManager->Start(L"Status_Down", 0, 0.9f);
				player->SetPushSpeed(-2.0f);
				break;
			case 3:
				//Player�̃X�s�[�h�𑬂�����
				SEManager->Start(L"Status_Up", 0, 0.9f);
				player->SetPushSpeed(2.0f);
				break;
			default:
				break;
			}

			GetStage()->RemoveGameObject<RandomItem>(GetThis<RandomItem>());
			//���|�b�v�\��
			auto stageManager = GetStage()->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetRepopRandomItemPos(m_pos);
		}
	}

}
//end basecross
