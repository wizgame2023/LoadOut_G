/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "Ray.h"

namespace basecross {

	class Enemy :public Actor
	{
	private:
		Vec3 m_pos;
		float m_speed;
		float m_angle;

		// ���݂̃X�e�[�g�����Ă���
		shared_ptr<StateBase> m_CurrentSt;

		// ���̃X�e�[�g�����Ă����A�X�e�[�g������Ƒ����ɐ؂�ւ��
		shared_ptr<StateBase> m_NextSt;

		shared_ptr<Ray>m_forwardRay;
		//shared_ptr<Ray>m_leftRay;
		//shared_ptr<Ray>m_playerRay;

	public:
		//�R���X�g���N�^�E�f�X�g���N�^
		Enemy(shared_ptr<Stage>& StagePtr);
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

		float GetAngle();
		void SetAngle(float angle);

		shared_ptr<Ray> GetForwardRay();
	};

}
//end basecross
