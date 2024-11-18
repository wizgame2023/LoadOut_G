/*!
@file Wall.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Wall :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		Vec3 m_rot;//��]
		Vec3 m_scale;//�T�C�Y

		Vec3 m_miniMapStartPos;//�~�j�}�b�v�̒��S�_

	public:
		Wall(shared_ptr<Stage>& stagePtr, Vec3 pos, Vec3 rot,Vec3 miniMapStartPos,Vec3 scalse = Vec3(10.0f, 10.0f, 1.0f));//�R���X�g���N�^
		~Wall();//�f�X�g���N�^

		void MiniMapCreate(Vec3 miniMapStartPos);//�~�j�}�b�v�̎������g�𐶐�

		void OnCreate()override;//����
	};


}
//end basecross
