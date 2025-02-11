/*!
@file Movie.cpp
@brief ���[�r�[�֌W�̐e�N���X
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Movie::Movie(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}

	Movie::~Movie()
	{

	}

	void Movie::OnCreate()
	{
		auto stage = GetStage();
		m_collsionManager = GetStage()->GetSharedGameObject<StageCollisionManager>(L"CollsionManager");
		m_collsionManager->SetCollisionSwhich(false);//�R���W�����I�t�ɂ���

		auto objVec = stage->GetGameObjectVec();
		//�A�N�^�[���p�����Ă�����̂����擾
		for (auto obj : objVec)
		{
			auto actorCast = dynamic_pointer_cast<Actor>(obj);
			auto batteryCast = dynamic_pointer_cast<Battery>(obj);
			auto manholeCast = dynamic_pointer_cast<Manhole>(obj);
			auto spriteCast = dynamic_pointer_cast<Sprite>(obj);

			//�A�N�^�[���p�����Ă���G�t�F�N�g�ȊO�̃I�u�W�F�N�g��~
			if (actorCast)
			{
				if (!actorCast->FindTag(L"Effect"))
				{
					actorCast->MoveSwitch(false);//�����Ȃ��悤�ɂ���
					m_actorVec.push_back(actorCast);
				}
			}	
			//�}���z�[����~
			if (manholeCast)
			{
				//���[�r�[�������łȂ��}���z�[���͒�~����
				if (!manholeCast->FindTag(L"MovieManhole"))
				{
					manholeCast->SetUpdateSwitch(false);//�����Ȃ��悤�ɂ���
					m_manholeVec.push_back(manholeCast);
				}
				RemoveTag(L"MovieManhole");//���̃^�O���K�v�Ȃ��Ȃ����̂ō폜����
			}
			//�o�b�e���[��~
			if (batteryCast)
			{
				batteryCast->SetUpdateSwitch(false);//�����Ȃ��悤�ɂ���
				m_batteryVec.push_back(batteryCast);
			}
			//�X�v���C�g���p�����Ă���I�u�W�F�N�g�𓧖��ɂ���
			if (spriteCast)
			{
				spriteCast->OnClear(true);//�����ɂ���
				m_spriteVec.push_back(spriteCast);
			}

		}

		m_stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		m_stageManager->SetUpdateFlag(false);//�����Ȃ�����

		CameraChange();//�J�����ύX
	}

	void Movie::OnUpdate()
	{

	}

	void Movie::OnDestroy()
	{
		//�����I�u�W�F�N�g��������悤�ɂ���
		for (auto actor : m_actorVec)
		{
			auto actorCheck = actor.lock();
			if (actorCheck)
			{
				actorCheck->MoveSwitch(true);//������
			}
		}
		//�o�b�e���[�𓮂���悤�ɂ���
		for (auto battery : m_batteryVec)
		{
			auto batteryCheck = battery.lock();
			if (batteryCheck)
			{
				batteryCheck->SetUpdateSwitch(true);//������
			}
		}
		//�}���z�[���𓮂���悤�ɂ���
		for (auto manhole : m_manholeVec)
		{
			auto manholeCheck = manhole.lock();
			if (manholeCheck)
			{
				manholeCheck->SetUpdateSwitch(true);//������
			}

		}
		//�X�v���C�g�𓧖������������
		for (auto sprite : m_spriteVec)
		{
			auto spriteCheck = sprite.lock();
			if (spriteCheck)
			{
				spriteCheck->OnClear(false);//��������߂�
			}
		}

		//�J������߂�����
		auto View = GetStage()->CreateView<SingleView>();//�r���[�쐬
		auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 50.0f, -30.0f));

		View->SetCamera(PtrCamera);//�J������߂�
		GetStage()->SetView(View);

		m_collsionManager->SetCollisionSwhich(true);//�R���W�����I���ɂ���
		m_stageManager->SetUpdateFlag(true);//�X�e�[�W�}�l�[�W���[�������悤�ɂ���
	}

	//���[�r�[�p�̃J�����ɕύX������
	void Movie::CameraChange()
	{//�@�@�@�@�@�@�@�@�@�@�@�@�@�@���}�b�v�̒��a
		auto startPos = Vec3(0.0f, 200.0f, -200.0f);//�����ʒu

		m_stageCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());//�X�e�[�W�p�̃J�������擾
		//�����X�e�[�W�p�̃J�������擾�ł��Ȃ�������return���Ď������폜���܂�
		if (!m_stageCamera)
		{
			GetStage()->RemoveGameObject<Movie>(GetThis<Movie>());
			return;
		}
		auto a = m_stageCamera->GetEye();
		m_movieCamera = ObjectFactory::Create<Camera>();//�J�����쐬
		m_movieCamera->SetEye(m_stageCamera->GetEye());//�����ʒu
		m_movieCamera->SetAt(m_stageCamera->GetAt());//�������S�_
		auto movieView = GetStage()->CreateView<SingleView>();//�r���[�쐬
		movieView->SetCamera(m_movieCamera);//�r���[�Ƀ��[�r�[�p�̃J�����ݒu
		GetStage()->SetView(movieView);//�X�e�[�W�Ƀ��[�r�[�p�̃r���[��ݒu����

	}

	//�J�����𓮂���
	Vec3 Movie::CameraMove(float speed,Vec3 pos,Vec3 tagetPos)//�ړ����鋗�������߂Ă���
	{
		float vecX = tagetPos.x - pos.x;//�ڕW�ʒu��Player�Ƃ�X���W�̋����𑪂��Ă���
		float vecZ = tagetPos.z - pos.z;//�ڕW�ʒu��Player�Ƃ�Z���W�̋����𑪂��Ă���
		float rad = atan2(vecZ, vecX);//�p�x�����߂�i���W�A���j

		Vec3 moveVec(0.0f, 0.0f, 0.0f);

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();//�f���^�^�C�����擾
		moveVec.x = (speed * cos(rad)) * delta;//�ԐړI�ɋ����𑫂��Ă���
		moveVec.z = (speed * sin(rad)) * delta;//�ԐړI�ɋ����𑫂��Ă���

		return moveVec;
	}


}
//end basecross
