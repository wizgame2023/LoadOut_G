/*!
@file Movie.cpp
@brief ムービー関係の親クラス
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Movie::Movie(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}

	Movie::~Movie()
	{

	}

	void Movie::OnCreate()
	{
		auto stage = GetStage();
		m_collsionManager = GetStage()->GetSharedGameObject<StageCollisionManager>(L"CollsionManager");
		m_collsionManager->SetCollisionSwhich(false);//コリジョンオフにする

		auto objVec = stage->GetGameObjectVec();
		//アクターを継承しているものだけ取得
		for (auto obj : objVec)
		{
			auto actorCast = dynamic_pointer_cast<Actor>(obj);
			auto batteryCast = dynamic_pointer_cast<Battery>(obj);
			auto manholeCast = dynamic_pointer_cast<Manhole>(obj);

			//アクターを継承しているオブジェクト停止
			if (actorCast)
			{
				actorCast->MoveSwitch(false);//動けないようにする
				m_actorVec.push_back(actorCast);
			}
			////バッテリーオブジェクト停止
			//if (batteryCast)//バッテリー
			//{
			//	batteryCast->SetUpdateSwitch(false);//動けないようにする
			//	m_batteryVec.push_back(batteryCast);
			//}
			////マンホールオブジェクト停止
			//if (manholeCast)//マンホール
			//{
			//	manholeCast->SetUpdateSwitch(false);//動けないようにする
			//	m_manholeVec.push_back(manholeCast);
			//}

		}

		m_stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		m_stageManager->SetUpdateFlag(false);//動かなくする

		CameraChange();//カメラ変更
	}

	void Movie::OnUpdate()
	{

	}

	void Movie::OnDestroy()
	{
		//動くオブジェクトが動けるようにする
		for (auto actor : m_actorVec)
		{
			auto actorCheck = actor.lock();
			if (actorCheck)
			{
				actorCheck->MoveSwitch(true);//動ける
			}
		}
		//for (auto battery : m_batteryVec)
		//{
		//	auto batteryCheck = battery.lock();
		//	if (batteryCheck)
		//	{
		//		batteryCheck->SetUpdateSwitch(true);//動ける
		//	}
		//}
		//for (auto manhole : m_manholeVec)
		//{
		//	auto manholeCheck = manhole.lock();
		//	if (manholeCheck)
		//	{
		//		manholeCheck->SetUpdateSwitch(true);//動ける
		//	}
		//}

		//カメラを戻す処理
		auto View = GetStage()->CreateView<SingleView>();//ビュー作成
		auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 50.0f, -30.0f));

		View->SetCamera(PtrCamera);//カメラを戻す
		GetStage()->SetView(View);

		m_collsionManager->SetCollisionSwhich(true);//コリジョンオンにする
		m_stageManager->SetUpdateFlag(true);//ステージマネージャーが動くようにする
	}

	//ムービー用のカメラに変更させる
	void Movie::CameraChange()
	{//　　　　　　　　　　　　　　↓マップの直径
		auto startPos = Vec3(0.0f, 200.0f, -200.0f);//初期位置

		m_stageCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());//ステージ用のカメラを取得
		auto a = m_stageCamera->GetEye();
		m_movieCamera = ObjectFactory::Create<Camera>();//カメラ作成
		m_movieCamera->SetEye(m_stageCamera->GetEye());//初期位置
		m_movieCamera->SetAt(m_stageCamera->GetAt());//初期中心点
		auto movieView = GetStage()->CreateView<SingleView>();//ビュー作成
		movieView->SetCamera(m_movieCamera);//ビューにムービー用のカメラ設置
		GetStage()->SetView(movieView);//ステージにムービー用のビューを設置する

	}

	//カメラを動かす
	Vec3 Movie::CameraMove(float speed,Vec3 pos,Vec3 tagetPos)//移動する距離を決めている
	{
		float vecX = tagetPos.x - pos.x;//目標位置とPlayerとのX座標の距離を測っている
		float vecZ = tagetPos.z - pos.z;//目標位置とPlayerとのZ座標の距離を測っている
		float rad = atan2(vecZ, vecX);//角度を求める（ラジアン）

		Vec3 moveVec(0.0f, 0.0f, 0.0f);

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();//デルタタイムを取得
		moveVec.x = (speed * cos(rad)) * delta;//間接的に距離を足している
		moveVec.z = (speed * sin(rad)) * delta;//間接的に距離を足している

		return moveVec;
	}


}
//end basecross
