/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{

	}

	MiniMapManager::~MiniMapManager()
	{

	}

	void MiniMapManager::OnCreate()
	{
		auto stage = GetStage();//ステージ取得
		float Lenght = 225.0f;//ミニマップの直径
		stage->AddGameObject<Sprite>(L"Gray", Vec2(Lenght, Lenght), Vec3(-640+(Lenght/2.0f), 400.0f - (Lenght / 2.0f), 0.0f));

		m_startPos = Vec3(-640 + (Lenght / 2.0f), 400.0f - (Lenght / 2.0f),5.0f);//スタートポジション
		auto test = m_startPos;
		auto a = 0;
		m_mapSize = 200;//mapの直径
		m_mapMagnification = Lenght / m_mapSize;//マップの倍率

		CreateManhole();//マンホールを生成//もしかしたらエラーでる？
		CreateEnemy();
	}

	void MiniMapManager::OnUpdate()
	{

	}

	//ミニマップ用の壁を生成
	void MiniMapManager::CreateWall()
	{

	}

	//ミニマップ用のアイテムを生成
	void MiniMapManager::CreateItem()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto obj = stage->GetGameObjectVec();
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto item : obj)
		{
			if (dynamic_pointer_cast<Item>(item))//アイテム型にキャストする
			{
				auto castitem = dynamic_pointer_cast<Item>(item);
				auto itemTrans = item->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();
				
				stage->AddGameObject<MiniMapItem>(castitem ,L"White", Vec2(itemScale.x * m_mapMagnification, itemScale.z * m_mapMagnification),5,
					Vec3(m_startPos.x+(itemPos.x*m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification),0.0f),Vec3(0.0f,0.0f,0.0f));
			}
		}
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
			if (dynamic_pointer_cast<Manhole>(manhole))//アイテム型にキャストする
			{
				auto castManhole = dynamic_pointer_cast<Manhole>(manhole);
				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<Sprite>(L"Red", Vec2((itemScale.x * m_mapMagnification), (itemScale.z * m_mapMagnification)),
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f),Col4(1.0f,1.0f,1.0f,1.0f), 10);
			}
		}

	}

	//ミニマップ用の敵を作成
	void MiniMapManager::CreateEnemy()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto obj = stage->GetGameObjectVec();
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto manhole : obj)
		{
			if (dynamic_pointer_cast<Enemy>(manhole))//アイテム型にキャストする
			{
				float Lenght = 225.0f;//ミニマップの直径

				auto castEnemy = dynamic_pointer_cast<Actor>(manhole);
				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<MiniMapActor>(castEnemy, L"MiniEnemy", Vec2((itemScale.x / m_mapMagnification) * 3, (itemScale.z / m_mapMagnification) * 3), m_startPos, m_mapSize, Lenght);
			}
		}

	}

	Vec3 MiniMapManager::GetStartPos()
	{
		return m_startPos;
	}

	

}
//end basecross
