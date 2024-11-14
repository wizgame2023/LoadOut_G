/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ClearObject :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		Vec3 m_rot;//��]

	public:
		ClearObject(shared_ptr<Stage>& stagePtr, Vec3 pos, Vec3 rot);
		~ClearObject();

		void OnCreate()override;
		void OnUpdate()override;

		//void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};




}
//end basecross
