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

		float m_mapSize;//�}�b�v�̒��a
		float m_mapMagnification;//�}�b�v�̔{��
	public:
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void CreateWall();//�~�j�}�b�v�̕ǂ𐶐�����
		void CreateItem();//�~�j�}�b�v�̃A�C�e���𐶐�����
		void CreateManhole();//�~�j�}�b�v�̃}���z�[���𐶐�����
		void CreateEnemy();//�~�j�}�b�v�̓G�𐶐�����

		Vec3 GetStartPos();//�~�j�}�b�v�̌��_��n��
	};

}
//end basecross
