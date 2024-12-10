/*!
@file Attack.h
@brief çUåÇ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Attack :public StateBase
	{
		int m_count;



	public:
		Attack(const shared_ptr<Enemy> ptrOwner) :
			StateBase(ptrOwner),
			m_count(0)
		{
		}

		virtual ~Attack() {}

		void OnStart();
		void OnUpdate();
		void OnExit();

	};

}
//end basecross
