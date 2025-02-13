/*!
@file WaterPillar.cpp
@brief �u���b�N�̃I�u�W�F�N�g�̎���
�S���F�O�r
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	WaterPillar::WaterPillar(shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot,Vec3 scale) :
		Actor(StagePtr),
		m_pos(pos),
		m_originPos(pos),
		m_rot(rot),
		m_scale(scale),
		m_oneBlock(10),
		m_count(0)
	{
	}
	WaterPillar::~WaterPillar()
	{
	}

	void WaterPillar::OnCreate()
	{
		//�s�|�b�g��^�񒆂ł͂Ȃ��I�u�W�F�N�g�̉��ɂ�����
		m_pos.y = m_originPos.y - (m_scale.y / 2);//�I�u�W�F�N�g�̔������炷���Ƃ�

		//Transform�쐬
		auto ptr = GetComponent<Transform>();//Transform�擾
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 0.28f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -1.5f, 0.0f)
		);

		//���b�V������
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"WaterPillerMesh");
		ptrDraw->AddAnimation(L"Defalt", 0, 30, true, 30.0f);//�A�j���[�V�����ǉ�

		//ptrDraw->SetTextureResource(L"Water");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(true);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�
		ptrColl->SetDrawActive(false);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"WaterPillar");//�u���b�N�p�̃^�O���ꂪ��b�̃I�u�W�F�N�g

		//������ԃ}���z�[���쐬
		//m_manhole =  GetStage()->AddGameObject<Block>(m_pos-Vec3(0.0f,-m_pos.y,0.0f), Vec3(0.0f, 0.0f, 0.0f));
		//m_manhole->GetComponent<CollisionObb>()->SetAfterCollision(AfterCollision::None);
		//m_manhole->GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//�}���z�[���e�N�X�`���ɕύX
		//m_manhole->GetComponent<Transform>()->SetScale(10.0f, 1.0f, 10.0f);//�T�C�Y�ύX

	}

	void WaterPillar::OnUpdate()
	{
		//�t���O���I���ɂȂ�����A�b�v�f�[�g����
		if (!m_move) return;

		auto stage = GetStage();
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		auto ptr = GetComponent<Transform>();//Transform�擾

		//�A�j���[�V�����Đ�
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(delta);

		//ptr->SetScale()
		//Transform�쐬

		//������їp�̃}���z�[����Transform��Pos�擾
		//auto manholeTrans = m_manhole->GetComponent<Transform>();
		//auto manholePos = manholeTrans->GetPosition();

		//������їp�̃}���z�[�������̍����܂ōs������폜����
		//if (manholePos.y >= 300.0f && m_manhole)
		//{
		//	stage->RemoveGameObject<Block>(m_manhole);
		//}
		//else if(m_manhole)
		//{
		//	//������їp�̃}���z�[������ɏグ��
		//	//manholePos.y += 300 * delta;
		//	//manholeTrans->SetPosition(manholePos);
		//}

		//���������ɂȂ�܂ŐL�΂�
		if (m_count == 0)
		{
			if (m_count == 0)
			{
				m_scale.y += 110*delta;//�傫����y���P�Â��₷
				ptr->SetScale(m_scale);
				m_pos.y = m_originPos.y + (m_scale.y / 2);//�I�u�W�F�N�g�̔������炷���Ƃ�
				ptr->SetPosition(m_pos);
			}

			if (m_scale.y >= 30)
			{
				m_count = 1;//����L�΂��i�K���I��

				//�L�΂����������҂�����ɂ���
				m_scale.y = 30.0f;
				ptr->SetScale(m_scale);
				m_pos.y = m_originPos.y + (m_scale.y / 2);//�I�u�W�F�N�g�̔������炷���Ƃ�
				ptr->SetPosition(m_pos);

			}

		}

		//���̒����ɂȂ�܂ŏk�܂���
		if (m_count == 1)
		{
			m_scale.y -= 100 * delta;//�傫����y���P�Â��₷
			ptr->SetScale(m_scale);
			m_pos.y = m_originPos.y + (m_scale.y / 2);//�I�u�W�F�N�g�̔������炷���Ƃ�
			ptr->SetPosition(m_pos);

			if (m_scale.y <= 15.0f)
			{
				m_count = 2;//�����k�܂���i�K���I��

				//�L�΂����������҂�����ɂ���
				m_scale.y = 15.0f;
				ptr->SetScale(m_scale);
				m_pos.y = m_originPos.y + (m_scale.y / 2);//�I�u�W�F�N�g�̔������炷���Ƃ�
				ptr->SetPosition(m_pos);

			}


		}


	}

}



