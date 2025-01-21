/*!
@file MovieGameOver.cpp
@brief ゲームオーバーのムービー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieGameOver::MovieGameOver(shared_ptr<Stage>& stagePtr) :
		Movie(stagePtr)
	{

	}
	MovieGameOver::~MovieGameOver()
	{

	}

	void MovieGameOver::OnCreate()
	{
		Movie::OnCreate();
		m_tagetPos = m_movieCamera->GetEye() - Vec3(0.0f, 15.0f, 0.0f);//目的地

		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");//プレイヤー取得
		player->MoveSwitch(false);//playerを動かさない
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();
		playerDraw->ChangeCurrentAnimation(L"Player_Down");//やられたモーションに変更


	}

	void MovieGameOver::OnUpdate()
	{
		auto stage = GetStage();
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto cameraPos = m_movieCamera->GetEye();
		auto player = stage->GetSharedGameObject<Player>(L"Player");//プレイヤー取得
		auto playerTrans = player->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();


		player->MoveSwitch(false);//playerを動かさない

		if (m_count == 0)//処理①
		{
			if (cameraPos != m_tagetPos)
			{
				cameraPos.y -= 10.0f * delta;//間接的に移動
				m_movieCamera->SetEye(cameraPos);
				if (abs(cameraPos.y - m_tagetPos.y) <= 0.5f)//ほぼPosがターゲットののPosと一緒なら
				{
					cameraPos = m_tagetPos;
					m_movieCamera->SetEye(cameraPos);
					//m_count = 1;//更新
				}
				m_movieCamera->SetEye(cameraPos);

			}
			//Playerのアニメーション更新
			m_gameOverFlag = playerDraw->UpdateAnimation(delta);
			if (m_gameOverFlag)
			{
				m_count++;
			}

		}
		if (m_count == 1)//処理②
		{		
			//ステージマネージャーにゲームクリアのフラグを渡す
			auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetGameOverFlag(true);

		}

		if (m_count == 2)//処理③
		{
		}


	}

}
//end basecross
