/*!
@file MapManager.cpp
@brief �}�b�v�}�l�[�W���[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MapManager::MapManager(shared_ptr<Stage>& stagePtr,wstring stageName):
		GameObject(stagePtr),
		m_stageName(stageName)
	{

	}
	MapManager::~MapManager()
	{
	}

	void MapManager::OnCreate()
	{
		StageMapLoad();
		WallMapLoad();
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

	Vec3 MapManager::ConvertWorldMap(Vec2 selPosition)
	{
		float w_length = (selPosition.x * 10.0f) - 95.0f;
		float w_height = 95.0f - (selPosition.y * 10.0f);

		return Vec3(w_length, 0, w_height);
	}

	Vec2 MapManager::ConvertAStarMap(Vec2 selPosition)
	{
		int AStarLength = selPosition.x * 2 + 1 + 2;
		int AStarHeight = selPosition.y * 2 + 1 + 2;

		return Vec2(AStarLength, AStarHeight);
	}

	//AStar���W����Z�����W��
	Vec2 MapManager::ConvertA_S(Vec2 aStarPosition)
	{
		int Length = (aStarPosition.x - 1 - 2) / 2 ;
		int Height = (aStarPosition.y - 1 - 2) / 2 ;

		return Vec2(Length, Height);

	}

	//csv�t�@�C�����Z���}�b�v�f�[�^�Ƃ��ĕϊ�����
	void MapManager::StageMapLoad()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/"+m_stageName;

		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs(levelPath + L"GroundMap.csv");
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

				case 4://�n�b�`�쐬
					GetStage()->AddGameObject<Hatch>(Vec3((j * 10.0f) - 95, 0.05f, 95 - (i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
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
		wstring stage = L"Stage01/";
		auto levelPath = path + L"Levels/"+stage;

		//�}�b�v�f�[�^
		vector<vector<int>> upWallMap;

		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs(levelPath + L"UpWallMap.csv");
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
					datas.push_back(cellData);
				}
				//��ԍŏ��̍s�񂾂������Ă���
				upWallMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}

		int a = 0;//�f�o�b�N�p

		for (int h = 0; h < upWallMap.size(); h++)
		{
			for (int w = 0; w < upWallMap[0].size(); w++)
			{
				switch (upWallMap[h][w])
				{
				case 1://���ǐ���
					//GetStage()->AddGameObject<Block>();
					GetStage()->AddGameObject<Wall>(Vec3((w * 10.0f) - 95, 5.0f, 100 - (h * 10.0f)), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					break;
				default:
					break;
				}
			}
		}



		//�}�b�v�f�[�^
		vector<vector<int>> RightWallMap;

		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs2(levelPath + L"RightWallMap.csv");
		if (ifs2)
		{
			string line;
			while (getline(ifs2,line))
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
				RightWallMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}

		for (int i = 0; i < RightWallMap.size(); i++)
		{
			for (int j = 0; j < RightWallMap[0].size(); j++)
			{
				switch (RightWallMap[i][j])
				{
				case 1://�c�ǐ���
					GetStage()->AddGameObject<Wall>(Vec3((j * 10.0f) - 100, 5.0f, 95 - (i * 10.0f)), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					//GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f) - 95, 0.05f, 95 - (i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
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

	void MapManager::WallCreate()
	{

	}

	void MapManager::WallCreateKari()//���̏����͂����g��Ȃ�
	{//��
		vector<vector<int>> test_walls_up =
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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
			{0,0,1,1,0,1,0,0,1,0,1,1,1,1,1,1,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

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
			{1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1},
			{1,1,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,1,1,1,1},
			{1,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,1},
			{1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
			{1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0,1,1,1,1},
			{1,0,1,0,1,1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,1},
			{1,0,1,0,0,0,0,0,1,0,1,0,0,1,1,1,1,0,0,1,1},
			{1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,1,1,0,1,1,1},
			{1,1,0,1,1,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1,1},
			{1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1},
			{1,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,1,0,0,0,1},
			{1,0,0,0,0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1},
			{1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,1,1},
			{1,1,0,0,1,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,1},
			{1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1},
			{1,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,1,1,0,1,1},
			{1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1},
			{1,1,0,1,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,1},
			{1,1,1,0,1,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1},
			{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1}


		};

		//Math masu;
		//masu->Get

		for (int i = 0; i < test_walls_right.size(); i++)
		{
			for (int j = 0; j < test_walls_right[0].size(); j++)
			{
				int y = test_walls_right.size();
				int b = test_walls_right[0].size();
				int test = 0;
				switch (test_walls_right[i][j])
				{
				case 1://�c�ǐ���
					GetStage()->AddGameObject<Wall>(Vec3((j * 10.0f) - 100, 5.0f, 95 - (i * 10.0f)), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					//GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f) - 95, 0.05f, 95 - (i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
					break;

				default:
					break;
				}
			}
		}


		//A*�p�}�b�v�쐻
		AddExctraAStar(2);//A�X�^�[�ɗ]���ɔz�������

		for (int y=0; y < m_stageMap.size() * 2; y++)
		{

			int count = 0;
			//�]���ɔz�������
			while (count < 2)
			{
				count++;
				m_aStarLine.push_back(9);
			}
			count = 0;//���Z�b�g

			for (int x=0; x < m_stageMap[0].size() * 2; x++)
			{
				bool evenX;//�c���������ǂ���
				bool evenY;//�����������ǂ���

				////�c�Ɖ�����������̐��l�����m�F����
				evenX = x % 2 == 0 ? false : true;
				evenY = y % 2 == 0 ? false : true;

				//x��y����Ȃ��
				if (!evenX && !evenY)
				{
					m_aStarLine.push_back(0);
				}
				//x���y�������Ȃ�c��
				if (!evenX && evenY)
				{
					int originY = y / 2;//�����_�ȉ��؂�̂�
					int originX = x / 2;

					m_aStarLine.push_back(test_walls_right[originY][originX]);
				}
				//x������y����Ȃ牡��
				if (evenX && !evenY)
				{
					int originY = y / 2;//�����_�ȉ��؂�̂�
					int originX = x / 2;

					m_aStarLine.push_back(test_walls_up[originY][originX]);
				}
				//x��y�������Ȃ�n��
				if (evenX && evenY)
				{
					int originY = y / 2;//�����_�ȉ��؂�̂�
					int originX = x / 2;

					m_aStarLine.push_back(m_stageMap[originY][originX]);
				}
			}

			//�]���ɔz�������
			while (count < 2)
			{
				count++;
				m_aStarLine.push_back(9);
			}
			count = 0;//���Z�b�g


			//aStarMap��A���̈�s���z�������
			m_aStarMap.push_back(m_aStarLine);
			m_aStarLine.clear();//�g��Ȃ��z��͍폜
			auto a = 0;

		}
		m_aStarMap;
		AddExctraAStar(2);//A�X�^�[�ɗ]���ɔz�������
		auto test=0;
	}

	//�z��ɐ��l�����鏈��
	void MapManager::AddArray(int loop, int num)
	{
		int count = 0;
		//�]���ɔz�������
		while (count < 2)
		{
			count++;
			m_aStarLine.push_back(9);
		}
		count = 0;//���Z�b�g
	}

	//A�X�^�[�ɂ�����x�]���ɔz������鏈��
	void MapManager::AddExctraAStar(int addArray)
	{
		//�͈͊O�̔z����w�肵�ăG���[�͂��Ȃ��悤�ɂ�����x�]���ɔz������Ă���
		vector<int> extra;//�]���ɓ����z��
		for (int i = 0; i < m_stageMap.size() * 2; i++)
		{
			extra.push_back(9);//A*�̂��z��Ԃ����Ă���
		}

		int count = 0;//���قǔz������Ă��邩������ϐ�
		while (count < addArray)
		{
			count++;
			m_aStarMap.push_back(extra);//�z���]���ɓ���Ă���
		}
		m_aStarMap;

	}

	//A*�}�b�v��n��
	vector<vector<int>> MapManager::GetAStarMap()
	{
		return m_aStarMap;
	}

}
//end basecross
