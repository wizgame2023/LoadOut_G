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
		vector<vector<int>> m_upWallMap;
		vector<vector<int>> m_rightWallMap;
		vector<vector<int>> m_unityMap;//A*�̃}�b�v
		vector<int> m_unityLine;//A*�̃}�b�v�̈�s
		wstring m_stageName;//�X�e�[�W�̖��O

		float m_mapSize;//�}�b�v�̃T�C�Y(���a)
		float m_push;//��C�ɃI�u�W�F�N�g��������ۂɃG�N�Z���̍��W�ƍ��킹�邽�߂̐��l

		bool m_UpdetaUnityMapFlag;//UnityMap�̍X�V

	public:
		enum SelMapCount
		{
			Map_None = 0,
			Map_Manhole,
			Map_ManholeSet,
			Map_ManholeOpen,
			Map_ExitNone,
			Map_ExitOpen,
			Map_Item
		};
		MapManager(shared_ptr<Stage>& stagePtr,wstring stageName=L"Stage01/");//�R���X�g���N�^
		~MapManager();//�f�X�g���N�^

		void OnCreate()override;//����
		void OnUpdate()override;//�X�V

		Vec2 ConvertSelMap(Vec3 worldPosition);//���[���h���W����Z�����W�ɕς���
		Vec3 ConvertWorldMap(Vec2 selPosition);
		Vec2 ConvertUnityMap(Vec2 selPosition);
		Vec2 ConvertU_S(Vec2 AStarPosition);//AStar����Z���}�b�v�ɕς���

		void MapDataUpdate(Vec3 worldPosition,int change);
		int SelMapNow(Vec3 worldPosition);//���̃Z�����W�ɉ�������̂���Ԃ�

		void StageMapLoad();
		void WallMapLoad();
		void UnityMapCreate();//A*�}�b�v�̍쐬
		void WallCreate();//�ǂ𐶐�
		void AddExctraUnity(int addArray);//�]����A*�ɔz������鏈��
		void AddArray(int loop,int num);//�z��ɐ��l�����鏈��

		void SetUpdataUnityMapFlag(bool flag);

		float GetMapSize();//�}�b�v�̃T�C�Y��n������

		vector<vector<int>> TestAStar();//A*�̃e�X�g�p�̃}�b�v�擾

		vector<vector<int>> GetUnityMap();//A*�}�b�v�̎擾
	};


}
//end basecross
