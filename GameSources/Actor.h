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

	protected:
		bool m_move;//動くか動かないかのフラグ

	public:
		Actor(shared_ptr<Stage>& stagePtr);
		~Actor();

		virtual float GetAngle();
		virtual void SetAngle(float angle);

		void MoveSwich(bool onOff);//動いていいかのフラグ

		//void OnCreate()override;
		//void OnUpdate()override;

		//void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

}
//end basecross
