/*!
@file Patrol.h
@brief èÑâÒ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Patrol :public StateBase
	{
	public:
		Patrol(const shared_ptr<Enemy> ptrOwner) :
			StateBase(ptrOwner)
		{
		}
		virtual ~Patrol() {}

		void OnStart();
		void OnUpdate();
		void OnExit();
	};
}
//end basecross
