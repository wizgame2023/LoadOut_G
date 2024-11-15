/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {
	//コンストラクタの宣言・デストラクタ
	Enemy::Enemy(shared_ptr<Stage>& StagePtr) :
		Actor(StagePtr),
		m_pos(-0, 2.0f, 0),
		m_playerPos(0,0,0),
		m_speed(15),
		m_angle(0)
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{
		GetComponent<Transform>()->SetScale(1.5f,1.5f,1.5f);
		GetComponent<Transform>()->SetPosition(m_pos);
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		m_CurrentSt = make_shared<Patrol>(GetThis<Enemy>());

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

		AddTag(L"Enemy");

		m_CurrentSt->OnStart();

		m_forwardRay = GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 15.0f);
		m_playerRay= GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 50.0f);
	}

	void Enemy::OnUpdate()
	{
		auto trans = GetComponent<Transform>();
		auto app = App::GetApp;
		m_CurrentSt->OnUpdate();//現在のステート更新処理
		m_pos = trans->GetPosition();
		//次のステート用変数に何かしらのステートが代入されたら
		if(m_NextSt)
		{
			m_CurrentSt->OnExit();// 現在のステートが最後に行う処理
			
			m_CurrentSt.reset();// 現在のステート用の変数を空にする
		
			m_CurrentSt = m_NextSt;// 現在のステートに次のステートを代入
			
			m_NextSt.reset();// 次のステート用の変数を空にする
		
			m_CurrentSt->OnExit();// 切り替わった新しいステートの最初に行う処理
		}

		//auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得

		//if (mapManager->SelMapNow(trans->GetPosition())==2)
		//{
		//	GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
		//}
		auto rot = GetComponent<Transform>()->GetRotation();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");//playerを取得
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//playerのポジションを取得
		float playerVec = atan2f((m_pos.x - m_playerPos.x), (m_pos.z - m_playerPos.z)) + XM_PI * 0.5;//所有者(Enemy)を中心にplayerの方向を計算

		m_forwardRay->SetAngle(m_angle);
		//m_leftRay->SetAngle(m_angle - XM_PI * 0.5f);
		m_playerRay->SetAngle(playerVec);
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"\n敵の回転.x : " << rot.x
			<< L"\n敵の回転.y : " << rot.y
			<< L"\n敵の回転.z : " << rot.z
			<< L"\nplayerPOs.x : " << m_playerPos.x
			<< L"\nplayerPOs.z : " << m_playerPos.z
			<< L"\nアングル : " << m_angle
			<< L"\nplayerRay : " << XMConvertToDegrees(playerVec)
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

	float Enemy::GetAngle()
	{
		return  m_angle;
	}

	void Enemy::SetAngle(float angle)
	{
		m_angle = angle;
	}

	float Enemy::GetDistance(Vec3 a, Vec3 b)
	{ 
		float numX = a.x - b.z;
		float numY = a.y - b.y;
		float numZ = a.z - b.z;

		return  sqrtf(numX * numX + numY * numY + numZ * numZ);

	}

	Vec3 Enemy::GetPlayerPos()
	{
		return m_playerPos;
	}
	shared_ptr<Ray> Enemy::GetForwardRay()
	{
		return m_forwardRay;
	}

	shared_ptr<Ray> Enemy::GetPlayerRay()
	{
		return m_playerRay;
	}
}
//end basecross
