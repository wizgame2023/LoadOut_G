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

	protected:
		bool m_move;//�����������Ȃ����̃t���O
		Vec2 m_selPosNow;//���݂̃Z�����W��ۑ�����ϐ�
		Vec2 m_selPosBefor;//�O�����Z�����W��ۑ�����ϐ�

	public:
		Actor(shared_ptr<Stage>& stagePtr);
		~Actor();

		virtual void OnUpdate()override;

		virtual float GetAngle();
		Vec2 GetSelPosNow();//���݂̃Z�����W�̃Q�b�^�[
		Vec2 GetSelPosBefor();//�O�ɂ����Z�����W�̃Q�b�^�[

		virtual void SetAngle(float angle);

		void MoveSwitch(bool onOff);//�����Ă������̃t���O

		//void OnCreate()override;
		//void OnUpdate()override;

		//void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

}
//end basecross
