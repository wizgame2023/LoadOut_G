/*!
@file MovieUpEnemyMulti.cpp
@brief 敵が複数打ちあがるムービー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpEnemyMulti::MovieUpEnemyMulti(shared_ptr<Stage>& stagePtr,vector<weak_ptr<Enemy>> upEnemyVec) :
		Movie(stagePtr),
		m_upEnemyVec(upEnemyVec),
		m_removeFlag(false)
	{

	}

	MovieUpEnemyMulti::~MovieUpEnemyMulti()
	{

	}

	void MovieUpEnemyMulti::OnCreate()
	{
		Movie::OnCreate();
		auto sharedEnemy = m_upEnemyVec[0].lock();
		if (sharedEnemy)
		{
			m_movieCameraAt = sharedEnemy->GetComponent<Transform>()->GetPosition();//ムービーカメラの初期注視点を決める
		}

		//打ちあがる敵一人一人にどの方向に打ちあがっていくのか決める
		int i = 0;
		for (i; i < m_upEnemyVec.size(); i++)
		{
			float deg = rand() % 360;//ランダムに何度の方向に進むか決める
			float rad = XMConvertToRadians(deg);//ディグリーからラジアンに変える

			m_upEnemyMoveAngleVec.push_back(rad);//配列に入れる
		}

	}

	void MovieUpEnemyMulti::OnUpdate()
	{
		//ステージカメラを取得できなかったらreturn
		if (!m_stageCamera) return;

		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto speed = 100.0f;//スピード

		//カメラの注視点移動
		m_movieCameraAt.y += speed * delta;
		m_movieCamera->SetAt(m_movieCameraAt);//移動した注視点をセットする

		int enemyCountNum = 0;//敵の数を数える変数

		//複数打ちあがる敵の動きの処理
		for (auto enemy : m_upEnemyVec)
		{
			auto castEnemy = enemy.lock();
			//キャスト出来なかったらコンテニューと自分自身を削除
			if (!castEnemy)
			{
				GetStage()->RemoveGameObject<MovieUpEnemyMulti>(GetThis<MovieUpEnemyMulti>());
				continue;
			}

			//打ちあがるEnemyのコンポーネント取得
			auto enemyTrans = castEnemy->GetComponent<Transform>();
			auto enemyPos = enemyTrans->GetPosition();
			auto enemyQt = enemyTrans->GetQuaternion();


			//ランダムな方向に打ちあがっていく
			enemyPos.x += cosf(m_upEnemyMoveAngleVec[enemyCountNum]) * (speed / 10) * delta;
			enemyPos.z += sinf(m_upEnemyMoveAngleVec[enemyCountNum]) * (speed / 10) * delta;
			enemyPos.y += speed * delta;
			enemyTrans->SetPosition(enemyPos);//位置更新

			enemyQt = enemyQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
			enemyTrans->SetQuaternion(enemyQt);

			//ある程度敵が打ちあがったら終了フラグをオンにする
			if (enemyPos.y >= 150.0f)
			{
				//フラグをオンにする
				m_removeFlag = true;
			}

		}

		//フラグがオンになったら終了処理をする
		if (m_removeFlag)
		{
			for (auto enemy : m_upEnemyVec)
			{
				auto sharedEnemy = enemy.lock();

				if (sharedEnemy)//ちゃんとロックしているか確認する
				{
					GetStage()->RemoveGameObject<Enemy>(sharedEnemy);//削除する		
				
					//SE生成 敵の叫び声
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Scream", 0, 0.9f);
				}
			}
			GetStage()->RemoveGameObject<MovieUpEnemyMulti>(GetThis<MovieUpEnemyMulti>());//自分自身を削除
		}


	}

}
//end basecross
