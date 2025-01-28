/*!
@file MovieGameClear.cpp
@brief �Q�[���N���A�̃��[�r�[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieGameClear::MovieGameClear(shared_ptr<Stage>& stagePtr):
		Movie(stagePtr)
	{

	}
	MovieGameClear::~MovieGameClear()
	{

	}

	void MovieGameClear::OnCreate()
	{
		Movie::OnCreate();	
		m_tagetPos = m_movieCamera->GetEye() - Vec3(0.0f, 15.0f, 0.0f);//�ړI�n
		
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");//�v���C���[�擾	
		player->MoveSwitch(false);//player�𓮂����Ȃ�
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();
		playerDraw->ChangeCurrentAnimation(L"Happey");//���ꂵ�����[�V�����ɕύX

	}

	void MovieGameClear::OnUpdate()
	{
		//�X�e�[�W�J�������擾�ł��Ȃ�������return
		if (!m_stageCamera) return;

		auto stage = GetStage();
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		auto cameraPos = m_movieCamera->GetEye();
		auto player = stage->GetSharedGameObject<Player>(L"Player");//�v���C���[�擾
		auto playerTrans = player->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();

		//Player�̃A�j���[�V�����X�V
		playerDraw->UpdateAnimation(delta);

		player->MoveSwitch(false);//player�𓮂����Ȃ�
		Vec3 moveVec= Vec3(cameraPos.x - playerPos.x, cameraPos.y - playerPos.y, cameraPos.z - playerPos.z);//�J������Player�̋����x�N�g��
		float angle = atan2(moveVec.z, moveVec.x);//�p�x���擾
		playerTrans->SetRotation(Vec3(0.0f, -angle, 0.0f));//�J�����ڐ��ɂȂ�悤�ɂ���
		
		if (m_count == 0)//�����@
		{
			if (cameraPos != m_tagetPos)
			{
				cameraPos.y -= 10.0f*delta;//�ԐړI�Ɉړ�
				m_movieCamera->SetEye(cameraPos);
				if (abs(cameraPos.y - m_tagetPos.y) <= 0.5f)//�ق�Pos���^�[�Q�b�g�̂�Pos�ƈꏏ�Ȃ�
				{
					cameraPos = m_tagetPos;
					m_movieCamera->SetEye(cameraPos);
					m_count = 1;//�X�V
				}
				m_movieCamera->SetEye(cameraPos);

			}

		}
		if (m_count == 1)//�����A
		{
			//�X�e�[�W�}�l�[�W���[�ɃQ�[���N���A�̃t���O��n��
			auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetClearFlag(true);

		}


	}

}
//end basecross
