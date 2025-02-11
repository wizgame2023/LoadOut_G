/*!
@file Actor.h
@brief Player��Enemy�ȂǓ����I�u�W�F�N�g�̐e�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomItem :public Actor
	{
		Vec3 m_pos;//�|�W�V����
		Vec3 m_rot;//��]�x
		//const int m_oneBlock;//���̃Q�[���̒P��(���̐��l���Z�����W�ł͂P�Ƃ���)
	public:

		RandomItem(shared_ptr<Stage>& StagePtr, Vec3 pos);//�R���X�g���N�^
		~RandomItem();//�f�X�g���N�^

		virtual void OnCreate() override;//�J�n����ۂɌĂяo���֐�
		virtual void OnUpdate() override;

		void OnCollisionEnter(shared_ptr<GameObject>& obj)override;

	};
}
