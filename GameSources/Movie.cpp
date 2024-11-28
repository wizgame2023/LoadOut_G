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
		CameraChange();
		Vec3 cameraEye = m_movieCamera->GetEye();
		testPos = cameraEye;
	}

	void Movie::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		//auto pos = m_stageCamera.lock()->GetEye();
		//auto pos = Vec3(0.0f, 0.0f, 0.0f);

		//テスト用(動くかどうか確認しただけ)///////////////////////////////////////////////////////////////////
		Vec3 cameraEye = m_movieCamera->GetEye();
		Vec3 m_MoviePos = testPos+Vec3(100.0f, 0.0f, 10.0f);//目的地
		if (cameraEye != m_MoviePos)
		{
			cameraEye += CameraMove(30,cameraEye,m_MoviePos);//間接的に移動する
			m_movieCamera->SetEye(cameraEye);//移動する
			if (abs(cameraEye.x - m_MoviePos.x) <= 0.5f && abs(cameraEye.z - m_MoviePos.z) <= 0.5f)//ほぼPosがターゲットののPosと一緒なら
			{
				cameraEye = m_MoviePos;
				m_movieCamera->SetEye(cameraEye);//一緒とみなす
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	//ムービー用のカメラに変更させる
	void Movie::CameraChange()
	{
		auto startPos = Vec3(0.0f, 50.0f, -30.0f);//初期位置

		m_stageCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());//ステージ用のカメラを取得
		auto a = m_stageCamera.lock()->GetEye();
		m_movieCamera = ObjectFactory::Create<Camera>();//カメラ作成
		m_movieCamera->SetEye(startPos);//初期位置
		m_movieCamera->SetAt(m_stageCamera.lock()->GetAt());//初期中心点
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
