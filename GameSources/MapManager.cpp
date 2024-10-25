/*!
@file MapManager.cpp
@brief �}�b�v�}�l�[�W���[
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
		StageMapLoad();
	}

	void MapManager::OnUpdate()
	{

	}

	//���[���h���W���Z�����W�ɕϊ�����
	Vec2 MapManager::ConvertSelMap(Vec3 worldPosition)
	{
		float length = ((worldPosition.x + 45) / 10.0f) + 0.5f;//���̃Z�����W
		float height = -((worldPosition.z - 45) / 10.0f) + 0.5f;//�c�̃Z�����W

		return Vec2((int)length, (int)height);

	}

	//csv�t�@�C�����Z���}�b�v�f�[�^�Ƃ��ĕϊ�����
	void MapManager::StageMapLoad()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";

		//�}�b�v�f�[�^
		vector<vector<int>> stageMap;

		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs(levelPath + L"Stage1.csv");
		if (ifs)
		{
			string line;
			while (getline(ifs,line))
			{
				vector<int> datas;
				line += ",";

				string data;
				istringstream ss(line);//�ǂݎ�������e���X�g���[���ɕϊ�����
				//��s���ϊ�
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//string�^����int�^�ɕύX
					datas.push_back(cellData);
				}
				//��ԍŏ��̍s�񂾂������Ă���
				m_stageMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}
		int a = 0;//�f�o�b�N�p
	}

	void MapManager::MapDataUpdate(int leght, int height,int change)
	{
		//���߂��z��̏ꏊ�ɐ��l��ύX������
		m_stageMap[leght][height] = change;
	}

}
//end basecross
