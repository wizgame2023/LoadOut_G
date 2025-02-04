/*!
@file RepopEnemy.h
@brief ���|�b�v���̓G�̓���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TargetLost :public Patrol
	{
	private:
		float m_goalPosY;//�ڕW�n�_
		float m_speed;
		float m_aStarUpdateCount;//AStar�����̍X�V���鎞�Ԃ𑪂����

		bool m_arrive;//���ǂ蒅�������̃t���O

		Vec3 m_ownerPos;
		Vec3 m_ownerRot;
		Vec3 m_playerPos;
		Vec3 m_forward;
		Vec3 m_right;

		Vec3 m_targetPos;//�ڕW�n�_
		vector<Vec3>m_navi;//�ڕW�n�_�ɂ��ǂ蒅�����߂̈ړ��ꏊ
		int m_numbers;//�ړ������̉��Ԗڂ̈ړ������Ȃ𐔂��邽�߂̕ϐ�

	public:
		TargetLost(const shared_ptr<Enemy> ptrOwner);
		~TargetLost();

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}
//end basecross
