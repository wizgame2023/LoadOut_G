/*!
@file TilteStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "BlackOut.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SpriteNum>m_sprite;

		shared_ptr<Sprite> m_StagePhoto;
		shared_ptr<Sprite> m_StageText;
		shared_ptr<NuberManager> m_NumberSprite;
		shared_ptr<BlackOut> m_blackOut;//�Ó]����

		int m_SelectStage;//�I�����Ă���X�e�[�W

		const int m_allStage = 20;
		

	public:
		//�\�z�Ɣj��
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnDestroy()override;

	};


}
//end basecross

