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
		Vec3 m_Pos;//�ʒu
	public:
		MyCamera(Vec3 pos);
		~MyCamera();

		void OnCreate()override;
		void OnUpdate()override;
	};


}
//end basecross
