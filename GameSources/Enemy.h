/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Enemy :public GameObject
	{
	private:
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_speed;
		// ���݂̃X�e�[�g�����Ă���
		shared_ptr<StateBase> m_CurrentSt;

		// ���̃X�e�[�g�����Ă����A�X�e�[�g������Ƒ����ɐ؂�ւ��
		shared_ptr<StateBase> m_NextSt;

	public:
		//�R���X�g���N�^�E�f�X�g���N�^
		Enemy(const shared_ptr<Stage>& StagePtr);
		~Enemy();

		//�����E�X�V�E�폜
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		// m_NextState�ɑ������
		template <typename NextState>
		void ChangeState()
		{
			m_NextSt.reset();

			m_NextSt = makeShared<NextState>(GetThis<Enemy>());
		}
		float GetSpeed();
	};

}
//end basecross
