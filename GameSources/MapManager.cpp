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
		float length = ((worldPosition.x + 95) / 10.0f) + 0.5f;//���̃Z�����W
		float height = -((worldPosition.z - 95) / 10.0f) + 0.5f;//�c�̃Z�����W

		return Vec2((int)length, (int)height);

	}

	//csv�t�@�C�����Z���}�b�v�f�[�^�Ƃ��ĕϊ�����
	void MapManager::StageMapLoad()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";

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

		int a = m_stageMap[0].size();//�f�o�b�N�p

		//csv�t�@�C������ǂݎ���ď��֌W�̃I�u�W�F�N�g�̐�������
		for (int i = 0; i < m_stageMap.size(); i++)
		{
			for (int j = 0; j < m_stageMap[0].size(); j++)
			{
				int y = m_stageMap.size();
				int b = m_stageMap[0].size();
				int test = 0;
				switch (m_stageMap[i][j])
				{
				case 1://�}���z�[������
					GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f)-95, 0.05f, 95-(i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
					break;

				default:
					break;
				}
			}
		}

		
	}

	//�ǐ����pcsv�t�@�C����ǂݍ���
	void MapManager::WallMapLoad()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";

		//�}�b�v�f�[�^
		vector<vector<int>> wallMap;

		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs(levelPath + L"Stage1.csv");
		if (ifs)
		{
			string line;
			while (getline(ifs, line))
			{
				vector<int> datas;
				line += ",";

				string data;
				istringstream ss(line);//�ǂݎ�������e���X�g���[���ɕϊ�����
				//��s���ϊ�
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//string�^����int�^�ɕύX
					if (cellData != 0)//�����A���̃Z���f�[�^���ǂɊ֌W�Ȃ����ł���Εǐ����p�̂̔z��ɓ���Ȃ�
					{
						datas.push_back(cellData);
					}
				}
				//��ԍŏ��̍s�񂾂������Ă���
				wallMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}

		int a = 0;//�f�o�b�N�p

		for (int h = 0; h < wallMap.size(); h++)
		{
			for (int w = 0; w < wallMap[0].size(); w++)
			{
				switch (wallMap[h][w])
				{
				case 1://���E�ǐ���
					//GetStage()->AddGameObject<Block>();
					break;
				case 2://�㉺�ǐ���
					//GetStage()->AddGameObject<Block>();
					break;
				default:
					break;
				}
			}
		}

	}

	//�Z���}�b�v�Ƀ}���z�[���Ȃǂ�u������
	void MapManager::MapDataUpdate(Vec3 worldPosition,int change)
	{
		Vec2 SelPos = ConvertSelMap(worldPosition);

		//���߂��z��̏ꏊ�ɐ��l��ύX������
		m_stageMap[SelPos.y][SelPos.x] = change;
	}


	//���̃Z�����W�ɉ�������̂���Ԃ�
	int MapManager::SelMapNow(Vec3 worldPosition)
	{
		Vec2 SelPos = ConvertSelMap(worldPosition);

		return m_stageMap[SelPos.y][SelPos.x];
	}

	void MapManager::WallCreateKari()
	{//��
		vector<vector<int>> test_walls_up =
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
			{0,0,0,0,1,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
			{0,1,0,0,0,0,0,1,1,1,1,1,0,1,1,1,0,0,0,0},
			{0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,1,1,0,0,0},
			{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
			{0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,0,1,1,1,0},
			{0,0,0,1,0,1,1,1,0,0,1,1,1,0,0,0,0,1,0,0},
			{0,0,0,0,0,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0},
			{0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1},
			{0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0},
			{0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0},
			{0,0,1,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0},
			{0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0},
			{0,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0},
			{0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0},
			{0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0},
			{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,0,1,0,0,1,0,1,1,1,1,1,1,0,0,0,0}
		};
		//csv�t�@�C������ǂݎ���ď��֌W�̃I�u�W�F�N�g�̐�������
		for (int i = 0; i < test_walls_up.size(); i++)
		{
			for (int j = 0; j < test_walls_up[0].size(); j++)
			{
				int y = test_walls_up.size();
				int b = test_walls_up[0].size();
				int test = 0;
				switch (test_walls_up[i][j])
				{
				case 1://���ǐ���
					GetStage()->AddGameObject<Wall>(Vec3((j * 10.0f) - 95, 5.0f, 100 - (i * 10.0f)), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					//GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f) - 95, 0.05f, 95 - (i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
					break;

				default:
					break;
				}
			}
		}

		
		
		//�c
		vector<vector<int>> test_walls_right =
		{
			{0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0},
			{0,1,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,1,1,1},
			{0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1},
			{0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
			{0,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0,1,1,1},
			{0,0,1,0,1,1,0,0,0,0,1,0,1,1,1,1,1,0,0,0},
			{0,0,1,0,0,0,0,0,1,0,1,0,0,1,1,1,1,0,0,1},
			{0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,1,1,0,1,1},
			{0,1,0,1,1,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
			{0,1,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0},
			{0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,1,0,0,0},
			{0,0,0,0,0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,1},
			{0,1,0,0,1,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0},
			{0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1},
			{0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,1,1,0,1},
			{0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
			{0,1,0,1,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,0,1,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1},
			{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0}


		};

		for (int i = 0; i < test_walls_right.size(); i++)
		{
			for (int j = 0; j < test_walls_right[0].size(); j++)
			{
				int y = test_walls_right.size();
				int b = test_walls_right[0].size();
				int test = 0;
				switch (test_walls_right[i][j])
				{
				case 1://���ǐ���
					GetStage()->AddGameObject<Wall>(Vec3((j * 10.0f) - 100, 5.0f, 95 - (i * 10.0f)), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					//GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f) - 95, 0.05f, 95 - (i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
					break;

				default:
					break;
				}
			}
		}


	}

}
//end basecross
