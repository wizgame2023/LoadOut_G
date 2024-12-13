/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Item :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		Vec3 m_rot;//��]

	public:
		Item(shared_ptr<Stage>& stagePtr,Vec3 pos,Vec3 rot);
		~Item();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};


}
//end basecross
