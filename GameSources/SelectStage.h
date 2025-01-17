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
		shared_ptr<Sprite>m_spriteMozi;
		shared_ptr<Sprite>m_spriteB;

		int m_SelectStage;//�I�����Ă���X�e�[�W

		const int m_allStage = 20;
		
		bool m_decisionFlag;//�I���������ǂ����̃t���O

		CONTROLER_STATE m_controler;//�R���g���[���[

	public:
		//�\�z�Ɣj��
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SelectionStage();//�ǂ̃X�e�[�W�ɂ��邩�̑I������

		void OnDestroy()override;

	};


}
//end basecross

