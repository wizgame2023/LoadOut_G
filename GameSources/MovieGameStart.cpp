/*!
@file MovieGameStart.cpp
@brief �Q�[���J�n���̃��[�r�p
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieGameStart::MovieGameStart(shared_ptr<Stage>& stagePtr,float mapSize,float speed) :
		Movie(stagePtr),
		m_mapSize(mapSize),
		m_speed(speed)
	{

	}

	MovieGameStart::~MovieGameStart()
	{
	}

	void MovieGameStart::OnCreate()
	{
		Movie::OnCreate();
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = stage->GetGameObjectVec();
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto enemy : obj)
		{
			auto castEnemy = dynamic_pointer_cast<Enemy>(enemy);
			if (castEnemy)//�A�C�e���^�ɃL���X�g����
			{
				castEnemy->MoveSwich(false);//�������Ȃ�������
			}
		}
		for (auto player : obj)
		{
			auto castPlayer = dynamic_pointer_cast<Player>(player);
			if (castPlayer)//�A�C�e���^�ɃL���X�g����
			{
				castPlayer->MoveSwich(false);//�������Ȃ�������
			}
		}


	}

	void MovieGameStart::OnUpdate()
	{
		auto cameraPos = m_movieCamera->GetEye();//�J�����̃|�W�V�������擾
		auto tagetPos = Vec3(0.0f, 0.0f, m_mapSize/2);//�ړI�n

		if (m_count == 0)//�����@
		{
			if (cameraPos != tagetPos)//�ړI�n�ƃJ�����̈ʒu�������łȂ��Ȃ�
			{
				cameraPos += CameraMove(m_speed, cameraPos, tagetPos);
				m_movieCamera->SetEye(cameraPos);
				if (abs(cameraPos.x - tagetPos.x) <= 5.8f && abs(cameraPos.z - tagetPos.z) <= 5.8f)//�ق�Pos���^�[�Q�b�g�̂�Pos�ƈꏏ�Ȃ�
				{
					tagetPos.y = cameraPos.y;
					m_movieCamera->SetEye(tagetPos);//�ꏏ�Ƃ݂Ȃ�
					m_count = 1;
				}

			}

			auto cameraAt = m_movieCamera->GetAt();//�J������At���擾
			auto tagetAt = cameraPos-Vec3(0.0f,cameraPos.y,-30.0f);
			m_movieCamera->SetAt(tagetAt);

		}

		if (m_count == 1)//�����A
		{
			auto View = GetStage()->CreateView<SingleView>();//�r���[�쐬
			auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 50.0f, -30.0f));

			View->SetCamera(PtrCamera);//�J������߂�
			GetStage()->SetView(View);
			GetStage()->RemoveGameObject<MovieGameStart>(GetThis<MovieGameStart>());//�������g���폜

			//Acotr��������悤�ɂ���
			auto stage = GetStage();//�X�e�[�W�擾
			//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
			auto obj = stage->GetGameObjectVec();
			//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
			for (auto enemy : obj)
			{
				auto castEnemy = dynamic_pointer_cast<Enemy>(enemy);
				if (castEnemy)//�A�C�e���^�ɃL���X�g����
				{
					castEnemy->MoveSwich(true);//�������Ȃ�������
				}
			}
			for (auto player : obj)
			{
				auto castPlayer = dynamic_pointer_cast<Player>(player);
				if (castPlayer)//�A�C�e���^�ɃL���X�g����
				{
					castPlayer->MoveSwich(true);//�������Ȃ�������
				}
			}

		}

	}

	//���[�r�[�p�̃J�����ɕύX������
	void MovieGameStart::CameraChange()
	{
		float stageLenght = m_mapSize;//�X�e�[�W�̒��a
		auto startPos = Vec3(0.0f, stageLenght, -stageLenght);//�����ʒu
		m_StageView = GetStage()->GetView();
		m_stageCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());//�X�e�[�W�p�̃J�������擾 �Ȃ������̊֐����I���Ƃ��̕ϐ��̒��g�������܂�

		m_movieCamera = ObjectFactory::Create<Camera>();//�J�����쐬
		m_movieCamera->SetEye(startPos);//�����ʒu
		m_movieCamera->SetAt(m_stageCamera->GetAt());//�������S�_
		auto movieView = GetStage()->CreateView<SingleView>();//�r���[�쐬
		movieView->SetCamera(m_movieCamera);//�r���[�Ƀ��[�r�[�p�̃J�����ݒu
		GetStage()->SetView(movieView);//�X�e�[�W�Ƀ��[�r�[�p�̃r���[��ݒu����

	}
}
//end basecross
