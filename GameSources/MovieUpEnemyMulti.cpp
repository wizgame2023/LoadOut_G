/*!
@file MovieUpEnemyMulti.cpp
@brief �G�������ł������郀�[�r�[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpEnemyMulti::MovieUpEnemyMulti(shared_ptr<Stage>& stagePtr,vector<weak_ptr<Enemy>> upEnemyVec) :
		Movie(stagePtr),
		m_upEnemyVec(upEnemyVec),
		m_removeFlag(false)
	{

	}

	MovieUpEnemyMulti::~MovieUpEnemyMulti()
	{

	}

	void MovieUpEnemyMulti::OnCreate()
	{
		Movie::OnCreate();
		auto sharedEnemy = m_upEnemyVec[0].lock();
		if (sharedEnemy)
		{
			m_movieCameraAt = sharedEnemy->GetComponent<Transform>()->GetPosition();//���[�r�[�J�����̏��������_�����߂�
		}

		//�ł�������G��l��l�ɂǂ̕����ɑł��������Ă����̂����߂�
		int i = 0;
		for (i; i < m_upEnemyVec.size(); i++)
		{
			float deg = rand() % 360;//�����_���ɉ��x�̕����ɐi�ނ����߂�
			float rad = XMConvertToRadians(deg);//�f�B�O���[���烉�W�A���ɕς���

			m_upEnemyMoveAngleVec.push_back(rad);//�z��ɓ����
		}

	}

	void MovieUpEnemyMulti::OnUpdate()
	{
		//�X�e�[�W�J�������擾�ł��Ȃ�������return
		if (!m_stageCamera) return;

		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		auto speed = 100.0f;//�X�s�[�h

		//�J�����̒����_�ړ�
		m_movieCameraAt.y += speed * delta;
		m_movieCamera->SetAt(m_movieCameraAt);//�ړ����������_���Z�b�g����

		int enemyCountNum = 0;//�G�̐��𐔂���ϐ�

		//�����ł�������G�̓����̏���
		for (auto enemy : m_upEnemyVec)
		{
			auto castEnemy = enemy.lock();
			//�L���X�g�o���Ȃ�������R���e�j���[�Ǝ������g���폜
			if (!castEnemy)
			{
				GetStage()->RemoveGameObject<MovieUpEnemyMulti>(GetThis<MovieUpEnemyMulti>());
				continue;
			}

			//�ł�������Enemy�̃R���|�[�l���g�擾
			auto enemyTrans = castEnemy->GetComponent<Transform>();
			auto enemyPos = enemyTrans->GetPosition();
			auto enemyQt = enemyTrans->GetQuaternion();


			//�����_���ȕ����ɑł��������Ă���
			enemyPos.x += cosf(m_upEnemyMoveAngleVec[enemyCountNum]) * (speed / 10) * delta;
			enemyPos.z += sinf(m_upEnemyMoveAngleVec[enemyCountNum]) * (speed / 10) * delta;
			enemyPos.y += speed * delta;
			enemyTrans->SetPosition(enemyPos);//�ʒu�X�V

			enemyQt = enemyQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
			enemyTrans->SetQuaternion(enemyQt);

			//������x�G���ł�����������I���t���O���I���ɂ���
			if (enemyPos.y >= 150.0f)
			{
				//�t���O���I���ɂ���
				m_removeFlag = true;
			}

		}

		//�t���O���I���ɂȂ�����I������������
		if (m_removeFlag)
		{
			for (auto enemy : m_upEnemyVec)
			{
				auto sharedEnemy = enemy.lock();

				if (sharedEnemy)//�����ƃ��b�N���Ă��邩�m�F����
				{
					GetStage()->RemoveGameObject<Enemy>(sharedEnemy);//�폜����		
				
					//SE���� �G�̋��ѐ�
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Scream", 0, 0.9f);
				}
			}
			GetStage()->RemoveGameObject<MovieUpEnemyMulti>(GetThis<MovieUpEnemyMulti>());//�������g���폜
		}


	}

}
//end basecross
