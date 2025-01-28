/*!
@file MovieGameUPEandP.cpp
@brief 敵が打ちあがる際プレイヤーもマンホールを踏んでた際の処理
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpEandP::MovieUpEandP(shared_ptr<Stage>& stagePtr, weak_ptr<Enemy> enemy,weak_ptr<Player> player) :
		Movie(stagePtr),
		m_Enemy(enemy),
		m_Player(player)
	{

	}

	MovieUpEandP::~MovieUpEandP()
	{

	}

	void MovieUpEandP::OnCreate()
	{
		Movie::OnCreate();

		m_sprite = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800));//暗転用のスプライト作成
		m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		m_spriteCol = m_sprite->GetColor();
	}

	void MovieUpEandP::OnUpdate()
	{
		//ステージカメラを取得できなかったらreturn
		if (!m_stageCamera) return;

		auto enemy = m_Enemy.lock();
		auto player = m_Player.lock();

		if (enemy && player)
		{
			auto delta = App::GetApp()->GetElapsedTime();

			//敵情報取得
			auto enemyTrans = enemy->GetComponent<Transform>();
			auto enemyPos = enemyTrans->GetPosition();
			auto enemyQt = enemyTrans->GetQuaternion();
			//プレイヤー情報取得
			auto playerTrans = player->GetComponent<Transform>();
			auto playerPos = playerTrans->GetPosition();
			auto playerQt = playerTrans->GetQuaternion();

			//注視点
			m_movieCamera->SetAt(playerPos);

			//移動処理
			enemyPos.y += 100.0f * delta;
			playerPos.y += 100.0f * delta;

			//場所更新
			enemyTrans->SetPosition(enemyPos);
			playerTrans->SetPosition(playerPos);

			//回転処理
			enemyQt = enemyQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
			enemyTrans->SetQuaternion(enemyQt);
			playerQt = playerQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
			playerTrans->SetQuaternion(playerQt);

			m_time += delta;//時間経過

			//一定時間たったら終了
			if (m_time >= 1.0f)
			{
				m_spriteCol.w += delta;
				m_sprite->SetColor(m_spriteCol);
				if (m_spriteCol.w >= 1.0f)//画面が真っ暗になったら
				{				
					GetStage()->RemoveGameObject<MovieUpEandP>(GetThis<MovieUpEandP>());
					//ゲームオーバシーンに行く
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");//ゲームオーバシーンに移動する

				}

			}

		}
	}


}
//end basecross
