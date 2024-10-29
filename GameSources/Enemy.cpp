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
		m_scale(scale),
		m_speed(10)
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

		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
			wss << L"transform : "
			<< L"\n"
			<< L"postion : ("
			<< L"\nx."
			<< trans->GetPosition().x
			<< L","
			<< "\ny."
			<< trans->GetPosition().y
			<< L","
			<< "\nz."
			<< trans->GetPosition().z
			<< L")"
			<< L"\nRot:"
			<< L"\nx." << trans->GetRotation().x
			<< L"\ny." << trans->GetRotation().y
			<< L"\nz." << trans->GetRotation().z
			<< endl;
		scene->SetDebugString(wss.str());

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
}
//end basecross
