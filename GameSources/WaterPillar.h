#pragma once
#include "stdafx.h"

namespace basecross {
	class WaterPillar :public GameObject
	{
		Vec3 m_pos;//�|�W�V����
		Vec3 m_originPos;//���X�̎w�肳��Ă����ʒu
		Vec3 m_rot;//��]�x
		Vec3 m_scale;//�T�C�Y
		const int m_oneBlock;//���̃Q�[���̒P��(���̐��l���Z�����W�ł͂P�Ƃ���)
		wstring m_texName;//�e�N�X�`���̖��O
		int shape;//�`���ǂ����邩�̕ϐ�

		int m_count;//�i�s�x
	public:

		WaterPillar(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot,Vec3 scale);//�R���X�g���N�^
		~WaterPillar();//�f�X�g���N�^

		virtual void OnCreate() override;//�J�n����ۂɌĂяo���֐�
		virtual void OnUpdate() override;

	};
}
