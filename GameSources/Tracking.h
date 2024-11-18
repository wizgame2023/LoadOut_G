/*!
@file Tracking.h
@brief í«ê’
*/

#pragma once
#include "stdafx.h"
#include"Ray.h"
namespace basecross {

	class Tracking :public StateBase
	{
	private:
		Vec3 m_ownerPos;
		Vec3 m_ownerRot;
		Vec3 m_playerPos;
		Vec3 m_forward;
		Vec3 m_right;

		shared_ptr<Transform> m_trans;

		weak_ptr<Ray>m_playerRay;

	public:
		Tracking(const shared_ptr<Enemy> ptrOwner) :
			StateBase(ptrOwner),
			m_ownerPos(0, 0, 0),
			m_ownerRot(0, 0, 0),
			m_playerPos(0, 0, 0),
			m_forward(0, 0, 1),
			m_right(1, 0, 0)
		{
		}

		virtual ~Tracking() {}
		void OnStart();
		void OnUpdate();
		void OnExit();
	};

}
//end basecross
