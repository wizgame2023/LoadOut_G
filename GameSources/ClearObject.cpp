/*!
@file Character.cpp
@brief �����ȏ�Q��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ClearObject::ClearObject(shared_ptr<Stage>& stagePtr,Vec3 pos,Vec3 rot) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rot(rot)
	{

	}
	ClearObject::~ClearObject()
	{
	}

	void ClearObject::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(10.0f, 10.0f, 10.0f);

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//���b�V������
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"Bule");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::None);

		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(false);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�
		ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"ClearObject");//�A�C�e���p�̃^�O
	}

	void ClearObject::OnUpdate()
	{

	}





}
//end basecross
