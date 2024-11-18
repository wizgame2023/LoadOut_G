/*!
@file Attack.h
@brief �U��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Attack :public StateBase
	{




	public:
		Attack(const shared_ptr<Enemy> ptrOwner) :
			StateBase(ptrOwner)
		{
		}

		virtual ~Attack() {}

		void OnStart();
		void OnUpdate();
		void OnExit();

	};

}
//end basecross
