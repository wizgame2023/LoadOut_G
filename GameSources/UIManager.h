/*!
@file UIManager.h
@brief UI�̊Ǘ������܂�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIManager :public GameObject
	{
	private:
		shared_ptr<StageManager> m_stageManager;//�X�e�[�W�}�l�[�W���[
		shared_ptr<NuberManager> m_spriteNum;//�����X�v���C�g
		shared_ptr<NuberManager> m_spriteNumSecond;//�����X�v���C�g�̓��

		shared_ptr<Sprite> m_text;//�e�L�X�g�̃X�v���C�g
		shared_ptr<Sprite> m_sprite;

		bool m_keyGetFlag;//������ɓ��������𖞂����Ă��邩�m�F����t���O
	public:
		UIManager(shared_ptr<Stage> &stagePtr);//�R���X�g���N�^
		~UIManager();//�f�X�g���N�^

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void BatteryHow();//�d�r���ǂꂭ�炢�����Ă��邩��UI�𐶐�����
	};

}
//end basecross
