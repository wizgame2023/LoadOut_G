/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Battery :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		Vec3 m_rot;//��]

		bool m_updateFlag;//�A�b�v�f�[�g���邩�̃t���O

	public:
		Battery(shared_ptr<Stage>& stagePtr,Vec3 pos,Vec3 rot);
		~Battery();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		void SetUpdateSwitch(bool onOff);
	};


}
//end basecross
