/*!
@file YushinStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void YushinStage::CreateViewLight() {
		const Vec3 eye(0.0f, 250.0f, -200.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void YushinStage::CreateWall()
	{
		//auto path = App::GetApp()->GetDataDirWString();
		//auto levelPath = path + L"Levels/";
		//vector<vector<int>> stageMap;

		//ifstream ifs(levelPath += L"DebugStage.csv");
		//if (ifs)
		//{
		//	string line;
		//	while (getline(ifs, line))
		//	{
		//		vector<int> mapData;

		//		line += ",";
		//		string data;
		//		istringstream ss(line);
		//		while (getline(ss, data, ','))
		//		{
		//			int cellData = atoi(data.c_str());
		//			mapData.push_back(cellData);
		//		}

		//		stageMap.push_back(mapData);
		//	}
		//}

		//for (int r = 0; r < stageMap.size(); r++)
		//{
		//	for (int c = 0; c < stageMap[0].size(); c++)
		//	{
		//		Vec3 startPos((c * 10.0f) - 95, 0.05f, 95 - (r * 10.0f));
		//		switch (stageMap[r][c])
		//		{
		//		case 1:
		//			AddGameObject<Wall>(startPos, Vec3(0, 0, 0), Vec3(30.0, 10, 1.0));
		//			break;
		//		case 2:
		//			AddGameObject<Wall>(startPos, Vec3(0, 0, 0), Vec3(1.0, 10, 30.0));
		//			break;
		//		}
		//	}
		//}
	auto selLength = 20;
	auto wall = AddGameObject<Wall>(Vec3((selLength * 10.0f) / 2 + 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	AddGameObject<Wall>(Vec3(-(selLength * 10.0f) / 2 - 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	AddGameObject<Wall>(Vec3(0.0f, 0.0f, (-selLength * 10) / 2 - 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	AddGameObject<Wall>(Vec3(0.0f, 0.0f, (selLength * 10) / 2 + 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));

	}

	void YushinStage::CreateEnemy()
	{
		//AddGameObject<Enemy>(Vec3(0.0f, 2.5f, 0.0f));
		//AddGameObject<Enemy>(Vec3(95.0f, 2.5f, -95.0f));
		//AddGameObject<Enemy>(Vec3(95.0f, 2.5f, 95.0f));
		//AddGameObject<Enemy>(Vec3(-95.0f, 2.5f, -95.0f));
		auto group = CreateSharedObjectGroup(L"SeekGroup");
		//�z��̏�����
		vector<Vec3> vec = {
			{ -95.0f, 2.5f, 95.0f },
		};

		//�z�u�I�u�W�F�N�g�̍쐬
		for (size_t count = 0; count < vec.size(); count++) {
			auto ptr = AddGameObject<Enemy>(vec[count]);
			//�i���o�[�X�N�G�A���쐬���Ċ֘A������
			AddGameObject<NumberSquare>(ptr, count);
		}


	}
	void YushinStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			auto miniMapManager = AddGameObject<MiniMapManager>();//�~�j�}�b�v�����f�o�b�N�p
			SetSharedGameObject(L"MiniMapManager", miniMapManager);
			//Player�̐���
			auto ptrPlayer = AddGameObject<Player>(Vec3(50.0f, 3.0f, 50.0f), Vec3(0.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"Player", ptrPlayer);
			CreateWall();
			AddGameObject<Ground>();
			auto mapManager = AddGameObject<MapManager>();
			SetSharedGameObject(L"MapManager", mapManager);
			//mapManager->WallCreateKari();//���̓��ǂ𐶐�����

			CreateEnemy();

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
