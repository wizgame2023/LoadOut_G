/*!
@file RepopEnemy.h
@brief ƒŠƒ|ƒbƒvŽž‚Ì“G‚Ì“®‚«
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RepopEnemy :public StateBase
	{
	private:
		
	public:
		RepopEnemy(shared_ptr<Enemy> ptrOwner);
		~RepopEnemy();

		void OnCreate();
		void OnUpdate();
	};

}
//end basecross
