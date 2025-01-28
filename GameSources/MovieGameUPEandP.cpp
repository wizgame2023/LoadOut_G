/*!
@file MovieGameUPEandP.cpp
@brief �G���ł�������ۃv���C���[���}���z�[���𓥂�ł��ۂ̏���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpEandP::MovieUpEandP(shared_ptr<Stage>& stagePtr, weak_ptr<Enemy> enemy,weak_ptr<Player> player) :
		Movie(stagePtr),
		m_Enemy(enemy),
		m_Player(player)
	{

	}

	MovieUpEandP::~MovieUpEandP()
	{

	}

	void MovieUpEandP::OnCreate()
	{
		Movie::OnCreate();

		m_sprite = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800));//�Ó]�p�̃X�v���C�g�쐬
		m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		m_spriteCol = m_sprite->GetColor();
	}

	void MovieUpEandP::OnUpdate()
	{
		//�X�e�[�W�J�������擾�ł��Ȃ�������return
		if (!m_stageCamera) return;

		auto enemy = m_Enemy.lock();
		auto player = m_Player.lock();

		if (enemy && player)
		{
			auto delta = App::GetApp()->GetElapsedTime();

			//�G���擾
			auto enemyTrans = enemy->GetComponent<Transform>();
			auto enemyPos = enemyTrans->GetPosition();
			auto enemyQt = enemyTrans->GetQuaternion();
			//�v���C���[���擾
			auto playerTrans = player->GetComponent<Transform>();
			auto playerPos = playerTrans->GetPosition();
			auto playerQt = playerTrans->GetQuaternion();

			//�����_
			m_movieCamera->SetAt(playerPos);

			//�ړ�����
			enemyPos.y += 100.0f * delta;
			playerPos.y += 100.0f * delta;

			//�ꏊ�X�V
			enemyTrans->SetPosition(enemyPos);
			playerTrans->SetPosition(playerPos);

			//��]����
			enemyQt = enemyQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
			enemyTrans->SetQuaternion(enemyQt);
			playerQt = playerQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
			playerTrans->SetQuaternion(playerQt);

			m_time += delta;//���Ԍo��

			//��莞�Ԃ�������I��
			if (m_time >= 1.0f)
			{
				m_spriteCol.w += delta;
				m_sprite->SetColor(m_spriteCol);
				if (m_spriteCol.w >= 1.0f)//��ʂ��^���ÂɂȂ�����
				{				
					GetStage()->RemoveGameObject<MovieUpEandP>(GetThis<MovieUpEandP>());
					//�Q�[���I�[�o�V�[���ɍs��
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");//�Q�[���I�[�o�V�[���Ɉړ�����

				}

			}

		}
	}


}
//end basecross
