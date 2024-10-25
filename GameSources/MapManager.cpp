/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MapManager::MapManager(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}
	MapManager::~MapManager()
	{
	}

	void MapManager::OnCreate()
	{

	}

	void MapManager::OnUpdate()
	{

	}

	//���[���h���W���Z�����W�ɕϊ�����
	Vec2 MapManager::MyMapNow(Vec3 worldPosition)
	{
		float length = ((worldPosition.x + 45) / 10.0f) + 0.5f;//���̃Z�����W
		float height = -((worldPosition.z - 45) / 10.0f) + 0.5f;//�c�̃Z�����W

		return Vec2((int)length, (int)height);

	}

}
//end basecross
