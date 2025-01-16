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

		int m_beforeItemNum;//�O�̃A�C�e���̌�
		int m_beforeEnemyNum;//�O�̓G�̐�

		float m_mapSize;//�}�b�v�̒��a
		float m_mapMagnification;//�}�b�v�̔{��
	public:
		MiniMapManager(shared_ptr<Stage>& stage, float mapSize);
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void CreateWall();//�~�j�}�b�v�̕ǂ𐶐�����
		void CreateBattery();//�~�j�}�b�v�̃A�C�e���𐶐�����
		void CreateManhole();//�~�j�}�b�v�̃}���z�[���𐶐�����
		//void CreateWall();//�~�j�}�b�v�̕ǂ𐶐�����
		void CreateEnemy();//�~�j�}�b�v�̓G�𐶐�����
		void CreatePlayer();//�~�j�}�b�v�̃v���C���[�𐶐�����

		void UpdateBattery();//�~�j�}�b�v�̃A�C�e���\��(Update��)
		void UpdateEnemy();//�~�j�}�b�v�̓G�\��(Update��)

		Vec3 GetStartPos();//�~�j�}�b�v�̌��_��n��
	};

}
//end basecross
