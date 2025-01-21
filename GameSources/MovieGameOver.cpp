/*!
@file MovieGameOver.cpp
@brief �Q�[���I�[�o�[�̃��[�r�[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieGameOver::MovieGameOver(shared_ptr<Stage>& stagePtr) :
		Movie(stagePtr)
	{

	}
	MovieGameOver::~MovieGameOver()
	{

	}

	void MovieGameOver::OnCreate()
	{
		Movie::OnCreate();
		m_tagetPos = m_movieCamera->GetEye() - Vec3(0.0f, 15.0f, 0.0f);//�ړI�n

		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");//�v���C���[�擾
		player->MoveSwitch(false);//player�𓮂����Ȃ�
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();
		playerDraw->ChangeCurrentAnimation(L"Player_Down");//���ꂽ���[�V�����ɕύX


	}

	void MovieGameOver::OnUpdate()
	{
		auto stage = GetStage();
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		auto cameraPos = m_movieCamera->GetEye();
		auto player = stage->GetSharedGameObject<Player>(L"Player");//�v���C���[�擾
		auto playerTrans = player->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();


		player->MoveSwitch(false);//player�𓮂����Ȃ�

		if (m_count == 0)//�����@
		{
			if (cameraPos != m_tagetPos)
			{
				cameraPos.y -= 10.0f * delta;//�ԐړI�Ɉړ�
				m_movieCamera->SetEye(cameraPos);
				if (abs(cameraPos.y - m_tagetPos.y) <= 0.5f)//�ق�Pos���^�[�Q�b�g�̂�Pos�ƈꏏ�Ȃ�
				{
					cameraPos = m_tagetPos;
					m_movieCamera->SetEye(cameraPos);
					//m_count = 1;//�X�V
				}
				m_movieCamera->SetEye(cameraPos);

			}
			//Player�̃A�j���[�V�����X�V
			m_gameOverFlag = playerDraw->UpdateAnimation(delta);
			if (m_gameOverFlag)
			{
				m_count++;
			}

		}
		if (m_count == 1)//�����A
		{		
			//�X�e�[�W�}�l�[�W���[�ɃQ�[���N���A�̃t���O��n��
			auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetGameOverFlag(true);

		}

		if (m_count == 2)//�����B
		{
		}


	}

}
//end basecross
