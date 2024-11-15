/*!
@file MiniMapManager.h
@brief �~�j�}�b�v
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MiniMapManager :public GameObject
	{
	private:
		Vec3 m_startPos;//�����ʒu(�s�|�b�g)
	public:
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void CreateWall();//�~�j�}�b�v�̕ǂ𐶐�����

		Vec3 GetStartPos();//�~�j�}�b�v�̌��_��n��
	};

}
//end basecross
