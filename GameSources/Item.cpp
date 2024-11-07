/*!
@file Character.cpp
@brief �t���O�Ǘ��p�̃A�C�e��
       ���̃A�C�e�����E�����Ƃɂ���ă}���z�[�����グ�čU�����邱�Ƃ��ł���
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

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//���b�V������
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Bule");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(false);
		ptrColl->SetSleepActive(false);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�
		ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}

	void Item::OnUpdate()
	{

	}

	//Player�ɂԂ������ۂɃJ�E���g���v���X����
	void Item::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto player = dynamic_pointer_cast<Player>(other);
		auto stage = GetStage();

		if (player)
		{
			if (other->FindTag(L"Player"))//�����A�^�O��Player�Ȃ�
			{
				player->AddCount(1);//�J�E���g���v���X����
				stage->RemoveGameObject<Item>(GetThis<Item>());//�������g���폜
			}
		}
	}

}
//end basecross
