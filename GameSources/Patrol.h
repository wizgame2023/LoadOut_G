/*!
@file Patrol.h
@brief èÑâÒ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Patrol :public StateBase
	{
	private:
		Vec3 m_pos;
		Vec3 m_rot;

		int m_rnd;
		float m_time;
		float m_distance;
		float m_point;

		shared_ptr<Transform> m_trans;

	public:
		Patrol(const shared_ptr<Enemy> ptrOwner) :
			StateBase(ptrOwner),
			m_pos(0, 0, 0),
			m_rot(0, 0, 0),
			m_rnd(rand() % 2 + 1),
			m_time(0.0f),
			m_distance(0),
			m_point(30)
		{
		}
		virtual ~Patrol() {}

		void OnStart();
		void OnUpdate();
		void OnExit();
	};
}
//end basecross
