/*!
@file MovieUpEnemy.cpp
@brief 敵が上がるムービー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovieUpEnemy::MovieUpEnemy(shared_ptr<Stage>& stagePtr,shared_ptr<Enemy> enemy) :
		Movie(stagePtr),
		m_Enemy(enemy)
	{

	}

	MovieUpEnemy::~MovieUpEnemy()
	{
	}

	void MovieUpEnemy::OnCreate()
	{
		//打ちあがるEnemyのコンポーネント取得
		auto enemyTrans = m_Enemy.lock()->GetComponent<Transform>();
		auto enemyPos = enemyTrans->GetPosition();
		

		CameraChange();//カメラを変更する
		m_movieCamera->SetAt(enemyPos);//注視点を打ちあがるEnemyに固定する

		m_Enemy.lock()->MoveSwich(false);//動かなくする

	}

	void MovieUpEnemy::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		//打ちあがるEnemyのコンポーネント取得
		auto enemyTrans = m_Enemy.lock()->GetComponent<Transform>();
		auto enemyPos = enemyTrans->GetPosition();
		auto enemyRot = enemyTrans->GetQuaternion();

		m_movieCamera->SetAt(enemyPos);//注視点を打ちあがるEnemyに固定する
		auto speed = 100.0f;
		enemyPos.y += speed * delta;
		enemyTrans->SetPosition(enemyPos);//位置更新

		enemyRot = enemyRot*Quat(0.0f, 1.0f*(sin(XMConvertToRadians(30.0f)) / 2), 0.0f,cos(XMConvertToRadians(30.0f)) / 2.0f);
		enemyTrans->SetQuaternion(enemyRot);

		//終了処理
		if (enemyPos.y >= 150.0f)
		{
			auto View = GetStage()->CreateView<SingleView>();//ビュー作成
			auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 50.0f, -30.0f));

			View->SetCamera(PtrCamera);//カメラを戻す
			GetStage()->SetView(View);
			GetStage()->RemoveGameObject<MovieGameStart>(GetThis<MovieGameStart>());//自分自身を削除

		}


	}

}
//end basecross
