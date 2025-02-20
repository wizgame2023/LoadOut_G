/*!
@file MapManager.cpp
@brief マップマネージャー
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

	//ワールド座標をセル座標に変換する
	Vec2 MapManager::ConvertSelMap(Vec3 worldPosition)
	{
		float length = ((worldPosition.x + m_push) / 10.0f) + 0.5f;//横のセル座標
		float height = -((worldPosition.z - m_push) / 10.0f) + 0.5f;//縦のセル座標

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

	//AStar座標からセル座標へ
	Vec2 MapManager::ConvertU_S(Vec2 aStarPosition)
	{
		int Length = (aStarPosition.x - 1) / 2 ;
		int Height = (aStarPosition.y - 1) / 2 ;

		return Vec2(Length, Height);

	}

	//csvファイルをセルマップデータとして変換する
	void MapManager::StageMapLoad()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/"+m_stageName;

		//csvファイルからデータを読み込む
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
		m_push = ((m_stageMap.size() * 10)/2 - 5);
		int a = m_stageMap[0].size();//デバック用

		//csvファイルから読み取って床関係のオブジェクトの生成する
		for (int i = 0; i < m_stageMap.size(); i++)
		{
			for (int j = 0; j < m_stageMap[0].size(); j++)
			{
				int y = m_stageMap.size();
				int b = m_stageMap[0].size();
				int test = 0;
				switch (m_stageMap[i][j])
				{
				case 1://マンホール生成
					GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f)- m_push, 0.05f, m_push -(i * 10.0f)));//ブロックのピポットが真ん中のせいで100でなく95になっています
					break;
				case 4://ハッチ作成
					GetStage()->AddGameObject<Hatch>(Vec3((j * 10.0f) - m_push, 0.05f, m_push - (i * 10.0f)));//ブロックのピポットが真ん中のせいで100でなく95になっています
					break;
				case 6://バッテリー生成
					//GetStage()->AddGameObject<Spanner>((j * 10.0f) - m_push, 0.05f, m_push - (i * 10.0f), Vec3(0.0f, 0.0f, 0.0f));
					break;
				case 7://エネミー生成

					break;
				default:
					break;
				}
			}
		}

		GetStage()->AddGameObject<Ground>(m_stageMap,m_push);//床生成
		
	}

	//壁生成用csvファイルを読み込む
	void MapManager::WallMapLoad()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/"+m_stageName;

		//上にある壁
		//csvファイルからデータを読み込む
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
				istringstream ss(line);//読み取った内容をストリームに変換する
				//一行ずつ変換
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//string型からint型に変更
					datas.push_back(cellData);
				}
				//一番最初の行列だけ消えている
				m_upWallMap.push_back(datas);//一行ずつマップデータを入れている
			}
		}
		//生成
		for (int h = 0; h < m_upWallMap.size(); h++)
		{
			for (int w = 0; w < m_upWallMap[0].size(); w++)
			{
				switch (m_upWallMap[h][w])
				{
				case 1://横壁生成
					GetStage()->AddGameObject<Wall>(Vec3((w * 10.0f) - m_push, 5.0f, m_push+5 - (h * 10.0f)), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					break;
				default:
					break;
				}
			}
		}


		//左にある壁
		//csvファイルからデータを読み込む
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
				istringstream ss(line);//読み取った内容をストリームに変換する
				//一行ずつ変換
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//string型からint型に変更
					datas.push_back(cellData);
				}

				//一番最初の行列だけ消えている
				m_rightWallMap.push_back(datas);//一行ずつマップデータを入れている
			}
		}

		//生成
		for (int i = 0; i < m_rightWallMap.size(); i++)
		{
			for (int j = 0; j < m_rightWallMap[0].size(); j++)
			{
				switch (m_rightWallMap[i][j])
				{
				case 1://縦壁生成
					GetStage()->AddGameObject<Wall>(Vec3((j * 10.0f) - m_push+5 - 10, 5.0f, m_push - (i * 10.0f)), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					break;

				default:
					break;
				}
			}
		}



	}

	//マップの壁の配置を変更する処理//作成途中
	void MapManager::MapChange()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/" + m_stageName;

		//初期化処理
		m_upWallMap.clear();
		m_rightWallMap.clear();

		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto obj = stage->GetGameObjectVec();

		//前の壁の消去処理
		for (auto wall : obj)
		{
			auto castWall = dynamic_pointer_cast<Wall>(wall);
			if (castWall)//Enemy型にキャストする
			{
				stage->RemoveGameObject<Wall>(wall);
			}
		}


		//上にある壁
		//csvファイルからデータを読み込む
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
				istringstream ss(line);//読み取った内容をストリームに変換する
				//一行ずつ変換
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//string型からint型に変更
					datas.push_back(cellData);
				}
				//一番最初の行列だけ消えている
				m_upWallMap.push_back(datas);//一行ずつマップデータを入れている
			}
		}
		//生成
		for (int h = 0; h < m_upWallMap.size(); h++)
		{
			for (int w = 0; w < m_upWallMap[0].size(); w++)
			{
				switch (m_upWallMap[h][w])
				{
				case 1://横壁生成
					//GetStage()->AddGameObject<Block>();
					GetStage()->AddGameObject<Wall>(Vec3((w * 10.0f) - m_push, 5.0f, m_push + 5 - (h * 10.0f)), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					break;
				default:
					break;
				}
			}
		}

		//左にある壁
		//csvファイルからデータを読み込む
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
				istringstream ss(line);//読み取った内容をストリームに変換する
				//一行ずつ変換
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//string型からint型に変更
					datas.push_back(cellData);
				}

				//一番最初の行列だけ消えている
				m_rightWallMap.push_back(datas);//一行ずつマップデータを入れている
			}
		}

		//生成
		for (int i = 0; i < m_rightWallMap.size(); i++)
		{
			for (int j = 0; j < m_rightWallMap[0].size(); j++)
			{
				switch (m_rightWallMap[i][j])
				{
				case 1://縦壁生成
					GetStage()->AddGameObject<Wall>(Vec3((j * 10.0f) - m_push + 5 - 10, 5.0f, m_push - (i * 10.0f)), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(9.5f, 5.0f, 1.0f));
					//GetStage()->AddGameObject<Manhole>(Vec3((j * 10.0f) - 95, 0.05f, 95 - (i * 10.0f)));//ブロックのピポットが真ん中のせいで100でなく95になっています
					break;

				default:
					break;
				}
			}
		}

		//Unityマップの更新処理のフラグを立てる
		m_UpdetaUnityMapFlag = true;
	}

	//セルマップにマンホールなどを置く処理
	void MapManager::MapDataUpdate(Vec3 worldPosition,int change)
	{
		Vec2 SelPos = ConvertSelMap(worldPosition);

		//決めた配列の場所に数値を変更させる
		m_stageMap[SelPos.y][SelPos.x] = change;
	}


	//今のセル座標に何があるのかを返す
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
		m_unityMap.clear();//初期化
		for (int y = 0; y < (m_stageMap.size() * 2)+1; y++)
		{

			int count = 0;
			count = 0;//リセット

			for (int x = 0; x < (m_stageMap[0].size() * 2)+1; x++)
			{
				bool evenX;//縦が偶数かどうか
				bool evenY;//横が偶数かどうか

				////縦と横が奇数か偶数の数値かを確認する
				evenX = x % 2 == 0 ? false : true;
				evenY = y % 2 == 0 ? false : true;

				//xとyが偶数なら空白
				if (!evenX && !evenY)
				{
					m_unityLine.push_back(0);
				}
				//xが偶数yが奇数なら縦壁
				if (!evenX && evenY)
				{
					int originY = y / 2;//小数点以下切り捨て
					int originX = x / 2;

					m_unityLine.push_back(m_rightWallMap[originY][originX]);
				}
				//xが奇数yが偶数なら横壁
				if (evenX && !evenY)
				{
					int originY = y / 2;//小数点以下切り捨て
					int originX = x / 2;

					m_unityLine.push_back(m_upWallMap[originY][originX]);
				}
				//xとyが奇数なら地面
				if (evenX && evenY)
				{
					int originY = y / 2;//小数点以下切り捨て
					int originX = x / 2;

					m_unityLine.push_back(m_stageMap[originY][originX]);
				}
			}

			count = 0;//リセット

			//aStarMapにA＊の一行ずつ配列を入れる
			m_unityMap.push_back(m_unityLine);
			m_unityLine.clear();//使わない配列は削除
			auto a = 0;

		}

	}

	//配列に数値を入れる処理
	void MapManager::AddArray(int loop, int num)
	{
		int count = 0;
		//余分に配列を入れる
		while (count < 2)
		{
			count++;
			m_unityLine.push_back(9);
		}
		count = 0;//リセット
	}

	//Aスターにある程度余分に配列を入れる処理
	void MapManager::AddExctraUnity(int addArray)
	{
		//範囲外の配列を指定してエラーはかないようにある程度余分に配列を入れておく
		vector<int> extra;//余分に入れる配列
		for (int i = 0; i < (m_stageMap.size() * 2)+4; i++)
		{
			extra.push_back(9);//A*のｘ配列ぶん入れておく
		}

		int count = 0;//何個ほど配列を入れているか数える変数
		while (count < addArray)
		{
			count++;
			m_unityMap.push_back(extra);//配列を余分に入れておく
		}
		m_unityMap;

	}

	//A*マップを渡す
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
		//csvファイルからデータを読み込む
		ifstream ifs(levelPath + L"GroundMap.csv");
		if (ifs)
		{
			string line;
			while (getline(ifs, line))
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
				testMap.push_back(datas);//一行ずつマップデータを入れている
			}
		}
		

		return testMap;
	}

	void MapManager::SetUpdataUnityMapFlag(bool flag)
	{
		m_UpdetaUnityMapFlag = flag;
	}

	//マップのサイズを渡す
	float MapManager::GetMapSize()
	{
		return m_stageMap.size() * 10;
	}

}
//end basecross
