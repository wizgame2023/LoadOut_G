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
		//�A�N�^�[���e�N���X�̂��̂����擾
		for (auto actor : objVec)
		{
			auto actorCast = dynamic_pointer_cast<Actor>(actor);
			if (actorCast)
			{
				actorCast->MoveSwich(false);//�����Ȃ��悤�ɂ���
				auto m_actorOne = actorCast;
			}
			m_actorVec.push_back(actorCast);
		}

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
				actorCheck->MoveSwich(true);//������
			}
		}

		m_collsionManager->SetCollisionSwhich(true);//�R���W�����I���ɂ���
	}

	//���[�r�[�p�̃J�����ɕύX������
	void Movie::CameraChange()
	{//�@�@�@�@�@�@�@�@�@�@�@�@�@�@���}�b�v�̒��a
		auto startPos = Vec3(0.0f, 200.0f, -200.0f);//�����ʒu

		m_stageCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());//�X�e�[�W�p�̃J�������擾
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
