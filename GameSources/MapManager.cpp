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
		UnityMapCreate();
	}

	void MapManager::OnUpdate()
	{
		if (m_UpdetaUnityMapFlag)
		{
			UnityMapCreate();
			m_UpdetaUnityMapFlag = false;
		}
	}

	//���[���h���W���Z�����W�ɕϊ�����
	Vec2 MapManager::ConvertSelMap(Vec3 worldPosition)
	{
		float length = ((worldPosition.x + m_push) / 10.0f) + 0.5f;//���̃Z�����W
		float height = -((worldPosition.z - m_push) / 10.0f) + 0.5f;//�c�̃Z�����W

		return Vec2((int)length, (int)height);

	}

	Vec3 MapManager::ConvertWorldMap(Vec2 selPosition)
	{
		float w_length = (selPosition.x * 10.0f) - m_push;
		float w_height = m_push - (selPosition.y * 10.0f);

		return Vec3(w_length, 0, w_height);
	}

	Vec2 MapManager::ConvertUnityMap(Vec2 selPosition)
	{
		int AStarLength = (selPosition.x) * 2 + 1;
		int AStarHeight = (selPosition.y) * 2 + 1;

		return Vec2(AStarLength, AStarHeight);
	}

	//AStar���W����Z�����W��
	Vec2 MapManager::ConvertU_S(Vec2 aStarPosition)
	{
		int Length = (aStarPosition.x - 1) / 2 ;
		int Height = (aStarPosition.y - 1) / 2 ;

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
			bool first = false;
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
		m_push = ((m_stageMap.size() * 10)/2 - 5);
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
					GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f)- m_push, 0.05f, m_push -(i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
					break;
				case 4://�n�b�`�쐬
					GetStage()->AddGameObject<Hatch>(Vec3((j * 10.0f) - m_push, 0.05f, m_push - (i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
					break;
				case 6://�o�b�e���[����
					//GetStage()->AddGameObject<Spanner>((j * 10.0f) - m_push, 0.05f, m_push - (i * 10.0f), Vec3(0.0f, 0.0f, 0.0f));
					break;
				case 7://�G�l�~�[����

					break;
				default:
					break;
				}
			}
		}

		GetStage()->AddGameObject<Ground>(m_stageMap,m_push);//������
		
	}

	//�ǐ����pcsv�t�@�C����ǂݍ���
	void MapManager::WallMapLoad()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/"+m_stageName;

		//��ɂ����
		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs(levelPath + L"UpWallMap.csv");
		if (ifs)
		{
			string line;
			bool first = false;
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
				m_upWallMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}
		//����
		for (int h = 0; h < m_upWallMap.size(); h++)
		{
			for (int w = 0; w < m_upWallMap[0].size(); w++)
			{
				switch (m_upWallMap[h][w])
				{
				case 1://���ǐ���
					GetStage()->AddGameObject<Wall>(Vec3((w * 10.0f) - m_push, 5.0f, m_push+5 - (h * 10.0f)), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					break;
				default:
					break;
				}
			}
		}


		//���ɂ����
		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs2(levelPath + L"RightWallMap.csv");
		if (ifs2)
		{
			string line;
			bool first = false;
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
				m_rightWallMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}

		//����
		for (int i = 0; i < m_rightWallMap.size(); i++)
		{
			for (int j = 0; j < m_rightWallMap[0].size(); j++)
			{
				switch (m_rightWallMap[i][j])
				{
				case 1://�c�ǐ���
					GetStage()->AddGameObject<Wall>(Vec3((j * 10.0f) - m_push+5 - 10, 5.0f, m_push - (i * 10.0f)), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					break;

				default:
					break;
				}
			}
		}



	}

	//�}�b�v�̕ǂ̔z�u��ύX���鏈��//�쐬�r��
	void MapManager::MapChange()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/" + m_stageName;

		//����������
		m_upWallMap.clear();
		m_rightWallMap.clear();

		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = stage->GetGameObjectVec();

		//�O�̕ǂ̏�������
		for (auto wall : obj)
		{
			auto castWall = dynamic_pointer_cast<Wall>(wall);
			if (castWall)//Enemy�^�ɃL���X�g����
			{
				stage->RemoveGameObject<Wall>(wall);
			}
		}


		//��ɂ����
		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs(levelPath + L"UpriseWallMap.csv");
		if (ifs)
		{
			string line;
			bool first = false;
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
				m_upWallMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}
		//����
		for (int h = 0; h < m_upWallMap.size(); h++)
		{
			for (int w = 0; w < m_upWallMap[0].size(); w++)
			{
				switch (m_upWallMap[h][w])
				{
				case 1://���ǐ���
					//GetStage()->AddGameObject<Block>();
					GetStage()->AddGameObject<Wall>(Vec3((w * 10.0f) - m_push, 5.0f, m_push + 5 - (h * 10.0f)), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					break;
				default:
					break;
				}
			}
		}

		//���ɂ����
		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs2(levelPath + L"RightriseWallmap.csv");
		if (ifs2)
		{
			string line;
			bool first = false;
			while (getline(ifs2, line))
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
				m_rightWallMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}

		//����
		for (int i = 0; i < m_rightWallMap.size(); i++)
		{
			for (int j = 0; j < m_rightWallMap[0].size(); j++)
			{
				switch (m_rightWallMap[i][j])
				{
				case 1://�c�ǐ���
					GetStage()->AddGameObject<Wall>(Vec3((j * 10.0f) - m_push + 5 - 10, 5.0f, m_push - (i * 10.0f)), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					//GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f) - 95, 0.05f, 95 - (i * 10.0f)));//�u���b�N�̃s�|�b�g���^�񒆂̂�����100�łȂ�95�ɂȂ��Ă��܂�
					break;

				default:
					break;
				}
			}
		}

		//Unity�}�b�v�̍X�V�����̃t���O�𗧂Ă�
		m_UpdetaUnityMapFlag = true;
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


	void MapManager::UnityMapCreate()
	{
		m_unityMap.clear();//������
		for (int y = 0; y < (m_stageMap.size() * 2)+1; y++)
		{

			int count = 0;
			count = 0;//���Z�b�g

			for (int x = 0; x < (m_stageMap[0].size() * 2)+1; x++)
			{
				bool evenX;//�c���������ǂ���
				bool evenY;//�����������ǂ���

				////�c�Ɖ�����������̐��l�����m�F����
				evenX = x % 2 == 0 ? false : true;
				evenY = y % 2 == 0 ? false : true;

				//x��y�������Ȃ��
				if (!evenX && !evenY)
				{
					m_unityLine.push_back(0);
				}
				//x������y����Ȃ�c��
				if (!evenX && evenY)
				{
					int originY = y / 2;//�����_�ȉ��؂�̂�
					int originX = x / 2;

					m_unityLine.push_back(m_rightWallMap[originY][originX]);
				}
				//x���y�������Ȃ牡��
				if (evenX && !evenY)
				{
					int originY = y / 2;//�����_�ȉ��؂�̂�
					int originX = x / 2;

					m_unityLine.push_back(m_upWallMap[originY][originX]);
				}
				//x��y����Ȃ�n��
				if (evenX && evenY)
				{
					int originY = y / 2;//�����_�ȉ��؂�̂�
					int originX = x / 2;

					m_unityLine.push_back(m_stageMap[originY][originX]);
				}
			}

			count = 0;//���Z�b�g

			//aStarMap��A���̈�s���z�������
			m_unityMap.push_back(m_unityLine);
			m_unityLine.clear();//�g��Ȃ��z��͍폜
			auto a = 0;

		}

	}

	//�z��ɐ��l�����鏈��
	void MapManager::AddArray(int loop, int num)
	{
		int count = 0;
		//�]���ɔz�������
		while (count < 2)
		{
			count++;
			m_unityLine.push_back(9);
		}
		count = 0;//���Z�b�g
	}

	//A�X�^�[�ɂ�����x�]���ɔz������鏈��
	void MapManager::AddExctraUnity(int addArray)
	{
		//�͈͊O�̔z����w�肵�ăG���[�͂��Ȃ��悤�ɂ�����x�]���ɔz������Ă���
		vector<int> extra;//�]���ɓ����z��
		for (int i = 0; i < (m_stageMap.size() * 2)+4; i++)
		{
			extra.push_back(9);//A*�̂��z��Ԃ����Ă���
		}

		int count = 0;//���قǔz������Ă��邩������ϐ�
		while (count < addArray)
		{
			count++;
			m_unityMap.push_back(extra);//�z���]���ɓ���Ă���
		}
		m_unityMap;

	}

	//A*�}�b�v��n��
	vector<vector<int>> MapManager::GetUnityMap()
	{
		return m_unityMap;
	}

	vector<vector<int>> MapManager::TestAStar()
	{
		auto path = App::GetApp()->GetDataDirWString();
		wstring stage = L"testStage/";
		auto levelPath = path + L"Levels/" + stage;

		vector<vector<int>> testMap;
		//csv�t�@�C������f�[�^��ǂݍ���
		ifstream ifs(levelPath + L"GroundMap.csv");
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
				testMap.push_back(datas);//��s���}�b�v�f�[�^�����Ă���
			}
		}
		

		return testMap;
	}

	void MapManager::SetUpdataUnityMapFlag(bool flag)
	{
		m_UpdetaUnityMapFlag = flag;
	}

	//�}�b�v�̃T�C�Y��n��
	float MapManager::GetMapSize()
	{
		return m_stageMap.size() * 10;
	}

}
//end basecross
