/*!
@file Ground.cpp
@brief �u���b�N�̃I�u�W�F�N�g�̎���
�S���F�O�r
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ground::Ground(const shared_ptr<Stage>& StagePtr,vector<vector<int>> map,float push) :
		GameObject(StagePtr),
		m_map(map),
		m_push(push)
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
		ptr->SetScale(Vec3(10.0f,0.1f,10.0f));

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//���b�V������
		auto ptrDraw = AddComponent<PNTStaticInstanceDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Road");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		////csv�t�@�C������ǂݎ���ď��֌W�̃I�u�W�F�N�g�̐�������
		for (int i = 0; i < m_map.size(); i++)
		{
			for (int j = 0; j < m_map[0].size(); j++)
			{
				//�u���b�N�̈ʒu���擾
				float x = (j * 10.0f) - m_push;
				float z = m_push - (i * 10.0f);

				//�C���X�^���X�p�̍s����쐬����
				Mat4x4 matrix;
				//matrix.translation(Vec3(x, 0.0f, z));
				//matrix.scale(Vec3(10.0f, 0.1f, 10.0f));
				matrix.affineTransformation(
					Vec3(10.0f, 0.1f, 10.0f),
					Vec3(),
					Vec3(),
					Vec3(x, 0.0f, z)
				);
				ptrDraw->AddMatrix(matrix);//�u���b�N��\��

			}
		}


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