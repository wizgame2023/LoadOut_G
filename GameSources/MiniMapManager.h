/*!
@file MiniMapManager.h
@brief �~�j�}�b�v
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MiniMapManager :public GameObject
	{
	private:
	public:
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V
	};

}
//end basecross
