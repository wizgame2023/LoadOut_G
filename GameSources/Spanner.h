/*!
@file Spanner.h
@brief �X�p�i(�}���z�[����ł��グ�邽�߂̃A�C�e��)
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Spanner :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		Vec3 m_rot;//��]

		bool m_updateFlag;//�A�b�v�f�[�g���邩�̃t���O

	public:
		Spanner(shared_ptr<Stage>& stagePtr,Vec3 pos,Vec3 rot);
		~Spanner();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		void SetUpdateSwitch(bool onOff);
	};


}
//end basecross
