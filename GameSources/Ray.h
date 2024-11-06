/*!
@file Ray.h
@brief レイ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Ray :public GameObject
	{
	private:
	public:
		Ray(shared_ptr<Stage>& stagePtr);//コンストラクタ
		~Ray();//デストラクタ

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

}
//end basecross
