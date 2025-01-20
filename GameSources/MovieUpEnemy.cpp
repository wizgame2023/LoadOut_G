/*!
@file MovieUpEnemy.cpp
@brief �G���オ�郀�[�r�[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpEnemy::MovieUpEnemy(shared_ptr<Stage>& stagePtr,weak_ptr<Enemy> enemy) :
		Movie(stagePtr),
		m_Enemy(enemy)
	{

	}

	MovieUpEnemy::~MovieUpEnemy()
	{
	}

	void MovieUpEnemy::OnCreate()
	{		
		Movie::OnCreate();

		//�ł�������Enemy�̃R���|�[�l���g�擾
		auto enemyTrans = m_Enemy.lock()->GetComponent<Transform>();
		auto enemyPos = enemyTrans->GetPosition();
		

		m_movieCamera->SetAt(enemyPos);//�����_��ł�������Enemy�ɌŒ肷��

		m_Enemy.lock()->MoveSwich(false);//�����Ȃ�����

	}

	void MovieUpEnemy::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		//�ł�������Enemy�̃R���|�[�l���g�擾
		auto enemyTrans = m_Enemy.lock()->GetComponent<Transform>();
		auto enemyPos = enemyTrans->GetPosition();
		auto enemyQt = enemyTrans->GetQuaternion();

		m_movieCamera->SetAt(enemyPos);//�����_��ł�������Enemy�ɌŒ肷��
		auto speed = 100.0f;
		enemyPos.y += speed * delta;
		enemyTrans->SetPosition(enemyPos);//�ʒu�X�V

		enemyQt = enemyQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
		enemyTrans->SetQuaternion(enemyQt);

		//�I������
		if (enemyPos.y >= 150.0f)
		{
			//SE���� �G�̋��ѐ�
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			auto SE = SEManager->Start(L"Scream", 0, 0.9f);
			auto stage = GetStage();

			GetStage()->RemoveGameObject<Enemy>(m_Enemy.lock());
			GetStage()->RemoveGameObject<MovieUpEnemy>(GetThis<MovieUpEnemy>());//�������g���폜
		}


	}

}
//end basecross
