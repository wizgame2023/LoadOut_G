/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sky_base : public GameObject
	{
	public:
		Sky_base(const std::shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
		}

		void OnCreate() override;
	};
}
//end basecross