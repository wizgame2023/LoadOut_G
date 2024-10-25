/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {
	//コンストラクタの宣言・デストラクタ
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr,
		Vec3& pos, const Vec3& rot, const Vec3& scale) :
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot),
		m_scale(scale)
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(m_rot);
		trans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_CurrentSt = make_shared<Patrol>(GetThis<Enemy>());
		m_CurrentSt->OnStart();
	}

	void Enemy::OnUpdate()
	{

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
	}
	void Enemy::OnDestroy()
	{
		// オブジェクト自体が破棄される時に現在と次のステート用の変数を空にする
		m_CurrentSt.reset();
		m_NextSt.reset();

	}
}
//end basecross
