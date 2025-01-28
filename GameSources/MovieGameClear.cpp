/*!
@file MovieGameClear.cpp
@brief ゲームクリアのムービー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieGameClear::MovieGameClear(shared_ptr<Stage>& stagePtr):
		Movie(stagePtr)
	{

	}
	MovieGameClear::~MovieGameClear()
	{

	}

	void MovieGameClear::OnCreate()
	{
		Movie::OnCreate();	
		m_tagetPos = m_movieCamera->GetEye() - Vec3(0.0f, 15.0f, 0.0f);//目的地
		
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");//プレイヤー取得	
		player->MoveSwitch(false);//playerを動かさない
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();
		playerDraw->ChangeCurrentAnimation(L"Happey");//うれしいモーションに変更

	}

	void MovieGameClear::OnUpdate()
	{
		//ステージカメラを取得できなかったらreturn
		if (!m_stageCamera) return;

		auto stage = GetStage();
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto cameraPos = m_movieCamera->GetEye();
		auto player = stage->GetSharedGameObject<Player>(L"Player");//プレイヤー取得
		auto playerTrans = player->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();

		//Playerのアニメーション更新
		playerDraw->UpdateAnimation(delta);

		player->MoveSwitch(false);//playerを動かさない
		Vec3 moveVec= Vec3(cameraPos.x - playerPos.x, cameraPos.y - playerPos.y, cameraPos.z - playerPos.z);//カメラとPlayerの距離ベクトル
		float angle = atan2(moveVec.z, moveVec.x);//角度を取得
		playerTrans->SetRotation(Vec3(0.0f, -angle, 0.0f));//カメラ目線になるようにする
		
		if (m_count == 0)//処理①
		{
			if (cameraPos != m_tagetPos)
			{
				cameraPos.y -= 10.0f*delta;//間接的に移動
				m_movieCamera->SetEye(cameraPos);
				if (abs(cameraPos.y - m_tagetPos.y) <= 0.5f)//ほぼPosがターゲットののPosと一緒なら
				{
					cameraPos = m_tagetPos;
					m_movieCamera->SetEye(cameraPos);
					m_count = 1;//更新
				}
				m_movieCamera->SetEye(cameraPos);

			}

		}
		if (m_count == 1)//処理②
		{
			//ステージマネージャーにゲームクリアのフラグを渡す
			auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetClearFlag(true);

		}


	}

}
//end basecross
