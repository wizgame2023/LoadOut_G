#pragma once
#include "stdafx.h"

namespace basecross {
	class Ground :public GameObject
	{
		Vec3 m_pos;//�|�W�V����
		Vec3 m_rot;//��]�x
		int OneBlock;//���̃Q�[���̒P��(���̐��l���Z�����W�ł͂P�Ƃ���)
	public:

		Ground(const shared_ptr<Stage>& StagePtr, Vec3 pos,Vec3 rot = Vec3(10.0f,0.1f,10.0f));//�R���X�g���N�^
		Ground(const shared_ptr<Stage>& StagePtr);//�R���X�g���N�^
		~Ground();//�f�X�g���N�^

		virtual void OnCreate() override;//�J�n����ۂɌĂяo���֐�
		//virtual void OnUpdate() override;

	};
}
