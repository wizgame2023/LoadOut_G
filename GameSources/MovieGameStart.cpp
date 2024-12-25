/*!
@file MovieGameStart.cpp
@brief ゲーム開始時のムービ用
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieGameStart::MovieGameStart(shared_ptr<Stage>& stagePtr,float mapSize,float speed) :
		Movie(stagePtr),
		m_mapSize(mapSize),
		m_speed(speed)
	{

	}

	MovieGameStart::~MovieGameStart()
	{
	}

	void MovieGameStart::OnCreate()
	{
		Movie::OnCreate();
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto obj = stage->GetGameObjectVec();
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto enemy : obj)
		{
			auto castEnemy = dynamic_pointer_cast<Enemy>(enemy);
			if (castEnemy)//アイテム型にキャストする
			{
				castEnemy->MoveSwich(false);//うごかなくさせる
			}
		}
		for (auto player : obj)
		{
			auto castPlayer = dynamic_pointer_cast<Player>(player);
			if (castPlayer)//アイテム型にキャストする
			{
				castPlayer->MoveSwich(false);//うごかなくさせる
			}
		}


	}

	void MovieGameStart::OnUpdate()
	{
		auto cameraPos = m_movieCamera->GetEye();//カメラのポジションを取得
		auto tagetPos = Vec3(0.0f, 0.0f, m_mapSize/2);//目的地

		if (m_count == 0)//処理①
		{
			if (cameraPos != tagetPos)//目的地とカメラの位置が同じでないなら
			{
				cameraPos += CameraMove(m_speed, cameraPos, tagetPos);
				m_movieCamera->SetEye(cameraPos);
				if (abs(cameraPos.x - tagetPos.x) <= 5.8f && abs(cameraPos.z - tagetPos.z) <= 5.8f)//ほぼPosがターゲットののPosと一緒なら
				{
					tagetPos.y = cameraPos.y;
					m_movieCamera->SetEye(tagetPos);//一緒とみなす
					m_count = 1;
				}

			}

			auto cameraAt = m_movieCamera->GetAt();//カメラのAtを取得
			auto tagetAt = cameraPos-Vec3(0.0f,cameraPos.y,-30.0f);
			m_movieCamera->SetAt(tagetAt);

		}

		if (m_count == 1)//処理②
		{
			auto View = GetStage()->CreateView<SingleView>();//ビュー作成
			auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 50.0f, -30.0f));

			View->SetCamera(PtrCamera);//カメラを戻す
			GetStage()->SetView(View);
			GetStage()->RemoveGameObject<MovieGameStart>(GetThis<MovieGameStart>());//自分自身を削除

			//Acotrが動けるようにする
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto enemy : obj)
			{
				auto castEnemy = dynamic_pointer_cast<Enemy>(enemy);
				if (castEnemy)//アイテム型にキャストする
				{
					castEnemy->MoveSwich(true);//うごかなくさせる
				}
			}
			for (auto player : obj)
			{
				auto castPlayer = dynamic_pointer_cast<Player>(player);
				if (castPlayer)//アイテム型にキャストする
				{
					castPlayer->MoveSwich(true);//うごかなくさせる
				}
			}

		}

	}

	//ムービー用のカメラに変更させる
	void MovieGameStart::CameraChange()
	{
		float stageLenght = m_mapSize;//ステージの直径
		auto startPos = Vec3(0.0f, stageLenght, -stageLenght);//初期位置
		m_StageView = GetStage()->GetView();
		m_stageCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());//ステージ用のカメラを取得 なぜかこの関数が終わるとこの変数の中身が消えます

		m_movieCamera = ObjectFactory::Create<Camera>();//カメラ作成
		m_movieCamera->SetEye(startPos);//初期位置
		m_movieCamera->SetAt(m_stageCamera->GetAt());//初期中心点
		auto movieView = GetStage()->CreateView<SingleView>();//ビュー作成
		movieView->SetCamera(m_movieCamera);//ビューにムービー用のカメラ設置
		GetStage()->SetView(movieView);//ステージにムービー用のビューを設置する

	}
}
//end basecross
