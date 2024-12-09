/*!
@file MovieUpEnemy.cpp
@brief �G���オ�郀�[�r�[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpEnemy::MovieUpEnemy(shared_ptr<Stage>& stagePtr,shared_ptr<Enemy> enemy) :
		Movie(stagePtr),
		m_Enemy(enemy)
	{

	}

	MovieUpEnemy::~MovieUpEnemy()
	{
	}

	void MovieUpEnemy::OnCreate()
	{
		//�ł�������Enemy�̃R���|�[�l���g�擾
		auto enemyTrans = m_Enemy.lock()->GetComponent<Transform>();
		auto enemyPos = enemyTrans->GetPosition();
		

		CameraChange();//�J������ύX����
		m_movieCamera->SetAt(enemyPos);//�����_��ł�������Enemy�ɌŒ肷��

		m_Enemy.lock()->MoveSwich(false);//�����Ȃ�����

	}

	void MovieUpEnemy::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		//�ł�������Enemy�̃R���|�[�l���g�擾
		auto enemyTrans = m_Enemy.lock()->GetComponent<Transform>();
		auto enemyPos = enemyTrans->GetPosition();
		auto enemyRot = enemyTrans->GetQuaternion();

		m_movieCamera->SetAt(enemyPos);//�����_��ł�������Enemy�ɌŒ肷��
		auto speed = 100.0f;
		enemyPos.y += speed * delta;
		enemyTrans->SetPosition(enemyPos);//�ʒu�X�V

		enemyRot = enemyRot*Quat(0.0f, 1.0f*(sin(XMConvertToRadians(30.0f)) / 2), 0.0f,cos(XMConvertToRadians(30.0f)) / 2.0f);
		enemyTrans->SetQuaternion(enemyRot);

		//�I������
		if (enemyPos.y >= 150.0f)
		{
			auto View = GetStage()->CreateView<SingleView>();//�r���[�쐬
			auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 50.0f, -30.0f));

			View->SetCamera(PtrCamera);//�J������߂�
			GetStage()->SetView(View);
			GetStage()->RemoveGameObject<MovieGameStart>(GetThis<MovieGameStart>());//�������g���폜

		}


	}

}
//end basecross
