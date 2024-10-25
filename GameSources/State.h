/*!
@file State.h
@brief �X�e�[�g�}�V��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//Enemy�N���X�̑O���錾
	class Enemy;

	//�X�e�[�g�̊��N���X
	class StateBase
	{
	protected:
		// �X�e�[�g�̏��L�җp
		shared_ptr<Enemy> m_Owner;
	public:
		//StateBase�̃R���X�g���N�^�E�f�X�g���N�^�̐錾
		StateBase(const shared_ptr<Enemy> OwnerPtr) :
			m_Owner(OwnerPtr)
		{

		}
		virtual ~StateBase() {}

		virtual void OnStart() = 0;//�X�e�[�g�����s����Ƃ��ŏ��̈�񂾂��s��
		virtual void OnUpdate() = 0;//�X�e�[�g�����s����Ƃ����t���[���s��
		virtual void OnExit() = 0;//�X�e�[�g���؂�ւ�鎞�ɍs��
	};

}
//end basecross
