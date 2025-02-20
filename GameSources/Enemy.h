/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "Ray.h"
#include "BillBoard.h"

namespace basecross {

	enum ABILITY
	{
		normal,
		perspective,
		rush,
	};

	enum ANGER
	{
		ANGER_NONE,
		ANGER_LOW,
		ANGER_MIDDLE,
		ANGER_HI
	};

	class Enemy :public Actor
	{
	private:
		Vec3 m_pos;
		const Vec3 m_startPos;
		Vec3 m_playerPos;
		Vec3 m_scale;

		float m_speed;
		float m_angle;

		int m_ability;
		int m_anger;//�ǂꂭ�炢�{���Ă���̂���\���ϐ�(�X�e�[�^�X���オ��)

		bool m_startPop;//�ŏ��̃X�|�[�������|�b�v����\���ϐ�


		//�V���h�E�}�b�v
		shared_ptr<Shadowmap> m_ptrShadow;
		//���b�V���f�[�^
		shared_ptr<PNTBoneModelDraw> m_ptrDraw;

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
		Enemy(shared_ptr<Stage>& StagePtr, Vec3 pos, bool startpop = true, int ability = normal,int anger = 0);

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
		void ChangeAbility(int state);//�X�e�[�g��ύX���鏈��
		float GetSpeed();
		void SetSpeed(float speed);
		float GetAngle();
		int GetAbility();
		int GetAnger();//�{��l��n��
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
