/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MyCamera :public Camera
	{
	private:
		Vec3 m_Pos;//位置
	public:
		MyCamera(Vec3 pos);
		~MyCamera();

		void OnCreate()override;
		void OnUpdate()override;
	};


}
//end basecross
