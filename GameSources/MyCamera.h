/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MyCamera :public Camera
	{
	private:
	public:
		MyCamera();
		~MyCamera();

		void OnCreate()override;
		void OnUpdate()override;
	};


}
//end basecross
