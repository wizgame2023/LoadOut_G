/*!
@file Patrol.h
@brief 巡回
*/

#pragma once
#include "stdafx.h"
#include "Ray.h"

namespace basecross {

	class Patrol :public StateBase
	{
	private:
		//Vec3型のメンバー変数
		Vec3 m_ownerPos;
		Vec3 m_ownerRot;
		Vec3 m_destinationPos;
		Vec3 m_right;
		Vec3 m_forward;

		//int型メンバー変数
		int m_rnd;
		int m_numbers;

		//float型メンバー変数
		float m_time;
		float m_moveTime;
		float m_distance;
		const float m_point;

		//bool型メンバー変数
		bool m_destinationDecision;
		bool m_wallCheck;
		bool m_rightCheck;
		bool m_forwardCheck;
		bool m_minus;

		//shared_ptr型メンバー変数
		shared_ptr<Transform> m_trans;

		//weak_ptr型メンバー変数
		weak_ptr<Ray> m_forwardRay;
		weak_ptr<Ray>m_playerRay;
	public:
		//コンストラクタの宣言
		Patrol(const shared_ptr<Enemy> ptrOwner) :
			StateBase(ptrOwner),
			m_ownerPos(0, 0, 0),
			m_ownerRot(0, 0, 0),
			m_destinationPos(0, 0, 0),
			m_right(1, 0, 0),
			m_forward(0, 0, 1),
			m_rnd(1),
			m_numbers(0),
			m_time(0.0f),
			m_moveTime(0.0f),
			m_distance(0.0f),
			m_point(120.0f),
			m_destinationDecision(false),
			m_wallCheck(false),
			m_rightCheck(false),
			m_forwardCheck(false),
			m_minus(false)

		{
		}
		virtual ~Patrol() {}

		void OnStart();
		void OnUpdate();
		void OnExit();


	};
}
//end basecross
