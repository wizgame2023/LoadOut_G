/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr, float mapSize) :
		GameObject(stagePtr),
		m_mapSize(mapSize)
	{

	}
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_mapSize(200)
	{

	}

	MiniMapManager::~MiniMapManager()
	{

	}

	//生成処理
	void MiniMapManager::OnCreate()
	{
		auto stage = GetStage();//ステージ取得
		float Lenght = 225.0f;//ミニマップの直径
		auto background = stage->AddGameObject<Sprite>(L"Gray", Vec2(Lenght, Lenght), Vec3(-640+(Lenght/2.0f), 400.0f - (Lenght / 2.0f), 0.0f));
		background->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		m_startPos = Vec3(-640 + (Lenght / 2.0f), 400.0f - (Lenght / 2.0f),5.0f);//スタートポジション
		m_mapMagnification = Lenght / m_mapSize;//マップの倍率

		CreateManhole();//マンホールを生成
		CreateEnemy();//敵UI生成
		CreatePlayer();//PlayerUI作成
		CreateWall();//壁UI生成
	}

	//更新処理
	void MiniMapManager::OnUpdate()
	{
		UpdateBattery();
		UpdateEnemy();
	}

 
	//ミニマップ用のアイテムを生成
	void MiniMapManager::CreateBattery()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto objVec = stage->GetGameObjectVec();
		int count = 0;
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto item : objVec)
		{
			auto castitem = dynamic_pointer_cast<Spanner>(item);
			if (castitem)//アイテム型にキャストする
			{
				auto itemTrans = item->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();
				
				auto miniMapItem = stage->AddGameObject<MiniMapItem>(castitem, L"White", Vec2(itemScale.x * m_mapMagnification, itemScale.z * m_mapMagnification)/*size*/,
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f),
					Col4(1.0f, 1.0f, 0.0f, 1.0f)/*黄色にする*/, 5/*レイヤー*/);
				miniMapItem->AddTag(L"MiniMapItem");//タグを追加
				count++;
			}
		}
		m_beforeItemNum = count;
	}
	//ミニマップ用のアイテムを生成(Updeta版)
	void MiniMapManager::UpdateBattery()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto objVec = stage->GetGameObjectVec();
		int itemNumNow = 0;
		//ステージにあるアイテムの数をカウントする
		for (auto item : objVec)
		{
			auto castitem = dynamic_pointer_cast<Spanner>(item);
			if (castitem)//アイテム型にキャストする
			{
				itemNumNow++;
			}
		}

		//今あるアイテムの数が前よりも多かったらミニマップのアイテムの表示を更新する
		if (itemNumNow > m_beforeItemNum)
		{
			//ミニマップにあるアイテムをリセットする
			for (auto sprite : objVec)
			{
				auto castsprite = dynamic_pointer_cast<Sprite>(sprite);
				if (castsprite)//アイテム型にキャストする
				{
					//タグがMiniMapItem
					if (castsprite->FindTag(L"MiniMapItem"))
					{
						castsprite->MyDestroy();//自分自身を消去する
					}
				}
			}

			//再生成する
			CreateBattery();
		}

		m_beforeItemNum = itemNumNow;//更新する
	}

	//ミニマップの敵表示(Update版)
	void MiniMapManager::UpdateEnemy()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto objVec = stage->GetGameObjectVec();
		int enemyNumNow = 0;
		//ステージにあるアイテムの数をカウントする
		for (auto enemy : objVec)
		{
			auto castEnemy = dynamic_pointer_cast<Enemy>(enemy);
			if (castEnemy)//アイテム型にキャストする
			{
				enemyNumNow++;
			}
		}

		//今あるアイテムの数が前よりも多かったらミニマップのアイテムの表示を更新する
		if (enemyNumNow > m_beforeEnemyNum)
		{
			//ミニマップにあるアイテムをリセットする
			for (auto sprite : objVec)
			{
				auto castsprite = dynamic_pointer_cast<MiniMapActor>(sprite);
				if (castsprite)//キャストする
				{
					//タグがMiniMapItem
					if (castsprite->FindTag(L"MiniMapEnemy"))
					{
						castsprite->MyDestroy();//自分自身を消去する
					}
				}
			}
			//再生成する
			CreateEnemy();
		}

		m_beforeEnemyNum = enemyNumNow;//更新する
	}


	//ミニマップ用のマンホールを作成
	void MiniMapManager::CreateManhole()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto obj = stage->GetGameObjectVec();
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto manhole : obj)
		{	
			auto castManhole = dynamic_pointer_cast<Manhole>(manhole);
			if (castManhole)//アイテム型にキャストする
			{
				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<ManholeSprite>(castManhole, L"Bule",Vec2((itemScale.x * m_mapMagnification), (itemScale.z * m_mapMagnification)),
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f),Col4(1.0f,1.0f,1.0f,1.0f), 10);
			}
		}

	}

	//ミニマップ用のハッチを作成
	void MiniMapManager::CreateHatch()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto objVec = stage->GetGameObjectVec();
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto obj : objVec)
		{
			auto castHatch = dynamic_pointer_cast<Hatch>(obj);
			if (castHatch)//アイテム型にキャストする
			{
				auto hatchTrans = castHatch->GetComponent<Transform>();
				auto hatchPos = hatchTrans->GetPosition();
				auto hatchScale = hatchTrans->GetScale();

				stage->AddGameObject<MiniMapHatch>(L"White", Vec2((hatchScale.x * m_mapMagnification), (hatchScale.z * m_mapMagnification)),
					Vec3(m_startPos.x + (hatchPos.x * m_mapMagnification), m_startPos.y + (hatchPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(0.35f, 1.0f, 0.1f, 1.0f), 10);//緑
			}
		}
	}

	//ミニマップの用の壁を作成
	void MiniMapManager::CreateWall()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto obj = stage->GetGameObjectVec();

		////テスト用壁を表示
		for (auto manhole : obj)
		{
			auto castManhole = dynamic_pointer_cast<Wall>(manhole);
			if (castManhole)//アイテム型にキャストする
			{
				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemRot = itemTrans->GetRotation();
				if (itemRot.y > 0)
				{
					itemRot.y = XMConvertToRadians(90.0f);
				}
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<Sprite>(L"White", Vec2((itemScale.x * m_mapMagnification), (itemScale.z * m_mapMagnification)),
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, itemRot.y), Col4(1.0f, 1.0f, 1.0f, 1.0f), 10);
			}
		}

	}

	//ミニマップ用の敵を作成
	void MiniMapManager::CreateEnemy()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto objVec = stage->GetGameObjectVec();
		int count = 0;//生成したミニマップのEnemyの数を数える

		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto obj : objVec)
		{
			auto castEnemy = dynamic_pointer_cast<Enemy>(obj);
			if (castEnemy)//Enemy型にキャストする
			{
				float Lenght = 225.0f;//ミニマップの直径

				auto enemyTrans = castEnemy->GetComponent<Transform>();
				auto enemyPos = enemyTrans->GetPosition();
				auto enemyScale = enemyTrans->GetScale();

				auto sprite = stage->AddGameObject<MiniMapActor>(castEnemy, L"MiniEnemy", Vec2((enemyScale.x * m_mapMagnification) * 2.0f, (enemyScale.z * m_mapMagnification) * 2.0f), m_startPos, m_mapSize, Lenght);
				sprite->AddTag(L"MiniMapEnemy");//タグ追加
				count++;

			}
		}

		m_beforeEnemyNum = count;//生成したミニマップのEnemyの数を渡す
	}

	void MiniMapManager::CreatePlayer()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto obj = stage->GetGameObjectVec();
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto manhole : obj)
		{
			auto castPlayer = dynamic_pointer_cast<Player>(manhole);
			if (castPlayer)//Enemy型にキャストする
			{
				float Lenght = 225.0f;//ミニマップの直径

				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<MiniMapActor>(castPlayer, L"MiniPlayer", Vec2((10 * m_mapMagnification), (10 * m_mapMagnification)), m_startPos, m_mapSize, Lenght);
			}
		}

	}

	Vec3 MiniMapManager::GetStartPos()
	{
		return m_startPos;
	}

	

}
//end basecross
