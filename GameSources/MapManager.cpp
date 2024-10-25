/*!
@file MapManager.cpp
@brief マップマネージャー
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

	//ワールド座標をセル座標に変換する
	Vec2 MapManager::ConvertSelMap(Vec3 worldPosition)
	{
		float length = ((worldPosition.x + 45) / 10.0f) + 0.5f;//横のセル座標
		float height = -((worldPosition.z - 45) / 10.0f) + 0.5f;//縦のセル座標

		return Vec2((int)length, (int)height);

	}

	//csvファイルをセルマップデータとして変換する
	void MapManager::StageMapLoad()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";

		//マップデータ
		vector<vector<int>> stageMap;

		//csvファイルからデータを読み込む
		ifstream ifs(levelPath + L"Stage1.csv");
		if (ifs)
		{
			string line;
			while (getline(ifs,line))
			{
				vector<int> datas;
				line += ",";

				string data;
				istringstream ss(line);//読み取った内容をストリームに変換する
				//一行ずつ変換
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//string型からint型に変更
					datas.push_back(cellData);
				}
				//一番最初の行列だけ消えている
				m_stageMap.push_back(datas);//一行ずつマップデータを入れている
			}
		}
		int a = 0;//デバック用
	}

	void MapManager::MapDataUpdate(int leght, int height,int change)
	{
		//決めた配列の場所に数値を変更させる
		m_stageMap[leght][height] = change;
	}

}
//end basecross
