/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Item :public GameObject
	{
	private:

	public:
		Item(shared_ptr<Stage>& stagePtr);
		~Item();

		void OnCreate()override;
		void OnUpdate()override;
	};


}
//end basecross
