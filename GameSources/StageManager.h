/*!
@file StageManager.h
@brief �X�e�[�W�̐i�s���Ǘ�����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageManager :public GameObject
	{
	private:

	public:
		StageManager(shared_ptr<Stage>& stagePtr);
		~StageManager();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
