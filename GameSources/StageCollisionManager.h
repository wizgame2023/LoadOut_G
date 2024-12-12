/*!
@file StageCollisionManager.h
@brief �R���W�����̊Ǘ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageCollisionManager :public GameObject
	{
	private:
		bool m_CollisionSwhich;

		void CollisionActive(bool On);//�X�e�[�W��̗L���ȃR���W�����͈͂����߂�

	public:
		StageCollisionManager(shared_ptr<Stage>& stagePtr);
		~StageCollisionManager();

		void OnCreate()override;
		void OnUpdate()override;
		void SetCollisionSwhich(bool On);//�R���W�����͈͂����߂邽�߂̃t���O���擾����֐�

	};
}