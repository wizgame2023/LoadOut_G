#pragma once
#include "stdafx.h"

namespace basecross {
	class Block :public GameObject
	{
		Vec3 m_pos;//�|�W�V����
		Vec3 m_rot;//��]�x
		int OneBlock;//���̃Q�[���̒P��(���̐��l���Z�����W�ł͂P�Ƃ���)
	public:

		Block(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot);//�R���X�g���N�^
		~Block();//�f�X�g���N�^

		virtual void OnCreate() override;//�J�n����ۂɌĂяo���֐�
		//virtual void OnUpdate() override;

	};
}
