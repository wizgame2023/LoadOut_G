/*!
@file RepopEnemy.h
@brief ���|�b�v���̓G�̓���
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
