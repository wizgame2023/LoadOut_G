/*!
@file Block.cpp
@brief �u���b�N�̃I�u�W�F�N�g�̎���
�S���F�O�r
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Block::Block(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot) :
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot),
		m_oneBlock(10)
	{
	}
	Block::~Block()
	{
	}

	void Block::OnCreate()
	{
		//Transform�쐬
		auto ptr = GetComponent<Transform>();//Transform�擾
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_oneBlock, m_oneBlock, m_oneBlock);

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

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(true);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�
		ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}

}



