/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "Ray.h"
#include "BillBoard.h"

namespace basecross {

	class Enemy :public Actor
	{
	private:
		Vec3 m_pos;
		const Vec3 m_startPos;
		Vec3 m_playerPos;
		float m_speed;
		float m_angle;

		// ���݂̃X�e�[�g�����Ă���
		shared_ptr<StateBase> m_CurrentSt;

		// ���̃X�e�[�g�����Ă����A�X�e�[�g������Ƒ����ɐ؂�ւ��
		shared_ptr<StateBase> m_NextSt;

		shared_ptr<Ray>m_forwardRay;
		shared_ptr<Ray>m_leftRay;
		shared_ptr<Ray>m_playerRay;

		shared_ptr<BillBoard> m_billBoard;
		shared_ptr<MapManager> m_mapMgr;

	public:
		//�R���X�g���N�^�E�f�X�g���N�^
		Enemy(shared_ptr<Stage>& StagePtr);
		Enemy(shared_ptr<Stage>& StagePtr,Vec3 pos);

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

			m_NextSt = make_shared<NextState>(GetThis<Enemy>());
		}
		float GetSpeed();
		float GetAngle();
		float GetDistance(Vec3 a, Vec3 b);
		void SetAngle(float angle);
		void GetGameOverScene();
		Vec3 GetPlayerPos();
		Vec3 GetStartPos();
		shared_ptr<Ray> GetForwardRay();
		shared_ptr<Ray> GetPlayerRay();
		shared_ptr<StateBase> GetNowState();
		shared_ptr<MapManager> GetMapMgr();
	};
}
//end basecross
