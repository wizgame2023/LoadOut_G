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
	};


}
//end basecross
