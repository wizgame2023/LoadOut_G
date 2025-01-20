/*!
@file MovieUpEnemy.cpp
@brief 敵が上がるムービー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpEnemy::MovieUpEnemy(shared_ptr<Stage>& stagePtr,weak_ptr<Enemy> enemy) :
		Movie(stagePtr),
		m_Enemy(enemy)
	{

	}

	MovieUpEnemy::~MovieUpEnemy()
	{
	}

	void MovieUpEnemy::OnCreate()
	{		
		Movie::OnCreate();

		//打ちあがるEnemyのコンポーネント取得
		auto enemyTrans = m_Enemy.lock()->GetComponent<Transform>();
		auto enemyPos = enemyTrans->GetPosition();
		

		m_movieCamera->SetAt(enemyPos);//注視点を打ちあがるEnemyに固定する

		m_Enemy.lock()->MoveSwich(false);//動かなくする

	}

	void MovieUpEnemy::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		//打ちあがるEnemyのコンポーネント取得
		auto enemyTrans = m_Enemy.lock()->GetComponent<Transform>();
		auto enemyPos = enemyTrans->GetPosition();
		auto enemyQt = enemyTrans->GetQuaternion();

		m_movieCamera->SetAt(enemyPos);//注視点を打ちあがるEnemyに固定する
		auto speed = 100.0f;
		enemyPos.y += speed * delta;
		enemyTrans->SetPosition(enemyPos);//位置更新

		enemyQt = enemyQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
		enemyTrans->SetQuaternion(enemyQt);

		//終了処理
		if (enemyPos.y >= 150.0f)
		{
			//SE生成 敵の叫び声
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			auto SE = SEManager->Start(L"Scream", 0, 0.9f);
			auto stage = GetStage();

			GetStage()->RemoveGameObject<Enemy>(m_Enemy.lock());
			GetStage()->RemoveGameObject<MovieUpEnemy>(GetThis<MovieUpEnemy>());//自分自身を削除
		}


	}

}
//end basecross
