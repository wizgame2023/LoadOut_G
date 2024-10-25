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

	public:
		MapManager(shared_ptr<Stage>& stagePtr);//�R���X�g���N�^
		~MapManager();//�f�X�g���N�^

		void OnCreate()override;//����
		void OnUpdate()override;//�X�V

		Vec2 MyMapNow(Vec3 worldPosition);
	};


}
//end basecross
