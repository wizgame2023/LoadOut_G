/*!
@file Actor.h
@brief PlayerやEnemyなど動くオブジェクトの親クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Actor :public GameObject
	{
	private:
		float m_angle;//角度

	public:
		Actor(shared_ptr<Stage>& stagePtr);
		~Actor();

		virtual float GetAngle();
		virtual void SetAngle(float angle);

		//void OnCreate()override;
		//void OnUpdate()override;

		//void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

}
//end basecross
