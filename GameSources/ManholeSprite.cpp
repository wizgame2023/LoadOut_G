/*!
@file ManholeSprite.cpp
@brief �~�j�}�b�v�p�̃}���z�[���X�v���C�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ManholeSprite::ManholeSprite(shared_ptr<Stage>& stagePtr,shared_ptr<Manhole> parent, wstring textureName, Vec2 size, Vec3 pos, Vec3 rot, Col4 color, int layer):
		Sprite(stagePtr,textureName,size,pos,rot,color,layer),
		m_parent(parent)
	{
	}

	ManholeSprite::~ManholeSprite()
	{
	}

	void ManholeSprite::OnUpdate()
	{
		auto lock = m_parent.lock();
		if (lock)
		{
			auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
			auto DrawSprite = GetComponent<PCTSpriteDraw>();
			auto state = lock->GetState();//�X�e�[�g�擾
			//�d�r��ݒu����Ă����
			if (state == lock->Manhole_Start)
			{
				DrawSprite->SetTextureResource(L"Red");
			}
			//���������オ��Ȃ�
			if (state == lock->Manhole_SoonUp)
			{
				m_countTime += delta;
				if (m_countTime < 0.1f)
				{
					DrawSprite->SetTextureResource(L"Red");
				}
				if (m_countTime >= 0.1f)
				{
					m_countTime = 0.0f;
					DrawSprite->SetTextureResource(L"Black");
				}
			}
			//�ʂ�Ȃ��Ȃ��Ă���Ȃ�
			if (state == lock->Manhole_Used)
			{
				DrawSprite->SetTextureResource(L"Black");
			}
			//�d�r��ݒu����Ă��Ȃ����
			if (state == lock->Manhole_None)
			{
				DrawSprite->SetTextureResource(L"Bule");
			}

		}
		//�ǐՌ����Ȃ���Ύ������g����������
		if (!lock)
		{
			GetStage()->RemoveGameObject<ManholeSprite>(GetThis<ManholeSprite>());
		}
	}


}
//end basecross
