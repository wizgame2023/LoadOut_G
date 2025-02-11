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
		shared_ptr<Sprite> m_StageText1;
		shared_ptr<Sprite> m_StageText2;
		shared_ptr<NuberManager> m_NumberSprite;
		shared_ptr<BlackOut> m_blackOut;//�Ó]����
		shared_ptr<Sprite>m_spriteMozi;
		shared_ptr<Sprite>m_spriteB;

		shared_ptr<Sprite> m_LStick1;
		shared_ptr<Sprite> m_LStick2;
		shared_ptr<Sprite> m_LStickLeft;
		shared_ptr<Sprite> m_LStickRight;

		float m_time = 0;
		float m_controllerTime = 0;
		float m_countTime = 0;


		int m_count = 0;
		int m_controllerCount = 0;
		int m_SelectStage;//�I�����Ă���X�e�[�W

		const int m_allStage = 20;
		
		bool m_decisionFlag;//�I���������ǂ����̃t���O
		bool m_stickCheck;//�X�e�B�b�N�̌X�����������󂯎�邩�̃t���O
		bool m_stickLongCheck;//�����X���Ă��邩�̃t���O

		bool m_updateFlag;//�A�b�v�f�[�g�̃t���O


		CONTROLER_STATE m_controler;//�R���g���[���[

	public:
		//�\�z�Ɣj��
		SelectStage() :
			Stage(),
			m_stickCheck(true),
			m_updateFlag(true)
		{}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SelectionStage();//�ǂ̃X�e�[�W�ɂ��邩�̑I������

		void OnDestroy()override;
		void SetUpdateFlag(bool onOff);//�A�b�v�f�[�g���邩�̃Z�b�^�[

	};


}
//end basecross

