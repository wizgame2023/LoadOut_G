/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {
	//コンストラクタの宣言・デストラクタ
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_speed(15)
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{
		GetComponent<Transform>()->SetScale(2.5f,2.5f,2.5f);
		GetComponent<Transform>()->SetPosition(0, 2.0f, 0);
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		m_CurrentSt = make_shared<Tracking>(GetThis<Enemy>());

		Mat4x4 spanMat;
		spanMat.affineTransformation
		(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 5.0f, 0.0f)
		);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		m_CurrentSt->OnStart();
	}

	void Enemy::OnUpdate()
	{
		auto trans = GetComponent<Transform>();

		m_CurrentSt->OnUpdate();//現在のステート更新処理

		//次のステート用変数に何かしらのステートが代入されたら
		if(m_NextSt)
		{
			m_CurrentSt->OnExit();// 現在のステートが最後に行う処理
			
			m_CurrentSt.reset();// 現在のステート用の変数を空にする
		
			m_CurrentSt = m_NextSt;// 現在のステートに次のステートを代入
			
			m_NextSt.reset();// 次のステート用の変数を空にする
		
			m_CurrentSt->OnExit();// 切り替わった新しいステートの最初に行う処理
		}

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得

		if (mapManager->SelMapNow(trans->GetPosition())==2)
		{
			GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
		}

	}
	void Enemy::OnDestroy()
	{
		// オブジェクト自体が破棄される時に現在と次のステート用の変数を空にする
		m_CurrentSt.reset();
		m_NextSt.reset();

	}

	float Enemy::GetSpeed()
	{
		return m_speed;
	}

	float Enemy::GetAngle()
	{
		return  GetComponent<Transform>()->GetRotation().y;
	}
}
//end basecross
