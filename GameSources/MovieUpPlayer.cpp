/*!
@file MovieUpPlayer.cpp
@brief Playerが打ちあがる時のムービー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpPlayer::MovieUpPlayer(shared_ptr<Stage>& stagePtr):
		Movie(stagePtr)
	{

	}

	MovieUpPlayer::~MovieUpPlayer()
	{

	}

	void MovieUpPlayer::OnCreate()
	{
		Movie::OnCreate();

		m_sprite = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800));//暗転用のスプライト作成
		m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		m_spriteCol = m_sprite->GetColor();
	}

	void MovieUpPlayer::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		//打ちあがるPlayer
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");
		auto playerTrans = player->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();
		auto playerQt = playerTrans->GetQuaternion();
		player->MoveSwich(false);//操作効かないようにする
		
		playerPos.y += 100.0f*delta;
		player->GetComponent<Transform>()->SetPosition(playerPos);


		playerQt = playerQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
		playerTrans->SetQuaternion(playerQt);


		m_movieCamera->SetAt(playerPos);

		//この後にゲームオーバ用のアニメーションを入れる
		m_time += delta;

		if (m_time >= 1.0f)
		{
			m_spriteCol.w += delta;
			m_sprite->SetColor(m_spriteCol);
			if (m_spriteCol.w >= 1.0f)//画面が真っ暗になったら
			{
				//ゲームオーバシーンに行く
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");//ゲームオーバシーンに移動する

			}
		}
	}

}
//end basecross
