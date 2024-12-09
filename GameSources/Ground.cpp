/*!
@file Ground.cpp
@brief �u���b�N�̃I�u�W�F�N�g�̎���
�S���F�O�r
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ground::Ground(const shared_ptr<Stage>& StagePtr, Vec3 pos, Vec3 rot) :
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot)
	{
	}
	Ground::Ground(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_pos(Vec3(0.0f, 0.0f, 0.0f)),
		m_rot(Vec3(200.0f, 0.1f, 200.0f))
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::OnCreate()
	{
		//Transform�쐬
		auto ptr = GetComponent<Transform>();//Transform�擾
		ptr->SetPosition(m_pos);
		ptr->SetRotation(0.0f,0.0f,0.0f);
		ptr->SetScale(m_rot);

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
		ptrDraw->SetTextureResource(L"Road");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W�������� �R���W��������Ȃ��Ȃ���
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(false);
		//ptrColl->SetSleepActive(true);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�
		//ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Ground");//�n�ʗp�̃^�O

	}

}