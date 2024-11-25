/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MapManager :public GameObject
	{
	private:
		vector<vector<int>> m_stageMap;
		vector<vector<int>> m_aStarMap;//A*�̃}�b�v
		vector<int> m_aStarLine;//A*�̃}�b�v�̈�s

	public:
		MapManager(shared_ptr<Stage>& stagePtr);//�R���X�g���N�^
		~MapManager();//�f�X�g���N�^

		void OnCreate()override;//����
		void OnUpdate()override;//�X�V

		Vec2 ConvertSelMap(Vec3 worldPosition);

		void MapDataUpdate(Vec3 worldPosition,int change);
		int SelMapNow(Vec3 worldPosition);//���̃Z�����W�ɉ�������̂���Ԃ�

		void StageMapLoad();
		void WallMapLoad();
		void WallCreateKari();//���̕ǂ𐶐����悤
		void AddExctraAStar(int addArray);//�]����A*�ɔz������鏈��
		void AddArray(int loop,int num);//�z��ɐ��l�����鏈��

		vector<vector<int>> GetAStarMap();//A*�}�b�v�̎擾
	};


}
//end basecross
