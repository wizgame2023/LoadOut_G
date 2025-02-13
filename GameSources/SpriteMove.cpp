/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	SpriteMove::SpriteMove(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size, Vec3 pos, Vec3 rot, Col4 color, float speed,int layer) :
		Sprite(stagePtr, textureName, size, pos, rot, color, layer),
		m_speed(speed)
	{
	}
	SpriteMove::~SpriteMove()
	{
	}
	void SpriteMove::OnCreate()
	{
		Sprite::OnCreate();
	}
	void SpriteMove::OnUpdate()
	{
		//�t���O���I���ɂȂ�����A�b�v�f�[�g����
		if (!m_updateFlag) return;

		float time = App::GetApp()->GetElapsedTime();
		//�X�v���C�g�̈ړ�
		m_pos.x += m_speed * time;
		m_trans->SetPosition(m_pos);

		//��ʂ���o��������鏈��
		if (m_pos.x >= 1000 || m_pos.x <= -1000)
		{
			GetStage()->RemoveGameObject<SpriteMove>(GetThis<SpriteMove>());
		}
	}
}
//end basecross
