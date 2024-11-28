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
		CameraChange();
		Vec3 cameraEye = m_movieCamera->GetEye();
		testPos = cameraEye;
	}

	void Movie::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		//auto pos = m_stageCamera.lock()->GetEye();
		//auto pos = Vec3(0.0f, 0.0f, 0.0f);

		//�e�X�g�p(�������ǂ����m�F��������)///////////////////////////////////////////////////////////////////
		Vec3 cameraEye = m_movieCamera->GetEye();
		Vec3 m_MoviePos = testPos+Vec3(100.0f, 0.0f, 10.0f);//�ړI�n
		if (cameraEye != m_MoviePos)
		{
			cameraEye += CameraMove(30,cameraEye,m_MoviePos);//�ԐړI�Ɉړ�����
			m_movieCamera->SetEye(cameraEye);//�ړ�����
			if (abs(cameraEye.x - m_MoviePos.x) <= 0.5f && abs(cameraEye.z - m_MoviePos.z) <= 0.5f)//�ق�Pos���^�[�Q�b�g�̂�Pos�ƈꏏ�Ȃ�
			{
				cameraEye = m_MoviePos;
				m_movieCamera->SetEye(cameraEye);//�ꏏ�Ƃ݂Ȃ�
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	//���[�r�[�p�̃J�����ɕύX������
	void Movie::CameraChange()
	{
		auto startPos = Vec3(0.0f, 50.0f, -30.0f);//�����ʒu

		m_stageCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());//�X�e�[�W�p�̃J�������擾
		auto a = m_stageCamera.lock()->GetEye();
		m_movieCamera = ObjectFactory::Create<Camera>();//�J�����쐬
		m_movieCamera->SetEye(startPos);//�����ʒu
		m_movieCamera->SetAt(m_stageCamera.lock()->GetAt());//�������S�_
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
