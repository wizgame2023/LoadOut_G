/*!
@file TutorialBoard.cpp
@brief �`���[�g���A���̃}�l�[�W���[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TutorialBoard::TutorialBoard(shared_ptr<Stage>& stagePtr,Vec3 pos) :
		Actor(stagePtr),
		m_pos(pos),
		m_changeTexture(false),
		m_countTime(0.0f),
		m_flow(TutorialBoard_Start)
	{

	}


	TutorialBoard::~TutorialBoard()
	{

	}

	//�쐬
	void TutorialBoard::OnCreate()
	{
		//Transform�쐬
		auto ptr = GetComponent<Transform>();//Transform�擾
		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f,0.0f,0.0f));
		ptr->SetScale(15.0f, 10.0f, 0.001f);

		//���b�V������
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		m_ptrDraw->SetTextureResource(L"Tutorial_Manhole");
		m_ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		SetAlphaActive(true);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//Player�擾
		m_player = GetStage()->GetSharedGameObject<Player>(L"Player");

		//AddTag(L"Block");//�u���b�N�p�̃^�O���ꂪ��b�̃I�u�W�F�N�g

	}

	//�X�V
	void TutorialBoard::OnUpdate()
	{
		//�A�b�v�f�[�g�t���O���I���ɂȂ�����A�b�v�f�[�g����
		if (!m_move) return;

		auto player = m_player.lock();
		//�Q�ƌ������Ȃ��Ȃ����玩����������
		if (!player)
		{
			GetStage()->RemoveGameObject<TutorialBoard>(GetThis<TutorialBoard>());
			return;
		}
		auto delta = App::GetApp()->GetElapsedTime();

		m_countTime += delta;

		//�i�s�x�o��(�G��ł��グ��e�N�X�`�����o�Ă��Ȃ���)
		if (m_countTime > 2.0f && m_flow == TutorialBoard_Start)
		{
			m_flow++;
			m_countTime = 0.0f;
		}
		//�i�s�x�o��(�G��ł��グ��e�N�X�`�����o�Ă��鎞)
		if (m_countTime > 1.0f && m_flow != TutorialBoard_Start)
		{
			m_flow++;
			m_countTime = 0.0f;
			//�i�s�x����ԍŌ�ɂȂ������ԍŏ��ɖ߂�
			if (m_flow == TutorialBoard_Reset)
			{
				m_flow = TutorialBoard_Start;
			}
		}

		//�i�s�x�ɂ���ăe�N�X�`�����ς��
		switch (m_flow)
		{
		case TutorialBoard_Start:
			m_ptrDraw->SetTextureResource(L"Tutorial_Manhole");
			break;
		case TutorialBoard_EnemyUp1:
			m_ptrDraw->SetTextureResource(L"Tutorial_Manhole2");
			break;
		case TutorialBoard_EnemyUp2:
			m_ptrDraw->SetTextureResource(L"Tutorial_Manhole3");
			break;
		case TutorialBoard_EnemyUp3:
			m_ptrDraw->SetTextureResource(L"Tutorial_Manhole4");
			break;
		default:
			break;
		}

		//Player��pos�擾
		Vec3 playerPos = player->GetComponent<Transform>()->GetPosition();
		//Player��z���W����������������Δ������ɂȂ�
		if (playerPos.z >= m_pos.z)
		{
			m_ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		}
		if (playerPos.z < m_pos.z)
		{
			m_ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

}
//end basecross