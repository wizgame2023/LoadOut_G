/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Hatch::Hatch(shared_ptr<Stage>& stagePtr,Vec3 pos) :
		GameObject(stagePtr),
		m_pos(pos)
	{

	}

	Hatch::~Hatch()
	{

	}

	void Hatch::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetScale(10.0f * 0.5f, 1.0f, 10.0f * 0.5f);

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(2.0f, 1.0f, 2.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//���b�V������
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Hatch");
		ptrDraw->SetOwnShadowActive(true); // �e�̉f�荞�݂𔽉f������
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(false);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Hatch");//�n�b�`�p�̃^�O

	}

	void Hatch::OnUpdate()
	{
		//�����n�b�`���󂢂Ă����ԂȂ�X�e�[�W�}�l�[�W���[�ɃQ�[���N���A���Ƃ����t���O��n��
		auto stage = GetStage();
		auto mapManager = stage->GetSharedGameObject<MapManager>(L"MapManager");
		auto pos = GetComponent<Transform>()->GetPosition();
		auto nowYuka = mapManager->SelMapNow(pos);//���̃Z�����W�͂ǂ̏�Ԃ�������
		if (nowYuka == 5)//�n�b�`���J����Ă����Ԃł����
		{
			//�F��ς���
			auto ptrDraw = GetComponent<PNTStaticDraw>();
			ptrDraw->SetTextureResource(L"Black");

			if (m_count == 0)
			{
				m_count = 1;
				stage->AddGameObject<MovieGameClear>();//�f�o�b�N�p

			}


			

			//�X�e�[�W�}�l�[�W���[�ɃQ�[���N���A�̃t���O��n��
			//auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
			//stageManager->SetClearFlag(true);
		}
	}


}
//end basecross
