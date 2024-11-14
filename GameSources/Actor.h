/*!
@file Actor.h
@brief Player��Enemy�ȂǓ����I�u�W�F�N�g�̐e�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Actor :public GameObject
	{
	private:
		float m_angle;//�p�x

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
