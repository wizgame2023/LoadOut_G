/*!
@file MovieUpPlayer.cpp
@brief Player���ł������鎞�̃��[�r�[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpPlayer::MovieUpPlayer(shared_ptr<Stage>& stagePtr):
		Movie(stagePtr)
	{

	}

	MovieUpPlayer::~MovieUpPlayer()
	{

	}

	void MovieUpPlayer::OnCreate()
	{
		CameraChange();//�J������ύX����

		m_sprite = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800));//�Ó]�p�̃X�v���C�g�쐬
		m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		m_spriteCol = m_sprite->GetColor();
	}

	void MovieUpPlayer::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		//�ł�������Player
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");
		auto playerPos = player->GetComponent<Transform>()->GetPosition();
		player->m_move = false;
		
		playerPos.y += 100.0f*delta;
		player->GetComponent<Transform>()->SetPosition(playerPos);

		m_movieCamera->SetAt(playerPos);

		//���̌�ɃQ�[���I�[�o�p�̃A�j���[�V����������
		m_time += delta;

		if (m_time >= 1.0f)
		{
			m_spriteCol.w += delta;
			m_sprite->SetColor(m_spriteCol);
			if (m_spriteCol.w >= 1.0f)//��ʂ��^���ÂɂȂ�����
			{
				//�Q�[���I�[�o�V�[���ɍs��
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");//�Q�[���I�[�o�V�[���Ɉړ�����

			}
		}
	}

}
//end basecross
